import csv
from pymodbus.client import ModbusTcpClient

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

def parse_address(address):
    """
    Parse Modbus address string to retrieve base address and offset.
    """
    base_address = int(address[3:5])  # Extract base address from %QX0.5 or %QX4.0
    offset = int(address[6])         # Extract bit offset
    return base_address, offset

# Read coils and write results to a CSV file
def read_output_coils_to_csv(output_file):
    if client.connect():
        print("Connected to Modbus server")
        with open(output_file, mode='w', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(['Description', 'Address', 'State'])  # Write header row

            for description, address in output_coil_addresses.items():
                base_address, offset = parse_address(address)
                result = client.read_coils(base_address, count=1)
                if not result.isError():
                    value = result.bits[offset]
                    state = 'ON' if value else 'OFF'
                    csv_writer.writerow([description, address, state])
                else:
                    csv_writer.writerow([description, address, 'ERROR'])

        client.close()
        print(f"Coil states written to {output_file}")
    else:
        print("Failed to connect to Modbus server")

if __name__ == '__main__':
    output_csv_file = 'coil_states.csv'  # Specify the output CSV file name
    read_output_coils_to_csv(output_csv_file)

