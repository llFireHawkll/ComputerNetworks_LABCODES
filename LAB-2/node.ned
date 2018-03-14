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

module Node
{
    parameters:
        int id;
        @display("bgb=377,299");
    gates:
        input in;
        output out;
    submodules:
        AL: Application {
            id = id;
            @display("p=32,120");
        }
        DL: Datalink {
            id = id;
            @display("p=165,120");
        }
        PL: Physical {
            id = id;
            @display("p=274,120");
        }
    connections:
        AL.toDL --> DL.fromAL;
        DL.toAL --> AL.fromDL;
        DL.toPL --> PL.fromDL;
        PL.toDL --> DL.fromPL;
        PL.toNode --> out;
        PL.fromNode <-- in;

}
