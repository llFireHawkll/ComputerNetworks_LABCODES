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

#include "node.h"

Define_Module(Node);

void Node::initialize()
{
    // TODO - Generated method body
    inG = gate("in");
    outG = gate("out");
    addr = par("id");
    if(addr==1)
    {
        cMessage* m = new cMessage();
        scheduleAt(1,m);
    }
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage())
    {
        Packet* newmsg = new Packet();
        newmsg->setSrc_addr(1);
        newmsg->setDest_addr(2);
        newmsg->setType(1);
        send(newmsg,outG);
    }
    else
    {
        Packet* premsg = check_and_cast<Packet*>(msg);
        if(premsg->getType()==1)
        {
            Packet* newmsg = new Packet();
            newmsg->setId(premsg->getId());
            newmsg->setType(2);
            newmsg->setSrc_addr(addr);
            newmsg->setDest_addr(premsg->getSrc_addr());
            send(newmsg,outG);

        }
        else
        {
            count++;
            if(count < 10)
            {
                Packet* newmsg = new Packet();
                newmsg->setId(premsg->getId());
                newmsg->setType(1);
                newmsg->setSrc_addr(addr);
                newmsg->setDest_addr(premsg->getSrc_addr());
                send(newmsg,outG);
            }
        }

    }
}
