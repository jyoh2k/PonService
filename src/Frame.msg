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

//
// TODO generated message class
//

cplusplus {{
#include <queue>
typedef struct wmHeader{unsigned char msgType; unsigned char seqNum; unsigned char interfaceID; unsigned char channel; 
						unsigned char status; unsigned char recommendedID; unsigned char ONU_COUNT;} WMHeader;
typedef struct wmPayload{unsigned short ONU_ID; unsigned char responseType; unsigned char occupancy; unsigned char channel; unsigned char SLA;} WMPayload;
    						   
typedef struct emheader{int PLI; int keyIndex; unsigned short portID; bool LF; int Others;} EMHeader; // 8Bytes
typedef struct empayload{int src; int dest; long seqNum; int type; long responseBytes;}EMPayload; // 8Bytes
typedef struct em{EMHeader header; EMPayload payload;char name[100];double timeStamp;} EM; 
typedef struct bwmap{unsigned short AllocID; bool DBRu; bool PLOAMu; short startTime; unsigned short grantSize; bool FWI; short HEC;} BWMAP; //8Bytes
typedef struct ploam{unsigned short ONU_ID; unsigned char Msg_Type_ID; char SeqNo; char Msg_Contents[36]; char MIC[8];} PLOAM;	//48Bytes

typedef std::queue<WMPayload> WMPayload_Array;
typedef std::queue<BWMAP> BWMAP_ARRAY;
typedef std::queue<int> DBRU; 
typedef std::queue<EM> EM_CHUNKS;
typedef std::queue<PLOAM> PLOAM_ARRAY;
}}

class noncobject WMHeader;
class noncobject WMPayload_Array;

class noncobject EM_CHUNKS;
class noncobject BWMAP_ARRAY;
class noncobject DBRU;
class noncobject PLOAM_ARRAY;
class noncobject PLOAM;

//
// TODO generated message class
//

packet GenericFrame {
    int src;
    int dest;
    int type;
    long seqNum;
    long responseBytes;
}

packet GenericFrameWithWMControl extends GenericFrame
{
	WMHeader header;
	WMPayload_Array payload;
}

packet GenericFrameWithPHYControl extends GenericFrame
{
    int command;
    int tuningWavelength;
    double sleepTime;
    double sleepDuration;
}

packet TC
{
    int wavelength;
    int type;
    EM_CHUNKS EMs;
}

packet TC_US extends TC
{
    unsigned int ONU_ID;		// 10bits
    unsigned int Ind;			// 9bits
    unsigned int HEC;			// 13bits
    PLOAM PLOAMu; 				// 48bytes * 1 ONUs;
    DBRU DBRu;					// 4bytes * N fragmentations
}								// total 4bytes * (N+1) + payload

packet TC_DS extends TC
{
    unsigned int BWmapLength;	// 11bits
    unsigned int PLOAMcount;	// 8bits
    unsigned int HEC;			// 13bits
    BWMAP_ARRAY BWMAPs;			// 8bytes * N Allocations (ONU : Allocations = 1:1)
    PLOAM_ARRAY PLOAMd;  		// 48bytes * P ONUs;
}								// total 4bytes * (2N+1) + 48bytes * P ONUs + payload


