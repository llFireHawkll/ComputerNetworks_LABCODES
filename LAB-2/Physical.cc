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

#include "Physical.h"

Define_Module(Physical);

void Physical::initialize()
{
    // TODO - Generated method body
    nid = par("id");
    fromDL = gate("fromDL");
    toDL = gate("toDL");
    fromNode = gate("fromNode");
    toNode = gate("toNode");
}


void Physical::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->getArrivalGate() == fromDL)
    {
        DL_PDU* pkt = check_and_cast<DL_PDU*>(msg);
        PL_PDU* pkt_new = new PL_PDU();
        pkt_new->encapsulate(pkt);
        send(pkt_new,toNode);
    }
    else if(msg->getArrivalGate() == fromNode)
    {
        PL_PDU* pkt = check_and_cast<PL_PDU*>(msg);
        DL_PDU* pkt_new = new DL_PDU();

        pkt_new = check_and_cast<DL_PDU*>(pkt->decapsulate());
        send(pkt_new, toDL);
        delete pkt;
    }
}
