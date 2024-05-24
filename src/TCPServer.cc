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

#include <ctype.h>
#include "TCPServer.h"
#include "TCPPkt_m.h"


Define_Module(TCPServer);

simtime_t TCPServer::startService(cMessage *msg)
{
    EV << "Starting service of " << msg->getName() << endl;
    return par("serviceTime").doubleValue();
}

void TCPServer::endService(cMessage *msg)
{
    EV << "Completed service of " << msg->getName() << endl;

    TCPPkt *tcpPkt = check_and_cast<TCPPkt *>(msg);

    std::string reply = processChars(tcpPkt->getPayload());
    tcpPkt->setPayload(reply.c_str());
    tcpPkt->setName(reply.c_str());

    int clientAddr = tcpPkt->getSrcAddress();
    int srvAddr = tcpPkt->getDestAddress();
    tcpPkt->setDestAddress(clientAddr);
    tcpPkt->setSrcAddress(srvAddr);

    send(msg, "g$o");
}

std::string TCPServer::processChars(const char *chars)
{
    std::string s = chars;
    for (unsigned int i = 0; i < s.length(); i++)
        s.at(i) = toupper(s.at(i));
    return s;
}
