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
#include "string.h"

Define_Module(Application);

void Application::initialize()
{
    // TODO - Generated method body

    fromDL = gate("fromDL");
    toDL = gate("toDL");
    id = par("aid");
    count = par("count");

    int i;
    char c = 'A';

    for(i=0; i<26; i++)
    {
        packets[i] = new AL_PDU();
        packets[i]->setAid(i);
        packets[i]->setType("DATA");
        packets[i]->setData(char(c));
        c++;
    }

    if(id == 1)
    {
        cMessage* event = new cMessage();
        scheduleAt(0, event);
    }
}

void Application::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    if(msg -> isSelfMessage())
    {
        send(packets[0], toDL);
        count = 1;
    }
    else
    {
        AL_PDU* pkt = check_and_cast<AL_PDU*>(msg);

        if(strcmp(pkt->getType(),"DATA") == 0)
        {
            AL_PDU* pkt = new AL_PDU();
            pkt->setType("ACK");            //Sending Ack
            send(pkt, toDL);
        }
        else
        {
            if(count < 26)                 //else Sending Data
            {
                send(packets[count], toDL);
                count++;
            }
        }
    }
}
