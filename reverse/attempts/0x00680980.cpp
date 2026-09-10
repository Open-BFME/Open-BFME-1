// ?getCommandList@NetPacket@@QAEPAVNetCommandList@@XZ
// partial score=0.84 date=2026-09-07
// cl: /DNDEBUG /MD /EHsc
// BANK: complete BFME getCommandList parser, RVA 0x00680980, retail1380B.
// Caller Connection::sendNetCommandMsg at0x006625E5 and relay pass0x0066A8F6
// reach ILT0x0001AB3B. All28 readers and ACK constructors/setters have matched
// named bodies. Type23 and unsupported types stop parsing; unknown wire tags
// call dumpPacketToLog then advance. Z repeats only ACK1/ACK2/ACKBOTH, retaining
// the original execution-frame word at+0x20 and incrementing the ACK ID.
// A32-bit commandID starts0; C copies only its low16bits and sets a byteflag.
// Only commands requiring IDs increment it if C was absent; the flag clears
// after either a D or Z command. New list calls reset, not reference init.
//
// Byte proof is NOT exact. Original declaration-only reconstruction is1417B
// executable+3Bpadding+116Bswitchtable=1536B object span; earlier RE notes
// miscounted that table as executable code. Named data base and reading header
// bytes before advancing i yield1401B code+3Bpadding+116Btable=1520B span.
// Register/local lifetimes still
// differ from retail. No matched progress is claimed for this bank.
#include <string.h>
#define NULL 0
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
enum NetCommandType {
    NETCOMMANDTYPE_ACKBOTH = 0,
    NETCOMMANDTYPE_ACKSTAGE1 = 1,
    NETCOMMANDTYPE_ACKSTAGE2 = 2,
    NETCOMMANDTYPE_FRAMEINFO = 3,
    NETCOMMANDTYPE_GAMECOMMAND = 4,
    NETCOMMANDTYPE_REQUESTGAMESPYSTATSAUTHKEY = 5,
    NETCOMMANDTYPE_GAMESPYSTATSAUTHKEY = 6,
    NETCOMMANDTYPE_REQUESTPLAYERLEAVE = 7,
    NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
    NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
    NETCOMMANDTYPE_PLAYERLEAVE = 10,
    NETCOMMANDTYPE_DESTROYPLAYER = 11,
    NETCOMMANDTYPE_KEEPALIVE = 12,
    NETCOMMANDTYPE_DISCONNECTCHAT = 13,
    NETCOMMANDTYPE_CHAT = 14,
    NETCOMMANDTYPE_PROGRESS = 15,
    NETCOMMANDTYPE_LOADCOMPLETE = 16,
    NETCOMMANDTYPE_TIMEOUTSTART = 17,
    NETCOMMANDTYPE_WRAPPER = 18,
    NETCOMMANDTYPE_FILE = 19,
    NETCOMMANDTYPE_FILEANNOUNCE = 20,
    NETCOMMANDTYPE_FILEPROGRESS = 21,
    NETCOMMANDTYPE_ROUTERFALLBACK = 22,
    NETCOMMANDTYPE_DISCONNECTSTART = 23,
    NETCOMMANDTYPE_DISCONNECTKEEPALIVE = 24,
    NETCOMMANDTYPE_DISCONNECTPLAYER = 25,
    NETCOMMANDTYPE_DISCONNECTVOTE = 26,
    NETCOMMANDTYPE_DISCONNECTFRAME = 27,
    NETCOMMANDTYPE_DISCONNECTSCREENOFF = 28
};
#define TRUE true
#define FALSE false
class NetCommandMsg {
public:
    void setExecutionFrame(unsigned int n) {m_frame=n;}
    void setID(unsigned short n) {m_id=n;}
    void setPlayerID(unsigned int n) {m_player=n;}
    void setNetCommandType(NetCommandType n) {m_type=n;}
    void detach();
private:
    void *m_vptr;
    unsigned int m_timestamp;
    unsigned int m_frame;
    unsigned int m_player;
    unsigned short m_id;
    NetCommandType m_type;
    int m_referenceCount;
};
class NetCommandRef {
public:
    NetCommandRef(NetCommandMsg *msg);
    ~NetCommandRef();
    NetCommandMsg *getCommand() {return m_msg;}
    void setRelay(unsigned char relay) {m_relay=relay;}
private:
    NetCommandMsg *m_msg;
    NetCommandRef *m_next;
    NetCommandRef *m_prev;
    unsigned char m_relay;
    unsigned int m_timeLastSent;
};
class NetCommandList {
public: NetCommandList(); void reset(); NetCommandRef *addMessage(NetCommandMsg*);
private: void *vptr; NetCommandRef *first,*last,*lastInserted;
};
Bool DoesCommandRequireACommandID(NetCommandType);
class NetAckStage1CommandMsg : public NetCommandMsg {
public:
    NetAckStage1CommandMsg();
    UnsignedShort getCommandID(); void setCommandID(UnsignedShort);
    UnsignedByte getOriginalPlayerID(); void setOriginalPlayerID(UnsignedByte);
    UnsignedShort commandID; UnsignedByte originalPlayer; unsigned m_originalExecutionFrame;
};
class NetAckStage2CommandMsg : public NetCommandMsg {
public:
    NetAckStage2CommandMsg();
    UnsignedShort getCommandID(); void setCommandID(UnsignedShort);
    UnsignedByte getOriginalPlayerID(); void setOriginalPlayerID(UnsignedByte);
    UnsignedShort commandID; UnsignedByte originalPlayer; unsigned m_originalExecutionFrame;
};
class NetAckBothCommandMsg : public NetCommandMsg {
public:
    NetAckBothCommandMsg();
    UnsignedShort getCommandID(); void setCommandID(UnsignedShort);
    UnsignedByte getOriginalPlayerID(); void setOriginalPlayerID(UnsignedByte);
    UnsignedShort commandID; UnsignedByte originalPlayer; unsigned m_originalExecutionFrame;
};
class NetPacket {
public:
    NetCommandList *getCommandList();
    void dumpPacketToLog();
    void *vptr; UnsignedByte m_packet[0x1DC];Int m_packetLen;
protected:
    static NetCommandMsg *readGameMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readAckBothMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readAckStage1Message(unsigned char *data, int &offset);
    static NetCommandMsg *readAckStage2Message(unsigned char *data, int &offset);
    static NetCommandMsg *readFrameMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readRouterFallbackMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readPlayerLeaveMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readDestroyPlayerMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readKeepAliveMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readDisconnectKeepAliveMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readDisconnectPlayerMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readDisconnectChatMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readDisconnectVoteMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readChatMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readProgressMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readLoadCompleteMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readTimeOutGameStartMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readWrapperMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readFileMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readFileAnnounceMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readFileProgressMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readInformPlayerLeaveFrameMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readRequestPlayerLeaveMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readRequestFrameDataMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readDisconnectFrameMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readDisconnectScreenOffMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readRequestGameSpyStatsAuthKeyMessage(unsigned char *data, int &offset);
    static NetCommandMsg *readGameSpyStatsAuthKeyMessage(unsigned char *data, int &offset);
};
NetCommandList *NetPacket::getCommandList()
{
    NetCommandList *retval = new NetCommandList;
    retval->reset();
    UnsignedByte commandType = 0;
    UnsignedInt frame = 0;
    UnsignedByte playerID = 0;
    UnsignedByte relay = 0;
    UnsignedInt commandID = 0;
    Bool commandIDWasRead = false;
    NetCommandRef *lastCommand = NULL;
    Int i = 0;
    while (i < m_packetLen) {
        if (m_packet[i] == 'T') {
            UnsignedByte value; memcpy(&value,m_packet+i+1,sizeof(UnsignedByte)); ++i; memcpy(&commandType,&value,sizeof(UnsignedByte)); i += sizeof(UnsignedByte);
        } else if (m_packet[i] == 'F') {
            UnsignedInt value; memcpy(&value,m_packet+i+1,sizeof(UnsignedInt)); ++i; memcpy(&frame,&value,sizeof(UnsignedInt)); i += sizeof(UnsignedInt);
        } else if (m_packet[i] == 'P') {
            UnsignedByte value; memcpy(&value,m_packet+i+1,sizeof(UnsignedByte)); ++i; memcpy(&playerID,&value,sizeof(UnsignedByte)); i += sizeof(UnsignedByte);
        } else if (m_packet[i] == 'R') {
            UnsignedByte value; memcpy(&value,m_packet+i+1,sizeof(UnsignedByte)); ++i; memcpy(&relay,&value,sizeof(UnsignedByte)); i += sizeof(UnsignedByte);
        } else if (m_packet[i] == 'C') {
            UnsignedShort value; memcpy(&value,m_packet+i+1,sizeof(UnsignedShort)); ++i; memcpy(&commandID,&value,sizeof(UnsignedShort)); i += sizeof(UnsignedShort);
            commandIDWasRead = true;
        } else if (data[i] == 'D') {
            ++i;
            NetCommandMsg *msg = NULL;
            switch ((NetCommandType)commandType) {
            case NETCOMMANDTYPE_GAMECOMMAND:msg = readGameMessage(data,i);break;
            case NETCOMMANDTYPE_ACKBOTH:msg = readAckBothMessage(data,i);break;
            case NETCOMMANDTYPE_ACKSTAGE1:msg = readAckStage1Message(data,i);break;
            case NETCOMMANDTYPE_ACKSTAGE2:msg = readAckStage2Message(data,i);break;
            case NETCOMMANDTYPE_FRAMEINFO:msg = readFrameMessage(data,i);break;
            case NETCOMMANDTYPE_ROUTERFALLBACK:msg = readRouterFallbackMessage(data,i);break;
            case NETCOMMANDTYPE_PLAYERLEAVE:msg = readPlayerLeaveMessage(data,i);break;
            case NETCOMMANDTYPE_DESTROYPLAYER:msg = readDestroyPlayerMessage(data,i);break;
            case NETCOMMANDTYPE_KEEPALIVE:msg = readKeepAliveMessage(data,i);break;
            case NETCOMMANDTYPE_DISCONNECTKEEPALIVE:msg = readDisconnectKeepAliveMessage(data,i);break;
            case NETCOMMANDTYPE_DISCONNECTPLAYER:msg = readDisconnectPlayerMessage(data,i);break;
            case NETCOMMANDTYPE_DISCONNECTCHAT:msg = readDisconnectChatMessage(data,i);break;
            case NETCOMMANDTYPE_DISCONNECTVOTE:msg = readDisconnectVoteMessage(data,i);break;
            case NETCOMMANDTYPE_CHAT:msg = readChatMessage(data,i);break;
            case NETCOMMANDTYPE_PROGRESS:msg = readProgressMessage(data,i);break;
            case NETCOMMANDTYPE_LOADCOMPLETE:msg = readLoadCompleteMessage(data,i);break;
            case NETCOMMANDTYPE_TIMEOUTSTART:msg = readTimeOutGameStartMessage(data,i);break;
            case NETCOMMANDTYPE_WRAPPER:msg = readWrapperMessage(data,i);break;
            case NETCOMMANDTYPE_FILE:msg = readFileMessage(data,i);break;
            case NETCOMMANDTYPE_FILEANNOUNCE:msg = readFileAnnounceMessage(data,i);break;
            case NETCOMMANDTYPE_FILEPROGRESS:msg = readFileProgressMessage(data,i);break;
            case NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME:msg = readInformPlayerLeaveFrameMessage(data,i);break;
            case NETCOMMANDTYPE_REQUESTPLAYERLEAVE:msg = readRequestPlayerLeaveMessage(data,i);break;
            case NETCOMMANDTYPE_REQUESTFRAMEDATA:msg = readRequestFrameDataMessage(data,i);break;
            case NETCOMMANDTYPE_DISCONNECTFRAME:msg = readDisconnectFrameMessage(data,i);break;
            case NETCOMMANDTYPE_DISCONNECTSCREENOFF:msg = readDisconnectScreenOffMessage(data,i);break;
            case NETCOMMANDTYPE_REQUESTGAMESPYSTATSAUTHKEY:msg = readRequestGameSpyStatsAuthKeyMessage(data,i);break;
            case NETCOMMANDTYPE_GAMESPYSTATSAUTHKEY:msg = readGameSpyStatsAuthKeyMessage(data,i);break;
            }
            if (!msg)break;
            msg->setExecutionFrame(frame);
            msg->setPlayerID(playerID);
            msg->setNetCommandType((NetCommandType)commandType);
            if (DoesCommandRequireACommandID((NetCommandType)commandType)) {
                if (!commandIDWasRead)++commandID;
                msg->setID(commandID);
            }
            commandIDWasRead = false;
            NetCommandRef *ref = retval->addMessage(msg);
            if (ref)ref->setRelay(relay);
            if(lastCommand){delete lastCommand;lastCommand=NULL;}
            lastCommand = new NetCommandRef(msg);
            msg->detach();
        } else if(m_packet[i]=='Z') {
            ++i;
            if (!lastCommand)break;
            NetCommandMsg *msg=NULL;
            unsigned originalExecutionFrame;
            if (commandType==NETCOMMANDTYPE_ACKSTAGE1) {
                msg = new NetAckStage1CommandMsg;
                NetAckStage1CommandMsg *last=(NetAckStage1CommandMsg*)lastCommand->getCommand();
                ((NetAckStage1CommandMsg*)msg)->setCommandID(last->getCommandID()+1);
                ((NetAckStage1CommandMsg*)msg)->setOriginalPlayerID(last->getOriginalPlayerID());
                originalExecutionFrame=last->m_originalExecutionFrame;
            } else if (commandType==NETCOMMANDTYPE_ACKSTAGE2) {
                msg = new NetAckStage2CommandMsg;
                NetAckStage2CommandMsg *last=(NetAckStage2CommandMsg*)lastCommand->getCommand();
                ((NetAckStage2CommandMsg*)msg)->setCommandID(last->getCommandID()+1);
                ((NetAckStage2CommandMsg*)msg)->setOriginalPlayerID(last->getOriginalPlayerID());
                originalExecutionFrame=last->m_originalExecutionFrame;
            } else if (commandType==NETCOMMANDTYPE_ACKBOTH) {
                msg = new NetAckBothCommandMsg;
                NetAckBothCommandMsg *last=(NetAckBothCommandMsg*)lastCommand->getCommand();
                ((NetAckBothCommandMsg*)msg)->setCommandID(last->getCommandID()+1);
                ((NetAckBothCommandMsg*)msg)->setOriginalPlayerID(last->getOriginalPlayerID());
                originalExecutionFrame=last->m_originalExecutionFrame;
            } else break;
            ((NetAckBothCommandMsg*)msg)->m_originalExecutionFrame=originalExecutionFrame;
            msg->setExecutionFrame(frame);
            msg->setPlayerID(playerID);
            msg->setNetCommandType((NetCommandType)commandType);
            if (DoesCommandRequireACommandID((NetCommandType)commandType)) {
                if (!commandIDWasRead)++commandID;
                msg->setID(commandID);
            }
            commandIDWasRead = false;
            NetCommandRef *ref = retval->addMessage(msg);
            if(ref)ref->setRelay(relay);
            delete lastCommand;
            lastCommand=NULL;
            lastCommand = new NetCommandRef(msg);
            msg->detach();
        } else {
            dumpPacketToLog();
            ++i;
        }
    }
    if(lastCommand){delete lastCommand;lastCommand=NULL;}
    return retval;
}
