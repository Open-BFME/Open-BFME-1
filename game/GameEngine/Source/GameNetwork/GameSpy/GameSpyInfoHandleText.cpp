// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/nat /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// GameSpyInfo::handleText, retail 0x006260C0.
// The vtable slot queues trimmed text as peer request type 0x15.

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include <new>

#define UNICODESTRING_H
struct UnicodeStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_text[ 1 ];
};

class UnicodeString
{
public:
	UnicodeString();
	UnicodeString( const UnicodeString &other );
	~UnicodeString();

	const unsigned short *str() const
	{
		return m_data ? m_data->m_text : reinterpret_cast<const unsigned short *>( 0x0107388C );
	}

	bool isEmpty() const
	{
		return !m_data || m_data->m_length == 0;
	}

	int compareNoCase( const UnicodeString &other ) const;
	void trim();

private:
	UnicodeStringData *m_data;
};

#include "GameNetwork/GameSpy/PeerThread.h"

class GameSpyInfo
{
public:
#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 ); GAMESPY_SLOT( 6 ); GAMESPY_SLOT( 7 );
	GAMESPY_SLOT( 8 ); GAMESPY_SLOT( 9 ); GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 );
	GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 ); GAMESPY_SLOT( 14 ); GAMESPY_SLOT( 15 );
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 ); GAMESPY_SLOT( 26 ); GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 );
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 ); GAMESPY_SLOT( 46 ); GAMESPY_SLOT( 47 );
	GAMESPY_SLOT( 48 ); GAMESPY_SLOT( 49 ); GAMESPY_SLOT( 50 ); GAMESPY_SLOT( 51 );
	GAMESPY_SLOT( 52 ); GAMESPY_SLOT( 53 ); GAMESPY_SLOT( 54 ); GAMESPY_SLOT( 55 );
	GAMESPY_SLOT( 56 ); GAMESPY_SLOT( 57 ); GAMESPY_SLOT( 58 ); GAMESPY_SLOT( 59 );
	GAMESPY_SLOT( 60 ); GAMESPY_SLOT( 61 ); GAMESPY_SLOT( 62 );
#undef GAMESPY_SLOT
	virtual Bool handleText( UnicodeString message );
};

Bool GameSpyInfo::handleText( UnicodeString message )
{
	PeerRequest request;
	request.text = message.str();

	message.trim();
	if ( !message.isEmpty() )
	{
		request.peerRequestType = PeerRequest::PEERREQUEST_MAX;
		TheGameSpyPeerMessageQueue->addRequest( request );
		return true;
	}

	return false;
}
