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

#include "Datalink.h"

Define_Module(Datalink);

void Datalink::initialize()
{
    // TODO - Generated method body
    nid = par("id");
    fromAL = gate("fromAL");
    toAL = gate("toAL");
    fromPL = gate("fromPL");
    toPL = gate("toPL");
}

void Datalink::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if (msg->getArrivalGate() == fromAL)
    {
        AL_PDU* pkt = check_and_cast<AL_PDU*>(msg);
        DL_PDU* pkt_new = new DL_PDU();

        pkt_new->encapsulate(pkt);
        pkt_new->setMsg(0);
        pkt_new->setId((pkt->getId()-1) % 2);

        send(pkt_new,toPL);
    }

    else if(msg->getArrivalGate() == fromPL)
    {
       DL_PDU* pkt=check_and_cast<DL_PDU*>(msg);

       if(pkt->getMsg() == 0)
       {
           AL_PDU* pkt_new = new AL_PDU();
           pkt_new = check_and_cast<AL_PDU*>(pkt->decapsulate());

           DL_PDU* Ack = new DL_PDU();
           Ack->setMsg(1);
           Ack->setId(pkt_new->getId());

           send(Ack,toPL);

           send(pkt_new,toAL);

       }
       else if(pkt->getMsg() == 1)
       {
             delete(pkt);
       }
    }
}
