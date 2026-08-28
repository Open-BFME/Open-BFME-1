// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

enum LANGameSlotState { LAN_SLOT_OPEN, LAN_SLOT_CLOSED, LAN_SLOT_EASY_AI, LAN_SLOT_MED_AI, LAN_SLOT_BRUTAL_AI, LAN_SLOT_PLAYER };

struct LANGameSlotConnectInfo
{
	UnsignedInt m_nat;
	UnsignedShort m_port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	virtual void reset();

protected:
	LANGameSlotState m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	Int m_color;
	Int m_startPos;
	Int m_playerTemplate;
	Int m_teamNumber;
	Int m_origColor;
	Int m_origStartPos;
	Int m_origPlayerTemplate;
	UnicodeString m_name;
	UnsignedInt m_IP;
	LANGameSlotConnectInfo m_connectInfo;
	UnsignedInt m_lastFrameInGame;
	Bool m_disconnected;
	UnsignedInt m_bfmeLayoutPad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
protected:
	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedInt m_lastHeard;
	LANPlayer *m_next;
	UnsignedInt m_IP;
	UnsignedInt m_bfmeLayoutPad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot
{
public:
private:
	LANPlayer m_user;
	AsciiString m_serial;
	UnsignedInt m_lastHeard;
};

LANGameSlot& forceLANGameSlotAssignment(LANGameSlot& dst, const LANGameSlot& src)
{
	return dst = src;
}

LANGameSlot& (*forceLANGameSlotAssignmentPointer)(LANGameSlot&, const LANGameSlot&) = forceLANGameSlotAssignment;

LANGameSlot& (LANGameSlot::*lanGameSlotAssignmentPointer)(const LANGameSlot&) = &LANGameSlot::operator=;
