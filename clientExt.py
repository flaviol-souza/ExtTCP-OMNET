import socket

def main():
    # Define the server address and port to connect to
    server_address = '127.0.0.1'  # Replace with the address specified in 'addr' parameter
    server_port = 4560  # Replace with the port specified in 'port' parameter

    # Create a TCP/IP socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        try:
            # Connect to the server
            print(f"Connecting to {server_address}:{server_port}")
            sock.connect((server_address, server_port))
            print("Connected successfully")

            # Send some data to the server
            message = "Hello, OMNeT++ Server!"
            print(f"Sending: {message}")
            sock.sendall(message.encode('utf-8'))

            # Wait for a response (if any)
            response = sock.recv(1024)
            print(f"Received: {response.decode('utf-8')}")

        except ConnectionRefusedError:
            print("Connection failed. Make sure the server is running and accessible.")
        except Exception as e:
            print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()

