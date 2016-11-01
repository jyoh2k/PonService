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

#ifndef COMMON_H_
#define COMMON_H_

#define DEBUG 1
//Message types
enum Types {GENERIC_FRAME = 0, REQ, REP, CONN, ACCEPT, NOTACCEPT, NOTIFY, FIN,
            GENERIC_CONTROL_FRAME=10,
            EM_FRAME = 20,
            TC_FRAME = 30, TC_US_FRAME, TC_DS_FRAME};

//Message flag
enum Commands {OLT_MANAGEMENT_COMMAND_SUCCESS = 10, OLT_SLEEP, OLT_WAKEUP, OLT_MONITORING,
               ONU_MANAGEMENT_COMMAND_SUCCESS = 20, ONU_SLEEP, ONU_DOZE, ONU_WAKEUP, ONU_TUNING};

//PHY interface status
enum Status {POWER_OFF = 0, RUNNING, TUNING};

//OLT state
enum OLT_STATE {OLT_INITIAL_STATE = 0, OLT_SN_QUIET, OLT_RANGING_QUIET0, OLT_RANGING_QUIET1, OLT_OPERATION_STATE, OLT_SLEEP_READY, OLT_SLEEP_STATE};

//ONU state
enum ONU_STATE {ONU_INITIAL_STATE0 = 0, ONU_INITIAL_STATE1, ONU_INITIAL_TUNING_STATE0, ONU_INITIAL_TUNING_STATE1,
                ONU_SN_STATE0, ONU_SN_STATE1, ONU_RANGING_STATE0, ONU_RANGING_STATE1, ONU_OPERATION_STATE, ONU_TUNING_STATE, ONU_ILODS_STATE, ONU_EMERGENCY_STATE};

#define MAX_INTERFACE_NUM 8

//PLOAM Message ID (for downstream)
#define PROFILE                 0x01
#define ASSIGN_ONU_ID           0x03
#define RANGING_TIME            0x04
#define DEACTIVATE_ONU_ID       0x05
#define DISABLE_SN              0x06
#define REQ_REGISTRATION        0x09
#define ASSIGN_ALLOC_ID         0x0A
#define KEY_CTRL                0x0D
#define SLEEP_ALLOW             0x12
//for PON
#define WAVE_TUNING             0x20
#define WAVE_CONFIRM            0x21
#define COMELETION_D            0x22

//PLOAM Message ID (for upstream)
#define SN_ONU                  0x01
#define REGISTRATION            0x02
#define KEY_REPORT              0x05
#define ACK                     0x09
#define SLEEP_REQ               0x10
//for PON
#define WAVE_TUNING_ACK         0x23
#define WAVE_TUNING_RESPONSE    0x24

//OLT state machine code
#define OLT_NOTHING                 0x0000
#define DS_GENERATION               0x0001
#define MAKE_SN_QUIET_WINDOW        0x0002
#define CLOSE_SN_QUIET_WINDOW       0x0004
#define MAKE_RANGING_QUIET_WINDOW   0x0008
#define CLOSE_RANGING_QUIET_WINDOW  0x0010
#define DBA_PROCESSING              0x0020
#define NEW_ONU_REGISTER            0x0040
#define CAPACITY_OVERFLOW_WARNING   0x0080
#define CAPACITY_UNDERFLOW_WARNING  0x0100
#define INTERFACE_SLEEP             0x0200
#define INTERFACE_WAKEUP            0x0400
#define WM_REPORT_REQUEST           0x0800
#define WM_UPDATE_REQUEST           0x1000

//ONU state machine code
#define NOTHING                 0x0000
#define DS_SYNC                 0x0001
#define BURST_PROFILE           0x0002
#define QUIET_GRANT             0x0004
#define ASSIGN_ID               0x0008
#define RANGING_ACK             0x0010
#define BW_ALLOCATION           0x0020
#define TUNING_READY            0x0040
#define TUNING_COMPLETION       0x0080
#define TUNING_CONFIRM          0x0100
#define TIMEOUT                 0x0200
#define STATE_FAIL              0x0400

//Message Header Flag
#define ERROR_FLAG          0x01
#define ACK_FLAG            0x02
#define TUNING_FLAG         0x04

#define BROADCAST_ONU_ID    0x03FF

//Related energy consumption (percentage)
#define ACTIVECONSUMPTION   100.0
#define DOZECONSUMPTION     50.0
#define SLEEPCONSUMPTION    10.0

#define SLA_HIGH            6000
#define SLA_MEDIUM_DAY      6000
#define SLA_MEDIUM_NIGHT    1500
#define SLA_LOW             1500

#define UPPER_THRESHOLD     0.8
#define LOWER_THRESHOLD     0.2
#define MAXBW_SLA_RATIO     1.5

#define EM_HEADER_SIZE              8       //Bytes

#define MAX_REPLY_CHUNK_SIZE        1500    //Bytes
#define MAX_EM_PAYLOAD_SIZE         16383   //Bytes
#define MAX_TC_DOWNSTREAM_SIZE      135432  //Bytes

#define PSBd_SIZE                   24      //Bytes
#define MAX_PHY_PAYLOADd_SIZE       155496  //Bytes
#define MAX_PHY_DOWNSTREAM_SIZE     (MAX_PHY_PAYLOADd_SIZE+PSBd_SIZE)  //Bytes

#define GUARD_TIME                  8       //Bytes
#define MAX_PHY_PAYLOADu_SIZE       38872   //Bytes
#define MAX_PHY_UPSTREAM_SIZE       (MAX_PHY_PAYLOADd_SIZE+GUARD_TIME)  //Bytes

#define US_TRANSMISSION_RATE        2488320000.0
#define DS_TRANSMISSION_RATE        9953280000.0

#endif

