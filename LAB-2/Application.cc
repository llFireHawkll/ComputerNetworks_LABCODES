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

#include "Application.h"

Define_Module(Application);

void Application::initialize()
{
    // TODO - Generated method body
    nid = par("id");
    fromDL = gate("fromDL");
    toDL = gate("toDL");
    count = 1;

    if(nid == 1)
    {
        cMessage* event = new cMessage();
        scheduleAt(0,event);

    }
}

void Application::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg -> isSelfMessage())
    {
        AL_PDU* pkt = new AL_PDU();
        pkt->setId(count);
        pkt->setMsg(0);
        count++;
        send(pkt,toDL);
    }
    else if(msg->getArrivalGate() == fromDL)
    {
        AL_PDU* Apkt=check_and_cast<AL_PDU*>(msg);

        if(Apkt->getMsg() == 0)
        {
            AL_PDU* Ack=new AL_PDU();
            Ack->setMsg(1);
            Ack->setId(Apkt->getId());
            send(Ack,toDL);
        }
        else if(Apkt->getMsg() == 1)
        {
            if(count<11)
            {
                 AL_PDU* Apkt=new AL_PDU();
                 Apkt->setMsg(0);
                 Apkt->setId(count);
                 count++;
                 send(Apkt,toDL);
             }
        }
    }
}
