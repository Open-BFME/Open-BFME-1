// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// stlport
// readable body of ??1LANAPI@@UAE@XZ: Code/GameEngine/Source/GameNetwork/lanapi.cpp
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"
#include "Common/SubsystemInterface.h"

// Retail 0x00688680. Zero Hour's ~LANAPI verbatim -- reset(), then delete
// m_transport -- and the member offsets it destroys agree with Zero Hour's
// declaration order exactly: UnicodeString m_name at +0x10, AsciiString
// m_userName at +0x14, AsciiString m_hostName at +0x18. Only m_transport moved,
// from +0x40 to +0x4C, so three dwords BFME added sit between them.
//
// reset() is a direct call, not a virtual one: MSVC devirtualizes it inside the
// destructor, where the dynamic type is known.

class LANPlayer;
class LANGameInfo;

class Transport
{
public:
	~Transport();				// ILT thunk 0x0003A48B, ICF-folded with Transport::reset
};

// Inline and empty, as Zero Hour declares it: retail restores 0x0111AE50 and
// tail-calls ~SubsystemInterface from inside ~LANAPI rather than calling
// ??1LANAPIInterface@@UAE@XZ, which only happens when the base dtor is inlined.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPIInterface : public SubsystemInterface
{
public:
	virtual ~LANAPIInterface() { }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI : public LANAPIInterface
{
public:
	virtual ~LANAPI();
	virtual void reset(void);		// ILT thunk 0x000068AC

protected:
	LANPlayer *m_lobbyPlayers;				// +0x08
	LANGameInfo *m_games;					// +0x0C
	UnicodeString m_name;					// +0x10
	AsciiString m_userName;					// +0x14
	AsciiString m_hostName;					// +0x18
	UnsignedByte m_bfmeUnidentified[0x4C - 0x1C];		// +0x1C, not yet named
	Transport *m_transport;					// +0x4C
};

// ??1LANAPI@@UAE@XZ
LANAPI::~LANAPI(void)
{
	reset();

	if (m_transport)
		delete m_transport;
}
