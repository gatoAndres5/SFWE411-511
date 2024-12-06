import unittest
from unittest.mock import MagicMock, patch
from codeHistorian import (
    client, parse_address, read_modbus_addresses_to_csv,
    output_coil_addresses, input_addresses
)  # Replace 'codeHistorian' with your actual script name
import os

class TestModbusIO(unittest.TestCase):

    @patch('codeHistorian.client.connect')
    @patch('codeHistorian.client.read_coils')
    @patch('codeHistorian.client.read_discrete_inputs')
    @patch('codeHistorian.client.close')
    def test_read_modbus_addresses_to_csv(self, mock_close, mock_read_discrete_inputs, mock_read_coils, mock_connect):
        """
        Test reading both output coils and input addresses, and writing them to a CSV.
        """
        # Mock connect behavior
        mock_connect.return_value = True

        # Determine the highest offset used in output_coil_addresses and input_addresses
        max_offset_coils = max(int(address.split('.')[1]) for address in output_coil_addresses.values())
        max_offset_inputs = max(int(address.split('.')[1]) for address in input_addresses.values())

        # Mock read_coils behavior
        mock_read_coils.return_value.isError.return_value = False
        # Ensure enough bits to cover all offsets for coils
        mock_read_coils.return_value.bits = [True if i % 2 == 0 else False for i in range(max_offset_coils + 1)]

        # Mock read_discrete_inputs behavior
        mock_read_discrete_inputs.return_value.isError.return_value = False
        # Ensure enough bits to cover all offsets for inputs
        mock_read_discrete_inputs.return_value.bits = [False if i % 2 == 0 else True for i in range(max_offset_inputs + 1)]

        # Output file name
        test_csv = 'test_io_states.csv'

        # Set a default duration for the test
        duration = 5  # or whatever duration you expect

        # Run the function with the duration argument
        read_modbus_addresses_to_csv(test_csv, duration)

        # Check if the file is created
        self.assertTrue(os.path.exists(test_csv))

        # Verify file contents
        with open(test_csv, 'r') as f:
            lines = f.readlines()

        # Check header
        self.assertEqual(lines[0].strip(), 'Description,Address,State')

        # Check output coils content lines
        coil_start_index = 1
        for i, (description, address) in enumerate(output_coil_addresses.items()):
            base_address, offset = parse_address(address)
            expected_state = 'ON' if mock_read_coils.return_value.bits[offset] else 'OFF'
            self.assertIn(f'{description},{address},{expected_state}', lines[coil_start_index + i].strip())

        # Check input addresses content lines
        input_start_index = coil_start_index + len(output_coil_addresses)
        for i, (description, address) in enumerate(input_addresses.items()):
            base_address, offset = parse_address(address)
            expected_state = 'ON' if mock_read_discrete_inputs.return_value.bits[offset] else 'OFF'
            self.assertIn(f'{description},{address},{expected_state}', lines[input_start_index + i].strip())

        # Verify that client methods were called
        mock_connect.assert_called_once()
        mock_read_coils.assert_called()
        mock_read_discrete_inputs.assert_called()
        mock_close.assert_called_once()

    def test_parse_address(self):
        """
        Test the parse_address function to ensure it extracts base address and offset correctly.
        """
        test_address = '%QX4.3'
        base_address, offset = parse_address(test_address)
        self.assertEqual(base_address, 4)
        self.assertEqual(offset, 3)

if __name__ == '__main__':
    unittest.main()
