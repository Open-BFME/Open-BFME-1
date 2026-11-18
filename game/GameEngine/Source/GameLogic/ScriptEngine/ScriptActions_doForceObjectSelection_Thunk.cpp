// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ?doForceObjectSelection@ScriptActions@@IAEXABVAsciiString@@0_N0@Z
// Clean C++ recovery of ScriptActions::doForceObjectSelection.
// Retail boundary: 0x002FAF10, 481 bytes, ends RET 16 at 0x002FB0EE.
// Identity: the matched ScriptActions::executeAction reaches this body through
// its OBJECT_FORCE_SELECT arm (ScriptActions.cpp).  BFME takes the team name
// by value through ScriptEngine vtable +0x44, walks the team member list with
// the virtual-base-adjusted Object DLINK pointer-to-member, and replaces Zero
// Hour's unconditional deselectAllDrawables with a controlling-player gate
// around a 0x3E9 GameMessage plus the +0xE0 InGameUI select slot.
// Object::m_template is Zero Hour's OVERRIDE<ThingTemplate> (Common/Override.h)
// and Overridable::getFinalOverride is the reference's inline recursive
// accessor (Common/Overridable.h): with that typing the Zero Hour statement
// order keeps retail's EBX bestGuess / EDI vbtable-index registers.

#include "../../../Include/Common/ScalarTypes.h"


typedef int ObjectID;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

// AsciiString is the canonical WWLib header.  Retail inlines `==` as a call
// to the out-of-line StringBase<char>::compare (ILT 0x000220C5 -> 0x0005FEB0).
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// ---------------------------------------------------------------------------
// Object: the DLINK pointer-to-member law.  The base that owns the team-member
// link sits at +4 and the base that introduces the virtual base (its own
// vbptr) sits at +0x68, so MSVC 7.1 encodes the link member's this-adjustment
// as 4 - 0x68 == -100 with vbindex 0 and emits
//   mov edx,[esi+0x68] / mov eax,[edx+0] / add eax,-100 / lea ecx,[eax+esi+0x68]
// exactly as retail does.  See inputs/reference/shims/objectdlink/ObjectDlinkPmf.h.
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ThingTemplate / Overridable: m_nextOverride at +0x04, m_name at +0x20.
// The override walk is the inline outer level plus the out-of-line recursive
// call at ILT 0x000022BB, which is why retail reads [eax+4] and branches
// before each of the two calls.
// ---------------------------------------------------------------------------
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const
	{
		if ( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;									// +0x00
	Overridable *m_nextOverride;						// +0x04
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_beforeName[0x18];
	AsciiString m_name;								// +0x20
	const AsciiString &getName() const { return m_name; }
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if ( !m_overridable ) return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	const T *operator*() const
	{
		if ( !m_overridable ) return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	operator const T *() const { return operator*(); }

	const T *m_overridable;
};

class Object;
class Drawable;
class Player;

class BfmeObjectVtbl
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual Drawable *getDrawable() const = 0;		// +0x28
};

class BfmeObjectDlinkBase
{
public:
	OVERRIDE<ThingTemplate> m_template;			// +0x04

	Object *dlink_next_TeamMemberList( void ) const;
};

class BfmeObjectFieldPad
{
public:
	unsigned char m_beforePosition[0x30];
	Coord3D m_position;								// +0x38
	unsigned char m_beforeVbptrCarrier[0x24];
};

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];						// +0x68 carries the vbptr
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectFieldPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_beforeId[4];
	ObjectID m_id;									// +0x74

	Player *getControllingPlayer() const;

	ObjectID getID() const { return m_id; }

	const ThingTemplate *getTemplate() const
	{
		return m_template;
	}

	const Coord3D *getPosition() const { return &m_position; }
};

template <class ObjectType>
class DLINK_ITERATOR
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)( void ) const;

	DLINK_ITERATOR( ObjectType *cur, GetNextFunc getNext )
		: m_cur( cur ), m_getNext( getNext ) {}

	Bool done() const { return m_cur == 0; }
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		m_cur = (m_cur->*m_getNext)();
	}

private:
	ObjectType *m_cur;
	GetNextFunc m_getNext;
};

// ---------------------------------------------------------------------------
// Team, ScriptEngine, Player/PlayerList, InGameUI, MessageStream, AudioEventRTS,
// AudioManager, TacticalView.  Every vtable overlay below places the observed
// retail slot exactly: 0x44, 0x28, 0xE0, 0x34, 0x44, 0x60.
// ---------------------------------------------------------------------------
class Team
{
public:
	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_head;									// +0x0C

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>( m_head, Object::dlink_next_TeamMemberList );
	}
};

class ScriptEngine
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual Team *getTeamNamed( AsciiString name, Bool exact ) = 0;	// +0x44, BY VALUE
};

