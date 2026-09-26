// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// InGameUI slot 59 (+0xEC) of the table 0x010F5B38 that ??0InGameUI
// (0x0044B800) installs; W3DInGameUI's table 0x01120590 inherits it. BFME adds
// this virtual between deselectAllDrawables (slot 58) and getSelectCount
// (slot 60), so Zero Hour has no slot for it and the name keeps the address.
// GameLogic::logicMessageDispatcher calls it at 0x007995FB as (TRUE, player).
// The body is Zero Hour CommandXlat.cpp's commented-out MSG_META_SELECT_ALL
// loop (GUI:MaxSelectionSize / GUI:SelectedAcrossMap): walk every drawable,
// select the given player's mobile, uncontained, live, selectable units, and
// when the flag is set hand each one to GameLogic::selectObject instead of the
// UI selection. KindOf values are the BFME name table at 0x012AA068.

#include "unicode_string.h"

inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString( const UnicodeString &that ) { ( (StringBase<unsigned short> *)this )->StringBase<unsigned short>::StringBase( *(const StringBase<unsigned short> *)&that ); }
inline UnicodeString::~UnicodeString() { ( (StringBase<unsigned short> *)this )->releaseBuffer(); }
template <class T> inline const T *StringBase<T>::str() const { static const T TheNullChr = 0; return m_data ? m_data->data : &TheNullChr; }

typedef bool Bool;
typedef int Int;
typedef unsigned short PlayerMaskType;

enum KindOfType
{
	KINDOF_CAN_ATTACK = 3,
	KINDOF_DOZER = 14,
	KINDOF_HARVESTER = 16,
	KINDOF_IGNORES_SELECT_ALL = 90,
};

enum Rva00446550MessageType
{
	RVA00446550_MSG_460 = 0x460,
};

class GameMessage;
class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	PlayerMaskType getPlayerMask() const { return 1 << m_playerIndex; }

private:
	unsigned char m_unmodelled00[0x24];
	Int m_playerIndex;										///< this+0x24
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;							///< this+0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	// Returns the masked word: a Bool return materialises `shr ecx,26; test cl,1`
	// where retail tests the word in place (`test dword [eax+0xD0],0x4000000`).
	unsigned int isKindOf( KindOfType t ) const { return m_kindof[ t / 32 ] & ( 1 << ( t % 32 ) ); }

private:
	unsigned char m_unmodelled08[0xc8 - 0x08];
	unsigned int m_kindof[6];								///< this+0xC8
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const
	{
		if( !m_template )
			return 0;
		return (const ThingTemplate *)m_template->getFinalOverride();
	}
	Bool isKindOf( KindOfType t ) const;

private:
	void *m_vtable;
	const ThingTemplate *m_template;						///< this+0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool isMobile() const;
	Player *getControllingPlayer() const;
	Bool queryRva001C9980();
	Bool isEffectivelyDead() const { return ( m_privateStatus & 1 ) != 0; }

	unsigned char m_unmodelled08[0x90 - 0x08];
	unsigned int m_status;									///< this+0x90, bit 3 UNSELECTABLE in table 0x012A6670
	unsigned char m_unmodelled94[0x214 - 0x94];
	void *m_unmodelled214;
	unsigned char m_unmodelled218[0x344 - 0x218];
	unsigned char m_privateStatus;							///< this+0x344
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	unsigned char m_unmodelled000[0xfc];
	Object *m_object;										///< this+0xFC
	unsigned char m_unmodelled100[0x104 - 0x100];
	Drawable *m_nextDrawable;								///< this+0x104
};

#define RVA00446550_SLOT(n) virtual void rvaSlot##n();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	RVA00446550_SLOT(00) RVA00446550_SLOT(01) RVA00446550_SLOT(02) RVA00446550_SLOT(03)
	RVA00446550_SLOT(04) RVA00446550_SLOT(05) RVA00446550_SLOT(06) RVA00446550_SLOT(07)
	RVA00446550_SLOT(08) RVA00446550_SLOT(09) RVA00446550_SLOT(10) RVA00446550_SLOT(11)
	virtual Drawable *firstDrawable();						///< vtable +0x30
};

extern GameClient *TheGameClient;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class MessageStream
{
public:
	RVA00446550_SLOT(00) RVA00446550_SLOT(01) RVA00446550_SLOT(02) RVA00446550_SLOT(03)
	RVA00446550_SLOT(04) RVA00446550_SLOT(05) RVA00446550_SLOT(06) RVA00446550_SLOT(07)
	RVA00446550_SLOT(08) RVA00446550_SLOT(09) RVA00446550_SLOT(10) RVA00446550_SLOT(11)
	RVA00446550_SLOT(12)
	virtual GameMessage *appendMessage( Rva00446550MessageType type );	///< vtable +0x34
};

extern MessageStream *TheMessageStream;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameText.h
class GameTextInterface
{
public:
	RVA00446550_SLOT(00) RVA00446550_SLOT(01) RVA00446550_SLOT(02) RVA00446550_SLOT(03)
	RVA00446550_SLOT(04) RVA00446550_SLOT(05) RVA00446550_SLOT(06) RVA00446550_SLOT(07)
	RVA00446550_SLOT(08) RVA00446550_SLOT(09)
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );	///< vtable +0x28
};

extern GameTextInterface *TheGameText;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void selectObject( Object *obj, Bool createNewSelection, PlayerMaskType playerMask, Bool affectClient );
};

extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	RVA00446550_SLOT(00) RVA00446550_SLOT(01) RVA00446550_SLOT(02) RVA00446550_SLOT(03)
	RVA00446550_SLOT(04) RVA00446550_SLOT(05) RVA00446550_SLOT(06) RVA00446550_SLOT(07)
	RVA00446550_SLOT(08) RVA00446550_SLOT(09) RVA00446550_SLOT(10) RVA00446550_SLOT(11)
	RVA00446550_SLOT(12)
	virtual void __cdecl message( UnicodeString format, ... );	///< vtable +0x34
	RVA00446550_SLOT(14) RVA00446550_SLOT(15)
	RVA00446550_SLOT(16) RVA00446550_SLOT(17) RVA00446550_SLOT(18) RVA00446550_SLOT(19)
	RVA00446550_SLOT(20) RVA00446550_SLOT(21) RVA00446550_SLOT(22) RVA00446550_SLOT(23)
	RVA00446550_SLOT(24) RVA00446550_SLOT(25) RVA00446550_SLOT(26) RVA00446550_SLOT(27)
	RVA00446550_SLOT(28) RVA00446550_SLOT(29) RVA00446550_SLOT(30) RVA00446550_SLOT(31)
	RVA00446550_SLOT(32) RVA00446550_SLOT(33) RVA00446550_SLOT(34) RVA00446550_SLOT(35)
	RVA00446550_SLOT(36) RVA00446550_SLOT(37) RVA00446550_SLOT(38) RVA00446550_SLOT(39)
	RVA00446550_SLOT(40) RVA00446550_SLOT(41) RVA00446550_SLOT(42) RVA00446550_SLOT(43)
	RVA00446550_SLOT(44) RVA00446550_SLOT(45) RVA00446550_SLOT(46) RVA00446550_SLOT(47)
	RVA00446550_SLOT(48) RVA00446550_SLOT(49) RVA00446550_SLOT(50) RVA00446550_SLOT(51)
	RVA00446550_SLOT(52) RVA00446550_SLOT(53) RVA00446550_SLOT(54) RVA00446550_SLOT(55)
	virtual void selectDrawable( Drawable *draw );			///< vtable +0xE0
	RVA00446550_SLOT(57)
	virtual void deselectAllDrawables();					///< vtable +0xE8
	virtual void rva00446550( Bool throughGameLogic, Player *player );	///< vtable +0xEC
	virtual Int getSelectCount();							///< vtable +0xF0
	virtual Int getMaxSelectCount();						///< vtable +0xF4
	RVA00446550_SLOT(62) RVA00446550_SLOT(63)
	RVA00446550_SLOT(64) RVA00446550_SLOT(65) RVA00446550_SLOT(66) RVA00446550_SLOT(67)
	RVA00446550_SLOT(68) RVA00446550_SLOT(69) RVA00446550_SLOT(70) RVA00446550_SLOT(71)
	RVA00446550_SLOT(72) RVA00446550_SLOT(73) RVA00446550_SLOT(74) RVA00446550_SLOT(75)
	RVA00446550_SLOT(76) RVA00446550_SLOT(77) RVA00446550_SLOT(78) RVA00446550_SLOT(79)
	RVA00446550_SLOT(80) RVA00446550_SLOT(81) RVA00446550_SLOT(82) RVA00446550_SLOT(83)
	RVA00446550_SLOT(84) RVA00446550_SLOT(85) RVA00446550_SLOT(86) RVA00446550_SLOT(87)
	RVA00446550_SLOT(88) RVA00446550_SLOT(89) RVA00446550_SLOT(90) RVA00446550_SLOT(91)
	virtual Bool getDisplayedMaxWarning();					///< vtable +0x170
	virtual void setDisplayedMaxWarning( Bool selected );	///< vtable +0x174
};

#undef RVA00446550_SLOT

extern InGameUI *TheInGameUI;

void InGameUI::rva00446550( Bool throughGameLogic, Player *player )
{
	if( !throughGameLogic )
	{
		TheInGameUI->deselectAllDrawables();
		TheMessageStream->appendMessage( RVA00446550_MSG_460 );
	}

	Drawable *draw = TheGameClient->firstDrawable();
	Bool createNewSelection = true;
	while( draw )
	{
		Object *object = draw->m_object;
		if( object
			&& object->isMobile()
			&& object->getControllingPlayer() == player
			&& !object->m_unmodelled214
			&& !object->getTemplate()->isKindOf( KINDOF_IGNORES_SELECT_ALL )
			&& ( object->isKindOf( KINDOF_CAN_ATTACK )
				|| ( !object->isKindOf( KINDOF_DOZER ) && !object->isKindOf( KINDOF_HARVESTER ) ) )
			&& !object->isEffectivelyDead()
			&& !( object->m_status & 8 )
			&& object->queryRva001C9980() )
		{
			if( TheInGameUI->getMaxSelectCount() > 0
				&& TheInGameUI->getSelectCount() >= TheInGameUI->getMaxSelectCount() )
			{
				if( !throughGameLogic && !TheInGameUI->getDisplayedMaxWarning() )
				{
					TheInGameUI->setDisplayedMaxWarning( true );
					UnicodeString msg;
					msg.format( TheGameText->fetch( "GUI:MaxSelectionSize" ).str(), TheInGameUI->getMaxSelectCount() );
					TheInGameUI->message( msg );
				}
			}
			else if( !throughGameLogic )
			{
				TheInGameUI->selectDrawable( draw );
				TheInGameUI->setDisplayedMaxWarning( false );
			}
			else
			{
				TheGameLogic->selectObject( object, createNewSelection, player->getPlayerMask(), false );
				createNewSelection = false;
			}
		}

		draw = draw->m_nextDrawable;
	}

	if( TheInGameUI->getSelectCount() && !throughGameLogic )
	{
		UnicodeString message = TheGameText->fetch( "GUI:SelectedAcrossMap" );
		TheInGameUI->message( message );
	}
}
