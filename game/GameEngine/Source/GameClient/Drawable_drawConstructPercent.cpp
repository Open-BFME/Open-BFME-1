// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib

// BFME's no-region construction-percent pass, reached from Drawable::drawIconUI
// case 0 through the named ILT at 0x00034130.

#include <stddef.h>

#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef unsigned int Color;
typedef float Real;
typedef bool Bool;

class GameFont;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText( UnicodeString text );
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void setFont( GameFont *font );
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void setColor( Color color, Color dropColor );
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void draw( Int x, Int y, Int scaleX, Int scaleY );
	virtual void getSize( Int *width, Int *height );
	virtual Int getWidth( Int line );
};

class DisplayStringManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString( DisplayString *string );
};

class GlobalLanguageData
{
public:
	Int adjustFontSize( Int pointSize );
};

class FontLibrary
{
public:
	GameFont *getFont( AsciiString *name, Real pointSize, UnsignedByte bold );
};

class InGameUI
{
	UnsignedByte m_pad000[ 0x7c4 ];

public:
	AsciiString m_drawableCaptionFont;
	Int m_drawableCaptionPointSize;
	UnsignedByte m_drawableCaptionBold;

	AsciiString getDrawableCaptionFontName();
	Int getDrawableCaptionPointSize() { return m_drawableCaptionPointSize; }
	UnsignedByte isDrawableCaptionBold() { return m_drawableCaptionBold; }
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
};

class TacticalView
{
public:
#define DRAWABLE_CONSTRUCT_VIEW_SLOT(n) virtual void slot##n();
	DRAWABLE_CONSTRUCT_VIEW_SLOT(00) DRAWABLE_CONSTRUCT_VIEW_SLOT(01)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(02) DRAWABLE_CONSTRUCT_VIEW_SLOT(03)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(04) DRAWABLE_CONSTRUCT_VIEW_SLOT(05)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(06) DRAWABLE_CONSTRUCT_VIEW_SLOT(07)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(08) DRAWABLE_CONSTRUCT_VIEW_SLOT(09)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(10) DRAWABLE_CONSTRUCT_VIEW_SLOT(11)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(12) DRAWABLE_CONSTRUCT_VIEW_SLOT(13)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(14) DRAWABLE_CONSTRUCT_VIEW_SLOT(15)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(16) DRAWABLE_CONSTRUCT_VIEW_SLOT(17)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(18) DRAWABLE_CONSTRUCT_VIEW_SLOT(19)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(20) DRAWABLE_CONSTRUCT_VIEW_SLOT(21)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(22) DRAWABLE_CONSTRUCT_VIEW_SLOT(23)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(24) DRAWABLE_CONSTRUCT_VIEW_SLOT(25)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(26) DRAWABLE_CONSTRUCT_VIEW_SLOT(27)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(28) DRAWABLE_CONSTRUCT_VIEW_SLOT(29)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(30) DRAWABLE_CONSTRUCT_VIEW_SLOT(31)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(32) DRAWABLE_CONSTRUCT_VIEW_SLOT(33)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(34) DRAWABLE_CONSTRUCT_VIEW_SLOT(35)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(36) DRAWABLE_CONSTRUCT_VIEW_SLOT(37)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(38) DRAWABLE_CONSTRUCT_VIEW_SLOT(39)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(40) DRAWABLE_CONSTRUCT_VIEW_SLOT(41)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(42) DRAWABLE_CONSTRUCT_VIEW_SLOT(43)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(44) DRAWABLE_CONSTRUCT_VIEW_SLOT(45)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(46) DRAWABLE_CONSTRUCT_VIEW_SLOT(47)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(48) DRAWABLE_CONSTRUCT_VIEW_SLOT(49)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(50) DRAWABLE_CONSTRUCT_VIEW_SLOT(51)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(52) DRAWABLE_CONSTRUCT_VIEW_SLOT(53)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(54) DRAWABLE_CONSTRUCT_VIEW_SLOT(55)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(56) DRAWABLE_CONSTRUCT_VIEW_SLOT(57)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(58) DRAWABLE_CONSTRUCT_VIEW_SLOT(59)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(60) DRAWABLE_CONSTRUCT_VIEW_SLOT(61)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(62) DRAWABLE_CONSTRUCT_VIEW_SLOT(63)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(64) DRAWABLE_CONSTRUCT_VIEW_SLOT(65)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(66) DRAWABLE_CONSTRUCT_VIEW_SLOT(67)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(68) DRAWABLE_CONSTRUCT_VIEW_SLOT(69)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(70) DRAWABLE_CONSTRUCT_VIEW_SLOT(71)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(72) DRAWABLE_CONSTRUCT_VIEW_SLOT(73)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(74) DRAWABLE_CONSTRUCT_VIEW_SLOT(75)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(76) DRAWABLE_CONSTRUCT_VIEW_SLOT(77)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(78) DRAWABLE_CONSTRUCT_VIEW_SLOT(79)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(80) DRAWABLE_CONSTRUCT_VIEW_SLOT(81)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(82) DRAWABLE_CONSTRUCT_VIEW_SLOT(83)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(84) DRAWABLE_CONSTRUCT_VIEW_SLOT(85)
	DRAWABLE_CONSTRUCT_VIEW_SLOT(86)
#undef DRAWABLE_CONSTRUCT_VIEW_SLOT
	virtual Int worldToScreen( Coord3D *world, ICoord2D *screen );
};

class CountermeasuresBehaviorInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Bool isActive() const;
};

class ThingTemplate
{
	UnsignedByte m_pad000[ 0x20 ];

public:
	AsciiString m_name;
};

class Object
{
	UnsignedByte m_pad000[ 0x90 ];

public:
	UnsignedInt m_status;

private:
	UnsignedByte m_pad094[ 0x18c ];

public:
	Real m_constructionPercent;

private:
	UnsignedByte m_pad224[ 0x120 ];

public:
	UnsignedByte m_privateStatus;

	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	const ThingTemplate *getTemplate() const;
	const CountermeasuresBehaviorInterface *getCountermeasuresBehaviorInterface() const;
};

class AsciiStringSuffix
{
public:
	Bool endsWithNoCase( const char *suffix );
};

class Drawable
{
	UnsignedByte m_pad000[ 0xfc ];

public:
	Object *m_object;

private:
	UnsignedByte m_pad100[ 0x1c8 ];

public:
	Real m_lastConstructDisplayed;
	DisplayString *m_constructDisplayString;

	const Coord3D *getPosition() const;
	void getConstructCenter( Coord3D *center );

private:
	void drawConstructPercent();
};

typedef Int (GlobalLanguageData::*AdjustFontSizeCall)( Int );
union AdjustFontSizeValue
{
	void (*freeFunction)();
	AdjustFontSizeCall memberFunction;
};

typedef GameFont *(FontLibrary::*GetFontCall)( AsciiString *, Real, UnsignedByte );
union GetFontValue
{
	void (*freeFunction)();
	GetFontCall memberFunction;
};

typedef const ThingTemplate *(Object::*GetTemplateCall)() const;
union GetTemplateValue
{
	void (*freeFunction)();
	GetTemplateCall memberFunction;
};

typedef Bool (AsciiStringSuffix::*EndsWithNoCaseCall)( const char * );
union EndsWithNoCaseValue
{
	void (*freeFunction)();
	EndsWithNoCaseCall memberFunction;
};

typedef const CountermeasuresBehaviorInterface *(Object::*CountermeasuresCall)() const;
union CountermeasuresValue
{
	void (*freeFunction)();
	CountermeasuresCall memberFunction;
};

typedef const Coord3D *(Drawable::*PositionCall)() const;
union PositionValue
{
	void (*freeFunction)();
	PositionCall memberFunction;
};

typedef void (Drawable::*ConstructCenterCall)( Coord3D * );
union ConstructCenterValue
{
	void (*freeFunction)();
	ConstructCenterCall memberFunction;
};

extern void j_00004e67();
extern void j_0000abc3();
extern void j_000084b8();
extern void j_0001c3dc();
extern void j_000351d9();
extern void j_0003ee55();
extern void j_000239ed();

static __forceinline const Coord3D *constructPosition( Drawable *drawable )
{
	PositionValue call = { j_0003ee55 };
	return (drawable->*call.memberFunction)();
}

