import csv
from datetime import datetime
from pymodbus.client import ModbusTcpClient

# Define the Modbus server details
MODBUS_SERVER_IP = '10.100.16.128'  # Replace with the actual IP
MODBUS_SERVER_PORT = 502           # Default Modbus TCP port

# Define CSV file for logging
CSV_FILE = 'modbus_operations_log.csv'

# Initialize CSV file and write headers if it doesn't exist
def initialize_csv(file_path):
    try:
        with open(file_path, mode='x', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Timestamp", "Operation", "Address", "Value", "Status", "Remarks"])
    except FileExistsError:
        # If the file already exists, do nothing
        pass

# Log an operation to the CSV file
def log_operation(operation, address, value, status, remarks=""):
    with open(CSV_FILE, mode='a', newline='') as file:
        writer = csv.writer(file)
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        writer.writerow([timestamp, operation, address, value, status, remarks])

# Main function to collect and document operations
def main():
    client = ModbusTcpClient(MODBUS_SERVER_IP, port=MODBUS_SERVER_PORT)
    if client.connect():
        print("Connected to Modbus server.")
        log_operation("Connect", "N/A", "N/A", "Success", "Connected to Modbus server")

        try:
            # Example: Reading coil at address 0
            address = 0
            print(f"Reading coil at address {address}...")
            response = client.read_coils(address, 1)
            if response.isError():
                log_operation("Read Coil", address, "N/A", "Failure", "Error reading coil")
            else:
                value = response.bits[0]
                print(f"Value at coil {address}: {value}")
                log_operation("Read Coil", address, value, "Success", "Successfully read coil")

            # Example: Writing to a coil
            address = 1
            value_to_write = False  # Turn off the coil
            print(f"Writing {value_to_write} to coil at address {address}...")
            response = client.write_coil(address, value_to_write)
            if response.isError():
                log_operation("Write Coil", address, value_to_write, "Failure", "Error writing to coil")
            else:
                log_operation("Write Coil", address, value_to_write, "Success", "Successfully wrote to coil")

        except Exception as e:
            print(f"An error occurred: {e}")
            log_operation("Exception", "N/A", "N/A", "Failure", str(e))
        finally:
            client.close()
            log_operation("Disconnect", "N/A", "N/A", "Success", "Disconnected from Modbus server")
    else:
        print("Failed to connect to Modbus server.")
        log_operation("Connect", "N/A", "N/A", "Failure", "Failed to connect to Modbus server")

if __name__ == "__main__":
    # Initialize CSV file
    initialize_csv(CSV_FILE)
    # Run the main function
    main()
