# ExtTCP-OMNET Simulation Project

This project provides an example of simulating TCP connections in OMNeT++ 4.6 using the INET Framework (20110921). The purpose of this simulation is to model a TCP-based client-server architecture with an external Python script acting as a TCP client.
![Simulation Example](figures/simulation_example.png)

## Project Purpose

The primary goal of this project is to demonstrate how to simulate TCP connections using OMNeT++ and the INET framework. This simulation includes a TCP server and a client within OMNeT++ and extends to an external TCP client implemented in Python.

## Requirements

- **OMNeT++ 4.6**: [Download OMNeT++ 4.6](https://omnetpp.org/omnetpp/doc_details/2295-omnet-4-6-source-tgz)
- **INET Framework (20111118)**: [Download INET 20111118](https://inet.omnetpp.org/Download.html)

## Installation and Setup

### Step 1: Install OMNeT++

1. Download and install OMNeT++ 4.6 from the provided link.
2. Follow the installation instructions in the OMNeT++ documentation.

### Step 2: Install INET Framework

1. Download INET 20110921 from the provided link.
2. Extract the INET framework into the OMNeT++ workspace.
3. Open the OMNeT++ IDE, import the INET project, and build it.

### Step 3: Clone the extTCP Project

Clone the project repository from GitHub:

```sh
git clone https://github.com/flaviol-souza/ExtTCP-OMNET
```

### Step 4: Build the Project

1. Open the OMNeT++ IDE.
2. Import the `ExtTCP-OMNET` project.
3. Build the project by right-clicking on the project and selecting `Build Project`.

## Configuration

Modify the `omnetpp.ini` file to match your network configuration:

```ini
[General]
scheduler-class = "cSocketRTScheduler"
network = ExtClient

cmdenv-express-mode = true
tkenv-default-run = 0

**.testing = false
**.testTimeout = 0

**.peer.numSctpApps=2
**.peer.sctpAppType="SCTPServer"
**.peer.sctpApp[0].address="10.1.1.1"
**.peer.sctpApp[0].port=7
**.peer.sctpApp[1].port=9
**.peer.sctpApp[0].numPacketsToReceive = 0
**.peer.sctpApp[0].waitToClose = 0s
**.peer.sctpApp[0].idleInterval = truncnormal(1,1)
**.peer.sctpApp[0].queueSize = 0
**.peer.sctpApp[0].replyDelay=0
**.peer.sctpApp[0].echoDelay=0
**.peer.sctpApp[0].echoFactor=1
**.peer.sctpApp[0].numPacketsToReceivePerClient = 0

**.tcpdump.dumpFile=""

**.ext[0].filterString = "(sctp or icmp) and ip dst host 10.1.1.1"
**.ext[0].device = "lo"
```

Ensure that `**.ext[0].device` is set to your network interface (e.g., `lo` for loopback).

## Running the Simulation

1. Start the OMNeT++ IDE.
2. Load and run the simulation by selecting the appropriate run configuration.
3. Observe the simulation using the graphical interface.

## External Client Script

The project includes a Python script to act as an external TCP client. To run the Python script:

```sh
python3 clientExt.py
```

This script will connect to the TCP server simulated in OMNeT++, send a message, and print the received response.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
