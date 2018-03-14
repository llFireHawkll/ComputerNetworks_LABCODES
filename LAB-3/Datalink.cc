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
    fromAL = gate("fromAL");
    fromPL = gate("fromPL");
    toAL = gate("toAL");
    toPL = gate("toPL");

    count = 0;
    retransmit_msg = new cMessage();
}

void Datalink::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->getArrivalGate() == fromAL)
    {
        AL_PDU* pkt = check_and_cast<AL_PDU*>(msg);
        d = new DL_PDU();

        int id = pkt->getAid();
        id = (id+1)%2;                   // Storing the node to which we have to send for ex Node0 --> Node1 so id = 1

        d->setType("DATA");
        d->setDid(id);
        d->encapsulate(pkt);

        buffer = d->dup();          // Duplicating the DL packet and storing it in temporary buffer
        Return_Node = (id+1) % 2;        // Return_node = 0 (this is only for first case just for understanding purpose)


        scheduleAt(simTime() + 10.0, retransmit_msg);

        if(uniform(0,1) < 0.3)
        {
            sendDelayed(d, simTime()+2.0, toPL);
        }
        else
        {
            sendDelayed(d, simTime()+1.0, toPL);
        }
    }

    else if(msg->getArrivalGate() == fromPL)
    {
        d = check_and_cast<DL_PDU*>(msg);

        if(strcmp(d->getType(),"DATA")== 0)
        {
            int id = d->getDid();
            id = (id+1)%2;

            DL_PDU* ack = new DL_PDU();

            ack->setType("ACK");
            ack->setDid(id);

            if(uniform(0,1) < 0.4)
            {
                sendDelayed(d->decapsulate(), simTime()+2.0, toAL);
                sendDelayed(ack, simTime()+2.0, toPL);
            }
            else
            {
                sendDelayed(d->decapsulate(), simTime()+1.0, toAL);
                sendDelayed(ack, simTime()+1.0, toPL);
            }
        }
        else
        {
            if(Return_Node == d->getDid())  // This condition says that everything went right and now do not retransmit
            {
                buffer = NULL;
                cancelEvent(retransmit_msg);
            }
            else
            {
                EV << "think";
                delete msg;
            }
        }
    }

    else if(msg->isSelfMessage())
    {
        if(msg == retransmit_msg)
        {
            EV << "Re-Transmitting Message";
            send(buffer, toPL);
        }
    }
}
