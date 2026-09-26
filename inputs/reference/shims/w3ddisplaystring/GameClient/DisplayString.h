// TU-scoped DisplayString layout shim.
//
// ZH's DisplayString inherits MemoryPoolObject and invokes
// MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE, which injects a SECOND base
// virtual (getObjectMemoryPool, overriding MemoryPoolObject's pure virtual)
// ahead of DisplayString's own declared virtuals. Retail BFME's vtable only
// has ONE base virtual (the destructor) before DisplayString's own methods -
// proven from three independent retail call sites:
//   - getListboxEntryBasedOnCoord (0x4B69D0): instData->getTextLength() ->
//     m_text->getTextLength() compiles to `call [vtbl+0xC]` (slot 3).
//   - W3DDisplayString::computeExtents masm note: getText @ vtbl+8 (slot 2).
//   - GadgetListBoxSetFont (0x4B7260, matched): retail bytes `call [eax+0x18]`
//     for setFont (slot 6, matches the existing hand-cast vtable[6] hack).
// Slots 0-3/6 = dtor,setText,getText,getTextLength,notifyTextChanged,reset,
// setFont - i.e. ZH's OWN declared order with the pool-glue slot removed.
// This shim drops the MemoryPoolObject base/macro entirely (unused in this
// TU: no DisplayString is ever `new`'d or deleteInstance()'d here, only
// consumed by pointer) so the vtable matches retail slot-for-slot.
#pragma once

#ifndef __DISPLAYSTRING_H_
#define __DISPLAYSTRING_H_

#include "Lib/BaseType.h"
#include "GameClient/GameFont.h"
#include "GameClient/Color.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

class DisplayStringManager;

class DisplayString
{

public:

	friend DisplayStringManager;

	DisplayString( void );
	// BFME's DisplayString destructor is out-of-line: W3DDisplayString's dtor
	// @0x6F4C50 CALLS it (thunk @0xD823) instead of inlining the base
	// teardown, which is what an inline empty body here would produce.
	virtual ~DisplayString( void );

	virtual void setText( UnicodeString text );		///< set text for this string
	virtual UnicodeString getText( void );				///< get text for this string
	virtual Int getTextLength( void );				///< return number of chars in string
	virtual void notifyTextChanged( void );		///< called when text has changed
	virtual void reset( void );								///< reset all contents of string

	virtual void setFont( GameFont *font );		///< set a font for display
	virtual GameFont *getFont( void );				///< return font in string
	virtual void setWordWrap( Int wordWrap ) = 0;	///< Set the width that we want to start wrapping text
	virtual void setWordWrapCentered( Bool isCentered ) = 0; ///< If this is set to true, the text on a new line is centered
	virtual void draw( Int x, Int y, Color color, Color dropColor ) = 0;  ///< render text
	virtual void draw( Int x, Int y, Color color, Color dropColor, Int xDrop, Int yDrop ) = 0;  ///< render text with the drop shadow being at the offsets passed in
	virtual void getSize( Int *width, Int *height ) = 0;  ///< get render size
	virtual Int getWidth( Int charPos = -1 ) = 0; ///< get text with up to charPos characters, 1- = all characters

	virtual void setUseHotkey( Bool useHotkey, Color hotKeyColor ) = 0;

	virtual void setClipRegion( IRegion2D *region );  ///< clip text in this region

	virtual void removeLastChar( void );			///< remove the last character
	virtual void appendChar( WideChar c );		///< append character to end

	DisplayString *next( void );							///< return next string

protected:

	UnicodeString m_textString;
	GameFont *m_font;			 ///< font to display this string with

	DisplayString *m_next;  ///< for the display string factory list ONLY
	DisplayString *m_prev;	///< for the display string factory list ONLY

};  // end DisplayString

inline UnicodeString DisplayString::getText( void ) { return m_textString; }
inline Int DisplayString::getTextLength( void ) { return m_textString.getLength(); }
inline void DisplayString::setFont( GameFont *font ) { m_font = font; }
inline GameFont *DisplayString::getFont( void ) { return m_font; }
inline void DisplayString::setClipRegion( IRegion2D *region ) {}
inline void DisplayString::notifyTextChanged( void ) {}
inline DisplayString *DisplayString::next( void ) { return m_next; }

#endif // __DISPLAYSTRING_H_
