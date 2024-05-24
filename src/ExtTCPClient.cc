//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "ExtTCPClient.h"

Define_Module(ExtTCPClient);

ExtTCPClient::ExtTCPClient()
{
    rtEvent = NULL;
}

ExtTCPClient::~ExtTCPClient()
{
    cancelAndDelete(rtEvent);
}

void ExtTCPClient::initialize()
{
    rtEvent = new cMessage("rtEvent");
    rtScheduler = check_and_cast<cSocketRTScheduler *>(simulation.getScheduler());
    rtScheduler->setInterfaceModule(this, rtEvent, recvBuffer, 4000, &numRecvBytes);

    addr = par("addr");
    srvAddr = par("srvAddr");
}

void ExtTCPClient::handleMessage(cMessage *msg)
{
    if (msg==rtEvent)
        handleSocketEvent();
    else
        handleReply(check_and_cast<TCPPkt *>(msg));
}

void ExtTCPClient::handleSocketEvent()
{
    // get data from buffer
    std::string text = std::string(recvBuffer, numRecvBytes);
    numRecvBytes = 0;

    // assemble and send Telnet packet
    TCPPkt *tcpPkt = new TCPPkt();
    tcpPkt->setPayload(text.c_str());
    tcpPkt->setName(text.c_str());
    tcpPkt->setDestAddress(srvAddr);
    tcpPkt->setSrcAddress(addr);

    send(tcpPkt,"g$o");
}

void ExtTCPClient::handleReply(TCPPkt *tcpReply)
{
    const char *reply = tcpReply->getPayload();
    rtScheduler->sendBytes(reply, strlen(reply));
    delete tcpReply;
}
