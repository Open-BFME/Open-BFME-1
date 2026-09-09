// ?ConstructNetCommandMsgFromRawData@NetPacket@@SAPAVNetCommandRef@@PAEG@Z
// partial score=0.88 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// BANKED RECONSTRUCTION: instruction shape is not yet exact (944 vs 940 B).
// Real body RVA 0x0067EE40 ends at 0x0067F1EB inclusive. Ghidra's 937-byte
// extent truncates the last add esp,0x24; ret epilogue (actual size 940).
// NetCommandWrapperList::getReadyCommands calls the parser through ILT
// 0x00048301. The old same-name claim at 0x00682FF0 is a string-name mapper.
//
// Retail dispatch and every reader destination were independently decoded.
// All 28 reader names below already have matched bodies. BFME has no parser
// case for disconnect-start marker 23, no ZH run-ahead or router-query/ack
// readers; router fallback plans, leave coordination, and auth keys replace them.
// Default type is ACKBOTH (0), not the reference's GAMECOMMAND (4). Unknown
// command types and null reader results return null before metadata/ref creation.
//
// PROGRESS 2026-09-09: moving `offset = payloadOffset;` before `msg->detach();`
// (instead of after) took this from 946 B to 944 B and fixed the historical
// AL-vs-CL wall -- the tag-byte compares now correctly encode as 2-byte
// `cmp al,imm8` forms in both retail and ours. Remaining wall is a pure
// register-role permutation in the prologue: retail assigns ESI=offset,
// EDI=data, EBP=commandType (all persistent across the whole function); ours
// assigns EDI=offset, EBP=data, EBX=commandType -- a 3-cycle rotation of the
// same three roles among esi/edi/ebp/ebx, plus one now-genuinely-unused `push
// esi`. The 4 extra bytes are ModRM/SIB cost from using EBP as a base register
// in [base+index] byte loads (mov al,[edi+ebp] needs a disp8 retail's
// [esi+edi] form doesn't). Tried: reordering offset/commandType/ref
// declarations to the top in various orders (no byte movement at all, same
// 944 B and same first diff) on top of the detach reorder. Header
// declaration-order, local tag, enum type, ref destructor, /Ob1, and /G5-/G6
// variants (prior session) made no byte progress either. Next lever to try:
// force EBP out of contention for the data pointer by giving `data` its own
// named local used only inside the tag-dispatch loop (mirroring
// while-form-picks-ebx / separate-loop-counter-shrink-wraps), or split
// `offset`'s role so the loop-body cursor and the post-loop payloadOffset
// are visibly different lifetimes.
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
    void setRelay(unsigned char relay) {m_relay=relay;}
private:
    NetCommandMsg *m_msg;
    NetCommandRef *m_next;
    NetCommandRef *m_prev;
    unsigned char m_relay;
    unsigned int m_timeLastSent;
};
class NetPacket {
public:
    static NetCommandRef *ConstructNetCommandMsgFromRawData(unsigned char *data,unsigned short length);
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
NetCommandRef * NetPacket::ConstructNetCommandMsgFromRawData(UnsignedByte *data, UnsignedShort dataLength) {
	NetCommandType commandType = NETCOMMANDTYPE_ACKBOTH;
	UnsignedShort commandID = 0;
	UnsignedInt frame = 0;
	UnsignedByte playerID = 0;
	UnsignedByte relay = 0;

	Int offset = 0;
	Bool notDone = TRUE;
	NetCommandRef *ref = NULL;

	while ((offset < (Int)dataLength) && notDone) {
		if (data[offset] == 'T') {
			++offset;
			memcpy(&commandType, data + offset, sizeof(UnsignedByte));
			offset += sizeof(UnsignedByte);
		} else if (data[offset] == 'R') {
			++offset;
			memcpy(&relay, data + offset, sizeof(UnsignedByte));
			offset += sizeof(UnsignedByte);
		} else if (data[offset] == 'P') {
			++offset;
			memcpy(&playerID, data + offset, sizeof(UnsignedByte));
			offset += sizeof(UnsignedByte);
		} else if (data[offset] == 'C') {
			++offset;
			memcpy(&commandID, data + offset, sizeof(UnsignedShort));
			offset += sizeof(UnsignedShort);
		} else if (data[offset] == 'F') {
			++offset;
			memcpy(&frame, data + offset, sizeof(UnsignedInt));
			offset += sizeof(UnsignedInt);
		} else if (data[offset] == 'D') {
			++offset;
			int payloadOffset = offset;
			NetCommandMsg *msg = NULL;
			if (commandType == NETCOMMANDTYPE_GAMECOMMAND) {
				msg = readGameMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_ACKBOTH) {
				msg = readAckBothMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_ACKSTAGE1) {
				msg = readAckStage1Message(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_ACKSTAGE2) {
				msg = readAckStage2Message(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_FRAMEINFO) {
				msg = readFrameMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_ROUTERFALLBACK) {
				msg = readRouterFallbackMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_PLAYERLEAVE) {
				msg = readPlayerLeaveMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_DESTROYPLAYER) {
				msg = readDestroyPlayerMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_KEEPALIVE) {
				msg = readKeepAliveMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_DISCONNECTKEEPALIVE) {
				msg = readDisconnectKeepAliveMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_DISCONNECTPLAYER) {
				msg = readDisconnectPlayerMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_DISCONNECTCHAT) {
				msg = readDisconnectChatMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_DISCONNECTVOTE) {
				msg = readDisconnectVoteMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_CHAT) {
				msg = readChatMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_PROGRESS) {
				msg = readProgressMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_LOADCOMPLETE) {
				msg = readLoadCompleteMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_TIMEOUTSTART) {
				msg = readTimeOutGameStartMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_WRAPPER) {
				msg = readWrapperMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_FILE) {
				msg = readFileMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_FILEANNOUNCE) {
				msg = readFileAnnounceMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_FILEPROGRESS) {
				msg = readFileProgressMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME) {
				msg = readInformPlayerLeaveFrameMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_REQUESTPLAYERLEAVE) {
				msg = readRequestPlayerLeaveMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_REQUESTFRAMEDATA) {
				msg = readRequestFrameDataMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_DISCONNECTFRAME) {
				msg = readDisconnectFrameMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_DISCONNECTSCREENOFF) {
				msg = readDisconnectScreenOffMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_REQUESTGAMESPYSTATSAUTHKEY) {
				msg = readRequestGameSpyStatsAuthKeyMessage(data, payloadOffset);
			}
			else if (commandType == NETCOMMANDTYPE_GAMESPYSTATSAUTHKEY) {
				msg = readGameSpyStatsAuthKeyMessage(data, payloadOffset);
			}
			if (msg == NULL) return NULL;

			msg->setExecutionFrame(frame);
			msg->setID(commandID);
			msg->setPlayerID(playerID);
			msg->setNetCommandType(commandType);

			ref = new NetCommandRef(msg);

			ref->setRelay(relay);

			offset = payloadOffset;
			msg->detach();
			msg = NULL;

			notDone = FALSE;
		}
	}

	return ref;
}
