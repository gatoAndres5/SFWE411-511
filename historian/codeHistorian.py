import csv
from pymodbus.client import ModbusTcpClient
import time

# Define Modbus client
client = ModbusTcpClient('127.0.0.1', port=502)  # Replace with your Modbus server IP and port

# Define output coil addresses and descriptions
output_coil_addresses = {
    'Overstay Notification': '%QX0.5',
    'Open Entry Gate': '%QX0.6',
    'Light Control (Light_ON)': '%QX4.0',
    'Exit Gate Opens': '%QX0.4',
    'Exit Gate Closes': '%QX0.9',
    'Signage Rain': '%QX2.1',
    'Signage Snow': '%QX2.2',
    'Signage Clear': '%QX2.3',
    'Parking Duration Status': '%QX3.0',
    'EV Charger Activation': '%QX6.0',
    'Ticket Validation Sensor': '%QX5.2',
    'Parking Space LED Indicator': '%QX0.7',
    'HMI Entry Display Trigger': '%QX7.0',
    'Overstay Penalty Indicator': '%QX7.1',
    'Alarm Status Indicator': '%QX7.3',
    'Lightning Status Display': '%QX7.5',
    'Exit Event Display': '%QX8.0',
    'System Health Check Display': '%QX8.2',
    'Manual Override Gate': '%QX8.3',
    'Manual Override Alarm': '%QX8.4',
    'Manual Override Light': '%QX8.5',
    'Status Sync Trigger': '%QX8.7',
    'Maintenance Mode Display': '%QX9.0',
}

# Define input addresses and descriptions
input_addresses = {
    'Entrance Gate Sensor': '%IX0.0',
    'Entrance Gate Sensor 0': '%IX0.1',
    'Ticket Validation Enter': '%IX0.2',
    'Ticket Validation Exit': '%IX0.4',
    'Physical Card Enter': '%IX0.3',
    'Physical Card Exit': '%IX0.5',
    'Permit Card Enter': '%IX0.6',
    'Permit Card Exit': '%IX1.1',
    'Open Spot Sensor': '%IX1.0',
    'Count Sensor': '%IX1.1',
    'License Plate Capture': '%IX1.0',
    'License Plate Verification': '%IX5.1',
    'Entrance Pass Through': '%IX0.8',
    'Alarm Button': '%IX5.0',
    'Light Sensor Condition': '%IW2.0',
    'Rain Sensor': '%IX2.1',
    'Snow Sensor': '%IX2.2',
    'Exit Sensor': '%IX0.4',
    'Exit Pass Through Sensor': '%IX0.8',
}

def parse_address(address):
    """
    Parse Modbus address string to retrieve base address and offset.
    """
    base_address = int(address[3:].split('.')[0])  # Extract base address before the period
    offset = int(address.split('.')[1])           # Extract bit offset after the period
    return base_address, offset

def read_addresses_to_csv(addresses, address_type, csv_writer):
    """
    Read Modbus addresses (coils or inputs) and write states to the CSV file.
    """
    for description, address in addresses.items():
        base_address, offset = parse_address(address)

        # Read coils or discrete inputs depending on address type
        if address_type == 'coil':
            result = client.read_coils(base_address, count=offset + 1)
        elif address_type == 'input':
            result = client.read_discrete_inputs(base_address, count=offset + 1)
        else:
            raise ValueError(f"Unknown address type: {address_type}")

        if not result.isError():  # Ensure no error occurred during the read
            if offset < len(result.bits):  # Check bounds
                value = result.bits[offset]
                state = 'ON' if value else 'OFF'
                csv_writer.writerow([description, address, state])
            else:
                csv_writer.writerow([description, address, 'OFFSET OUT OF RANGE'])
        else:
            csv_writer.writerow([description, address, 'READ ERROR'])

# Read coils and inputs, and write results to a CSV file
def read_modbus_addresses_to_csv(output_file, duration):
    if client.connect():
        print("Connected to Modbus server")
        start_time = time.time()
        with open(output_file, mode='w', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(['Description', 'Address', 'State'])  # Write header row
            # Initial read of coils and inputs
            read_addresses_to_csv(output_coil_addresses, 'coil', csv_writer)
            read_addresses_to_csv(input_addresses, 'input', csv_writer)

            while time.time() - start_time < duration:
                # Read output coils and input addresses every 5 seconds
                read_addresses_to_csv(output_coil_addresses, 'coil', csv_writer)
                read_addresses_to_csv(input_addresses, 'input', csv_writer)

                # Add a separator row to indicate 60 seconds have passed
                csv_writer.writerow(['---', '60 Seconds Passed', '---'])

                # Add a delay (60 seconds) before the next reading
                time.sleep(60)

        client.close()
        print(f"Modbus states written to {output_file}")
    else:
        print("Failed to connect to Modbus server")

if __name__ == '__main__':
    output_csv_file = 'modbus_states.csv'  # Specify the output CSV file name
    duration_seconds = 200  # Run for 200 seconds as an example
    read_modbus_addresses_to_csv(output_csv_file, duration_seconds)