class Player
{
public:
	unsigned char m_beforeIndex[0x24];
	Int m_playerIndex;									// +0x24
};

class PlayerList
{
public:
	unsigned char m_beforeLocalPlayer[0x0C];
	Player *m_localPlayer;							// +0x0C
};

class GameMessage
{
public:
	void appendBooleanArgument( Bool value );
	void appendObjectIDArgument( unsigned int id );
};

class MessageStream
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual GameMessage *createMessage( Int type ) = 0;	// +0x34
};

class InGameUI
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void s21() = 0;
	virtual void s22() = 0;
	virtual void s23() = 0;
	virtual void s24() = 0;
	virtual void s25() = 0;
	virtual void s26() = 0;
	virtual void s27() = 0;
	virtual void s28() = 0;
	virtual void s29() = 0;
	virtual void s30() = 0;
	virtual void s31() = 0;
	virtual void s32() = 0;
	virtual void s33() = 0;
	virtual void s34() = 0;
	virtual void s35() = 0;
	virtual void s36() = 0;
	virtual void s37() = 0;
	virtual void s38() = 0;
	virtual void s39() = 0;
	virtual void s40() = 0;
	virtual void s41() = 0;
	virtual void s42() = 0;
	virtual void s43() = 0;
	virtual void s44() = 0;
	virtual void s45() = 0;
	virtual void s46() = 0;
	virtual void s47() = 0;
	virtual void s48() = 0;
	virtual void s49() = 0;
	virtual void s50() = 0;
	virtual void s51() = 0;
	virtual void s52() = 0;
	virtual void s53() = 0;
	virtual void s54() = 0;
	virtual void s55() = 0;
	virtual void selectDrawable( Drawable *drawable ) = 0;	// +0xE0
};

// 0x70 bytes, constructed from the audio name and an int, destroyed at scope
// exit.  No virtuals, so sizeof is exactly the 0x70 retail allocates.
class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &name, int id );
	void setPlayerIndex( int index );
	~AudioEventRTS();

	unsigned char m_body[0x70];
};

class AudioManager
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void addAudioEvent( AudioEventRTS *event ) = 0;	// +0x44
};

class TacticalView
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void s21() = 0;
	virtual void s22() = 0;
	virtual void s23() = 0;
	virtual void moveCameraTo( const Coord3D *position, Int, Int, Int, Int, Int ) = 0;	// +0x60
};

// Retail reads each singleton straight into ECX and only then faults the
// vtable into EDX (`mov ecx,[global]` / `mov edx,[ecx]`), so these must be
// real extern globals at the pinned addresses, not address macros.
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern MessageStream *TheMessageStream;
extern InGameUI *TheInGameUI;
extern AudioManager *TheAudio;

#pragma comment(linker, "/alternatename:?TheTacticalView@@3PAVTacticalView@@A=?TheTacticalView@@3PAVView@@A")
extern TacticalView *TheTacticalView;

class ScriptActions
{
protected:
	void doForceObjectSelection( const AsciiString &teamName,
		const AsciiString &objectType, Bool centerInView,
		const AsciiString &audioToPlay );
};

void ScriptActions::doForceObjectSelection( const AsciiString &teamName,
	const AsciiString &objectType, Bool centerInView,
	const AsciiString &audioToPlay )
{
	Team *team = TheScriptEngine->getTeamNamed( teamName, false );

	if ( !team )
		return;

	Object *bestGuess = 0;

	for ( DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance() )
	{
		Object *obj = iter.cur();
		if ( obj->getTemplate() && obj->getTemplate()->getName().StringBase<char>::compare( objectType ) == 0 )
		{
			if ( bestGuess == 0 || obj->getID() < bestGuess->getID() )
				bestGuess = obj;
		}
	}

	if ( !( bestGuess && bestGuess->getDrawable() ) )
		return;

	Player *localPlayer = ThePlayerList->m_localPlayer;

	if ( bestGuess->getControllingPlayer() == localPlayer )
	{
		GameMessage *message = TheMessageStream->createMessage( 0x3E9 );
		message->appendBooleanArgument( true );
		const ObjectID objectId = bestGuess->m_id;
		message->appendObjectIDArgument( objectId );
		TheInGameUI->selectDrawable( bestGuess->getDrawable() );
	}

	AudioEventRTS audioEvent( audioToPlay, 0 );
	Player *const audioPlayer = ThePlayerList->m_localPlayer;
	const Int audioIndex = audioPlayer->m_playerIndex;
	audioEvent.setPlayerIndex( audioIndex );
	TheAudio->addAudioEvent( &audioEvent );

	if ( centerInView )
	{
		const Coord3D *p = bestGuess->getPosition();
		Coord3D cam;
		cam.x = p->x;
		cam.y = p->y;
		cam.z = p->z;
		TheTacticalView->moveCameraTo( &cam, 0, 0, 0, 0, 0 );
	}
}

