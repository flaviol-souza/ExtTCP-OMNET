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

#include "TCPClient.h"

Define_Module(TCPClient);

void TCPClient::initialize()
{
    addr = par("addr");
    srvAddr = par("srvAddr");

    cMessage *timer = new cMessage("timer");
    scheduleAt(simTime()+par("sendIaTime").doubleValue(), timer);
}

void TCPClient::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        simulateUserTyping();
        scheduleAt(simTime()+par("sendIaTime").doubleValue(), msg);
    }
    else
    {
        processEcho(check_and_cast<TCPPkt *>(msg));
    }
}

void TCPClient::simulateUserTyping()
{
    // send telnet packet
    TCPPkt *tcpPkt = new TCPPkt("x");
    tcpPkt->setPayload("x");
    tcpPkt->setDestAddress(srvAddr);
    tcpPkt->setSrcAddress(addr);

    send(tcpPkt,"g$o");
}

void TCPClient::processEcho(TCPPkt *tcpPkt)
{
    delete tcpPkt;
}
