// ?setCaptionText@Drawable@@QAEXABVUnicodeString@@@Z
// partial score=0.8 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// BFME Drawable::setCaptionText, 0x00418880, 381 bytes.  Reached from
// GameLogic::logicMessageDispatcher (0x0043xxxx, matched) through the ILT
// thunk ?j_00418880; the readable Zero Hour body is
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameClient/Drawable.cpp:3794 and every branch here comes from it.
//
// The body does NOT fit Drawable.cpp, and not because of the source: that TU
// compiles against the Zero Hour headers, so its DisplayString vtable carries
// the MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE slot (retail calls setText at
// +0x04, the vendored header reaches +0x08), its DisplayStringManager reaches
// newDisplayString at +0x18 (retail +0x24), and its InGameUI caption accessors
// read +0x1928/+0x192C where retail reads +0x7C8/+0x7CC.  Those are vtable and
// field displacements baked into the compiled bytes, not source spelling.
// Drawable::drawConstructPercent (0x0041FDF0, matched) already proved the
// BFME layout for the same class and the same four call sites, so setCaptionText
// lives beside it and the vendored copy in Drawable.cpp gives way.

#include <stddef.h>

#include "string_base.h"

// Retail's caption text is a StringBase<unsigned short>, not the Zero Hour
// four-byte header: the emptiness test is the inline m_data/m_length pair
// retail inlines at +0x20, the copy constructor is
// ??0?$StringBase@G@@AAE@ABV0@@Z (0x00888400) and the temporary's destructor
// folds onto ?releaseBuffer@?$StringBase@G@@AAEXXZ (0x008881D0).  The copy
// constructor and destructor stay INLINE forwarders or every by-value argument
// site transposes.
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() { releaseBuffer(); }
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	int compare( const UnicodeString &other ) const;
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

#define DRAWABLE_CAPTION_GLOBAL(type, address) \
	(*reinterpret_cast<type **>( address ))

void Drawable::setCaptionText( const UnicodeString &captionText )
{
	if ( captionText.isEmpty() )
	{
		if ( m_captionDisplayString )
		{
			DRAWABLE_CAPTION_GLOBAL( DisplayStringManager, 0x012f12cc )
				->freeDisplayString( m_captionDisplayString );
			m_captionDisplayString = 0;
		}
		return;
	}

	UnicodeString sanitizedString = captionText;
	DRAWABLE_CAPTION_GLOBAL( LanguageFilter, 0x012f1570 )->filterLine( sanitizedString );

	if ( m_captionDisplayString == 0 )
	{
		CaptionFontNameValue fontNameCall = { j_0003b75f };
		GetFontValue getFontCall = { j_0000abc3 };
		AdjustFontSizeValue adjustCall = { j_00004e67 };
		m_captionDisplayString = DRAWABLE_CAPTION_GLOBAL( DisplayStringManager, 0x012f12cc )
			->newDisplayString();
		GameFont *font =
			(DRAWABLE_CAPTION_GLOBAL( FontLibrary, 0x012f1b38 )->*getFontCall.memberFunction)(
				&(DRAWABLE_CAPTION_GLOBAL( InGameUI, 0x012f148c )->*fontNameCall.memberFunction)(),
				(Real)(DRAWABLE_CAPTION_GLOBAL( GlobalLanguageData, 0x012f1484 )
					->*adjustCall.memberFunction)(
						DRAWABLE_CAPTION_GLOBAL( InGameUI, 0x012f148c )
							->getDrawableCaptionPointSize() ),
				DRAWABLE_CAPTION_GLOBAL( InGameUI, 0x012f148c )->isDrawableCaptionBold() );
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

#undef DRAWABLE_CAPTION_GLOBAL

// ------------------------------------------------------------------
// MEASURED (probe.py, MSVC 7.1 /EHsc -O2):  ours 392 B vs retail 381 B,
// 15 relocations all resolving, shape 0.938, 9 structural differences.
// What this body already gets EXACT, where the six earlier verdicts did not:
//   * the /EHsc prologue ORDER (mov eax,fs:[0] / push -1 / push scope /
//     push eax / mov fs:[0],esp) and the `sub esp,8` + push ebx + push esi;
//   * freeDisplayString @ [edx+0x28] and newDisplayString @ [edx+0x24]
//     (the vendored Drawable.cpp header reaches +0x1C / +0x18);
//   * setText @ [eax+4], getText @ [edx+8], setFont @ [eax+0x18];
//   * InGameUI caption accessors at +0x7C8 / +0x7CC (vendored: +0x1928/+0x192C);
//   * getFont's Real: the fild dword / fstp dword [esp] int->float pair
//     (the vendored getFont takes Int and emits no conversion at all);
//   * the AsciiString temporary lives to the end of the getFont STATEMENT
//     (dtor right after getFont, before setFont) -- the vendored header's
//     AsciiString has no dtor here, so that call is simply absent;
//   * the display-string vptr load sits after getFont, not hoisted across it,
//     which only happens when getFont is its own `GameFont *font =` statement.
// Remaining 9 structural diffs, in probe order:
//   1. +0x22 the ZERO constant: retail `push edi; xor edi,edi` (edi reused for
//      the AsciiString temp at +0xAC once the 0 dies at +0x85), ours puts the 0
//      in ebx and the temp in edi. This is the standing blocker row 5737 calls
//      "MSVC's ZERO-REGISTER HOIST" and it is what makes `push edi` land 4
//      bytes late, `cmp word [eax+4],bx` instead of `di`, `mov [esi+0x2d0],ebx`
//      instead of `edi` and the -3-byte `mov [esp+0x20],ebx` vs `edi`.
//   2. Because bl is the 0, the compare bool has no register: ours
//      `setne byte [esp+0x24]` + `cmp byte [esp+0x24],bl` and the extra
//      `mov byte [esp+0x20],2` / `mov byte [esp+0x1c],bl` state stores, against
//      retail `setne bl` + `test bl,bl` with no state store at all.
//   3. retail splits the setText EH scope per branch (`push ecx; mov
//      [esp+0x14],esp` at +0x10D in the new path, `push ecx; mov [esp+0x10],esp`
//      at +0x13C in the else path); ours emits ONE `mov [esp+0x28],esp` shared
//      by both, because both branches fall into a single setText block.
// DISPROVED on this body (do not retry blind):
//   * `throw()` on the UnicodeString::compare declaration (eh_levers' first
//     choice) REMOVES both extra state stores but then drops `push ebx`
//     entirely, so the zero falls back to `test eax,eax` / immediate 0s:
//     shape falls 0.938 -> 0.876 and the structural count rises 9 -> 15.
//   * naming the compare result (`bool changed = ... != 0; if (changed)`) is
//     byte-identical to the inline form - 392 B, same 9 diffs. Only worth
//     knowing so the next seat does not spend a compile on it.
//   * the bool must stay a real bool: `if ( compare(...) )` would drop the
//     setne pair retail has at +0x130.
