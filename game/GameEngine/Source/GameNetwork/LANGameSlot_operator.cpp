// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

// UnicodeString is StringBase<WideChar>, and retail inlined the one-line
// forwarder away: every member copy below encodes
// ?set@?$StringBase@G@@QAEXABV1@@Z at 0x00888530 directly, not the ZH
// ?set@UnicodeString@@QAEXABV1@@Z spelling (which resolves to the NARROW
// StringBase<char> body at 0x00887C90).
#include "string_base.h"

inline void UnicodeString::set( const UnicodeString &stringSrc )
{
	reinterpret_cast<StringBase<WideChar> &>( *this ).set(
		reinterpret_cast<const StringBase<WideChar> &>( stringSrc ) );
}

enum LANGameSlotState { LAN_SLOT_OPEN, LAN_SLOT_CLOSED, LAN_SLOT_EASY_AI, LAN_SLOT_MED_AI, LAN_SLOT_BRUTAL_AI, LAN_SLOT_PLAYER };

struct LANGameSlotConnectInfo
{
	UnsignedInt m_nat;
	UnsignedShort m_port;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
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
