// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0055C480: set APT:ChatFriendLogInMessage then invoke ChatMessageOpen
// on the movie at this+0x250.
extern void j_00015235();

struct AptChatFriendLogInDispatchReceiver
{
	void dispatch(int movie, const char *function, int argumentCount,
		const void *argument, int unused1, int unused2, int unused3, int unused4);
};

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_rva012F19E8WindowManager;

class BfmeAptChatFriendLogIn
{
public:
	void showFriendLogIn( const UnicodeString &text );

private:
	unsigned char m_unmodelled[ 0x250 ];
	int m_movie;
};

// ?showFriendLogIn@BfmeAptChatFriendLogIn@@QAEXABVUnicodeString@@@Z
void BfmeAptChatFriendLogIn::showFriendLogIn( const UnicodeString &text )
{
	{
		AsciiString name( "APT:ChatFriendLogInMessage" );
		g_rva012F19E8WindowManager->bfme_setAptText( name, text );
	}
	typedef void (AptChatFriendLogInDispatchReceiver::*Dispatch)(int, const char *, int,
		const void *, int, int, int, int);
	union
	{
		void *asVoid;
		Dispatch asMember;
	} dispatchFunction;
	dispatchFunction.asVoid = (void *)j_00015235;
	(reinterpret_cast<AptChatFriendLogInDispatchReceiver *>(g_rva012F19E8WindowManager)->*
		dispatchFunction.asMember)(m_movie, "ChatMessageOpen", 0, 0, 0, 0, 0, 0);
}
