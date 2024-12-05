import unittest
from unittest.mock import MagicMock, patch
from codeHistorian import client, parse_address, read_output_coils_to_csv, output_coil_addresses  # Replace 'your_script' with your actual script name
import os

class TestModbusOutputCoils(unittest.TestCase):

    @patch('codeHistorian.client.connect')
    @patch('codeHistorian.client.read_coils')
    @patch('codeHistorian.client.close')
    def test_read_output_coils_to_csv(self, mock_close, mock_read_coils, mock_connect):
        """
        Test reading coils and writing to CSV.
        """
        # Mock connect behavior
        mock_connect.return_value = True

        # Determine the highest offset used in output_coil_addresses
        max_offset = max(int(address.split('.')[1]) for address in output_coil_addresses.values())

        # Mock read_coils behavior
        mock_read_coils.return_value.isError.return_value = False
        # Ensure enough bits to cover all offsets
        mock_read_coils.return_value.bits = [True if i % 2 == 0 else False for i in range(max_offset + 1)]

        # Output file name
        test_csv = 'test_coil_states2.csv'

        # Run the function
        read_output_coils_to_csv(test_csv)

        # Check if the file is created
        self.assertTrue(os.path.exists(test_csv))

        # Verify file contents
        with open(test_csv, 'r') as f:
            lines = f.readlines()

        # Check header
        self.assertEqual(lines[0].strip(), 'Description,Address,State')

        # Check content lines
        for i, (description, address) in enumerate(output_coil_addresses.items()):
            base_address, offset = parse_address(address)
            expected_state = 'ON' if mock_read_coils.return_value.bits[offset] else 'OFF'
            self.assertIn(f'{description},{address},{expected_state}', lines[i + 1])

        # Cleanup
        #os.remove(test_csv)

        # Verify that client methods were called
        mock_connect.assert_called_once()
        mock_read_coils.assert_called()
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
