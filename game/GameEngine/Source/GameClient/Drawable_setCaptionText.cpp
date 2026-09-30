// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?setCaptionText@Drawable@@QAEXABVUnicodeString@@@Z: game/GameEngine/Source/GameClient/Drawable.cpp

// BFME Drawable::setCaptionText, 0x00418880, 381 bytes.  Reached from the
// matched GameLogic::logicMessageDispatcher through the ILT thunk; the
// readable Zero Hour twin is
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameClient/Drawable.cpp:4317 (setCaptionText) with :4354 (clearCaptionText)
// inlined into it, and every branch here comes from them.
//
// This body lives in its own TU, not in Drawable.cpp: that TU compiles
// against the Zero Hour headers, whose DisplayString vtable carries the
// MEMORY_POOL_GLUE slot (retail calls setText at +0x04, the ZH header reaches
// +0x08), whose DisplayStringManager reaches newDisplayString at +0x18
// (retail +0x24), whose InGameUI caption accessors read +0x1928/+0x192C
// (retail +0x7C8/+0x7CC), and whose FontLibrary::getFont takes Int, so
// retail's fild/fstp int-to-Real pair cannot appear there.  Those are vtable
// and field displacements baked into the compiled bytes.  The matched
// Drawable::drawConstructPercent (0x0041FDF0,
// Drawable_drawConstructPercent.cpp) proves the same BFME layout for this
// class at the same four call sites, so the caption body lives beside it in
// this local-facade TU and the vendored ZH copy in Drawable.cpp stays a
// present-unmatched readable port.

#include <stddef.h>

#include "string_base.h"

// Retail's caption text is a StringBase<unsigned short>, not the Zero Hour
// four-byte header: the emptiness test is the inline m_data/m_firstChar pair
// retail folds into the guard at +0x20, the copy constructor is
// ??0?$StringBase@G@@AAE@ABV0@@Z (0x00888400) and the temporary's destructor
// folds onto ?releaseBuffer@?$StringBase@G@@AAEXXZ (0x008881D0).  The copy
// constructor and destructor stay INLINE forwarders and compare stays OUT OF
// LINE (the body calls its ILT thunk at 0x000226EC); the compare declaration
// is `const throw()`, the repo's convention for this facade (see the matched
// OnlineCustomMatchApplySlotColor.cpp:57 and three sibling Apt bodies).  With
// compare throwing, MSVC also registers the getText return temporary in the
// EH state machine and spills the branch bool, which retail does not do.
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() { releaseBuffer(); }
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	int compare( const UnicodeString &other ) const throw();
};

// The font name the caption is drawn with is a StringBase<char> temporary:
// retail destroys it through ?releaseBuffer@BFMERetailAsciiString@@AAEXXZ
// (0x00887940) at +0xFC, after the getFont call at +0xEC.
class AsciiString : private StringBase<char>
{
public:
	~AsciiString() { releaseBuffer(); }
};

typedef unsigned char UnsignedByte;
typedef int Int;
typedef float Real;

class GameFont;

// retail vtable: 0 dtor, 1 setText, 2 getText, 3 getTextLength, 4
// notifyTextChanged, 5 reset, 6 setFont
class DisplayString
{
public:
	virtual void slot00();
	virtual void setText( UnicodeString text );
	virtual UnicodeString getText();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void setFont( GameFont *font );
};

// retail vtable: newDisplayString at +0x24, freeDisplayString at +0x28
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

class LanguageFilter
{
public:
	void filterLine( UnicodeString &line );
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

// retail InGameUI: the caption font name at +0x7C4, its point size at +0x7C8
// and the bold flag at +0x7CC.  getDrawableCaptionFontName is not inlined --
// it is the body at 0x00415BF0, reached here through the ILT thunk.
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

// retail Drawable: the caption display string is the member at +0x2D0
class Drawable
{
	UnsignedByte m_pad000[ 0x2d0 ];

public:
	DisplayString *m_captionDisplayString;

	void setCaptionText( const UnicodeString &captionText );
};

typedef AsciiString (InGameUI::*CaptionFontNameCall)();
union CaptionFontNameValue
{
	void (*freeFunction)();
	CaptionFontNameCall memberFunction;
};

typedef GameFont *(FontLibrary::*GetFontCall)( AsciiString *, Real, UnsignedByte );
union GetFontValue
{
	void (*freeFunction)();
	GetFontCall memberFunction;
};

typedef Int (GlobalLanguageData::*AdjustFontSizeCall)( Int );
union AdjustFontSizeValue
{
	void (*freeFunction)();
	AdjustFontSizeCall memberFunction;
};

extern void j_0003b75f();
extern void j_0000abc3();
extern void j_00004e67();

extern DisplayStringManager *TheDisplayStringManager;
extern LanguageFilter *TheLanguageFilter;
extern FontLibrary *TheFontLibrary;
extern InGameUI *TheInGameUI;
extern GlobalLanguageData *TheGlobalLanguageData;

#define DRAWABLE_CAPTION_GLOBAL(type, global) \
	(static_cast<type *>( global ))

void Drawable::setCaptionText( const UnicodeString &captionText )
{
	if ( captionText.isEmpty() )
	{
		if ( m_captionDisplayString )
		{
			DRAWABLE_CAPTION_GLOBAL( DisplayStringManager, TheDisplayStringManager )
				->freeDisplayString( m_captionDisplayString );
		}
		m_captionDisplayString = 0;
		return;
	}

	{
		UnicodeString sanitizedString = captionText;
		DRAWABLE_CAPTION_GLOBAL( LanguageFilter, TheLanguageFilter )->filterLine( sanitizedString );

		if ( m_captionDisplayString == 0 )
		{
			CaptionFontNameValue fontNameCall = { j_0003b75f };
			GetFontValue getFontCall = { j_0000abc3 };
			AdjustFontSizeValue adjustCall = { j_00004e67 };
			m_captionDisplayString = DRAWABLE_CAPTION_GLOBAL( DisplayStringManager, TheDisplayStringManager )
				->newDisplayString();
			GameFont *font =
				(DRAWABLE_CAPTION_GLOBAL( FontLibrary, TheFontLibrary )->*getFontCall.memberFunction)(
					&(DRAWABLE_CAPTION_GLOBAL( InGameUI, TheInGameUI )->*fontNameCall.memberFunction)(),
					(Real)(DRAWABLE_CAPTION_GLOBAL( GlobalLanguageData, TheGlobalLanguageData )
						->*adjustCall.memberFunction)(
							DRAWABLE_CAPTION_GLOBAL( InGameUI, TheInGameUI )
								->getDrawableCaptionPointSize() ),
					DRAWABLE_CAPTION_GLOBAL( InGameUI, TheInGameUI )->isDrawableCaptionBold() );
			m_captionDisplayString->setFont( font );
			m_captionDisplayString->setText( sanitizedString );
		}
		else
		{
			// set the string if the value has changed
			if ( m_captionDisplayString->getText().compare( sanitizedString ) != 0 )
			{
				m_captionDisplayString->setText( sanitizedString );
			}
		}
	}
}

#undef DRAWABLE_CAPTION_GLOBAL