static __forceinline void constructCenter( Drawable *drawable, Coord3D *center )
{
	ConstructCenterValue call = { j_000239ed };
	(drawable->*call.memberFunction)( center );
}

#define DRAWABLE_CONSTRUCT_GLOBAL(type, address) \
	(*reinterpret_cast<type **>( address ))

typedef AsciiString (InGameUI::*CaptionFontNameCall)();
union CaptionFontNameValue
{
	void (*freeFunction)();
	CaptionFontNameCall memberFunction;
};
extern void j_0003b75f();

void Drawable::drawConstructPercent()
{
	Object *obj = m_object;
	if ( obj == NULL || (obj->m_status & 4) == 0 || (obj->m_status & 0x80000) != 0 ||
		obj->isEffectivelyDead() )
	{
		if ( m_constructDisplayString )
		{
			DRAWABLE_CONSTRUCT_GLOBAL( DisplayStringManager, 0x012f12cc )
				->freeDisplayString( m_constructDisplayString );
			m_constructDisplayString = NULL;
		}
		return;
	}

	if ( m_constructDisplayString == NULL )
	{
		m_constructDisplayString =
			DRAWABLE_CONSTRUCT_GLOBAL( DisplayStringManager, 0x012f12cc )->newDisplayString();
		CaptionFontNameValue fontNameCall = { j_0003b75f };
		GetFontValue getFontCall = { j_0000abc3 };
		AdjustFontSizeValue adjustCall = { j_00004e67 };
		m_constructDisplayString->setFont(
			(DRAWABLE_CONSTRUCT_GLOBAL( FontLibrary, 0x012f1b38 )->*getFontCall.memberFunction)(
				&(DRAWABLE_CONSTRUCT_GLOBAL( InGameUI, 0x012f148c )->*fontNameCall.memberFunction)(),
				(Real)(DRAWABLE_CONSTRUCT_GLOBAL( GlobalLanguageData, 0x012f1484 )->*adjustCall.memberFunction)(
					DRAWABLE_CONSTRUCT_GLOBAL( InGameUI, 0x012f148c )->getDrawableCaptionPointSize() ),
				DRAWABLE_CONSTRUCT_GLOBAL( InGameUI, 0x012f148c )->isDrawableCaptionBold() ) );
	}

	if ( m_lastConstructDisplayed != obj->m_constructionPercent )
	{
		GetTemplateValue getTemplateCall = { j_000084b8 };
		CountermeasuresValue countermeasuresCall = { j_000351d9 };
		UnicodeString buffer;
		if ( reinterpret_cast<const StringBase<char> *>(
				&(obj->*getTemplateCall.memberFunction)()->m_name )->endsWithNoCase( "moot" ) &&
			(obj->*countermeasuresCall.memberFunction)() != NULL &&
			(obj->*countermeasuresCall.memberFunction)()->isActive() )
		{
			buffer.format(
				DRAWABLE_CONSTRUCT_GLOBAL( GameTextInterface, 0x012f147c )
					->fetch( "CONTROLBAR:CouncilDesc" ),
				obj->m_constructionPercent );
		}
		else
		{
			buffer.format(
				DRAWABLE_CONSTRUCT_GLOBAL( GameTextInterface, 0x012f147c )
					->fetch( "CONTROLBAR:UnderConstructionDesc" ),
				obj->m_constructionPercent );
		}
		m_constructDisplayString->setText( buffer );
		m_lastConstructDisplayed = obj->m_constructionPercent;
	}

	ICoord2D screen;
	Coord3D center;
	constructCenter( this, &center );
	Real z = constructPosition( this )->z;
	TacticalView *view = DRAWABLE_CONSTRUCT_GLOBAL( TacticalView, 0x012f1600 );
	center.z = center.z - (center.z - z) * *reinterpret_cast<const Real *>( 0x010f15cc );
	if ( view->worldToScreen( &center, &screen ) != 0 )
		return;

	screen.x -= m_constructDisplayString->getWidth( -1 ) / 2;
	m_constructDisplayString->setColor( 0xffffffff, 0xff000000 );
	m_constructDisplayString->draw( screen.x, screen.y, 1, 1 );
}

#undef DRAWABLE_CONSTRUCT_GLOBAL
