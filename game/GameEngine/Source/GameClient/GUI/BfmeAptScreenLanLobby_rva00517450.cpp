// cl: /DNDEBUG /MD /EHsc
// Retail 0x00517450, 199 bytes.  This is the unclaimed LanLobby sibling
// between copyGuardName (0x005171A0) and commitUserName (0x00517550).
// The body is named by RVA because the original method spelling is not
// recovered.  Its direct named caller is BfmeA1006::bfmeGo1006A at 0x00688AD0;
// the LanLobby interpretation agrees with the matched sibling methods and
// the +0x25C BfmeE976 subobject. The address-derived owner preserves uncertainty.

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


class GameWindow;
GameWindow *MessageBoxOk( UnicodeString title, UnicodeString body,
	void (*callback)( void ) );

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

class LANAPI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
};

extern LANAPI *TheLAN;

class GameEngine;
extern GameEngine *TheGameEngine;
extern void j_00010f8c();
extern void j_00015235();

class BfmeX1070;

class BfmeR1070
{
};
typedef void (BfmeR1070::*BfmeR1070Fn)( BfmeX1070 *owner, char *name, int count, char *value,
	char *a, char *b, char *c, char *d );

// retail 0x012F19E8: the canonical spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A, defined once in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU reaches the
// same address through its own BfmeR1070 view, so it casts at the use; the
// view is only a receiver type for the ILT 0x00015235 member-pointer call.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

class BfmeE976
{
public:
	virtual void slot00();
	virtual void stop();
	void bfmeGo976E();
};

class Rva00517450LanLobby
{
public:
	void rva00517450();

private:
	char m_unmodelled[ 0x250 ];
	BfmeX1070 *m_actionOwner;
	char m_gap254[ 8 ];
	BfmeE976 m_subStop;
	char m_unmodelled260[ 0x148 ];
	volatile int m_state;
};

// ?rva00517450@Rva00517450LanLobby@@QAEXXZ
void Rva00517450LanLobby::rva00517450()
{
	Rva00517450LanLobby *self = this;
	BfmeE976 *subStop = &self->m_subStop;
	subStop->bfmeGo976E();
	subStop->stop();
	if ( TheLAN )
		TheLAN->slot13();
	((void (__fastcall *)( GameEngine * ))j_00010f8c)( TheGameEngine );
	self->m_state = 0;
	BfmeX1070 *owner = self->m_actionOwner;
	// Retail calls ILT 0x00015235 (-> 0x004675F0); member-pointer call keeps ECX.
	union { void (*fn)(); BfmeR1070Fn call; } target = { j_00015235 };
	( ((BfmeR1070 *)g_rva012F19E8WindowManager)->*target.call )( owner, "CancelGame", 0, 0, 0, 0, 0, 0 );
	MessageBoxOk( TheGameText->fetch( "GUI:HostLeftTitle" ),
		TheGameText->fetch( "GUI:HostLeft" ), 0 );
}
