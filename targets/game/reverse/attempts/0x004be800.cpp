// ?Rva004BE800@@YAXPAVGameWindow@@@Z
// partial score=0.238506 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc

#include "../Code/Libraries/Source/WWVegas/WWLib/unicode_string.h"
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
 ((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(*(const StringBase<WideChar> *)&s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s,int start,int length)
{
 ((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(*(const StringBase<WideChar> *)&s,start,length);
}
inline UnicodeString::~UnicodeString()
{
 ((StringBase<WideChar> *)this)->releaseBuffer();
}
template<class T> inline int StringBase<T>::getLength() const
{
 return m_data ? m_data->length : 0;
}

class GameWindow
{
public:
	void *winGetUserData();
};

class TextEntryText
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
	virtual int getTextLength();
};

class MaskedTextDisplay
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void removeLastChar();
};

struct EntryData
{
	TextEntryText *text;
	MaskedTextDisplay *secretTextDisplay;
	void *constructText;
	UnsignedInt flags;
	short maxTextLen;
	unsigned char receivedUnichar;
	unsigned char drawTextFromStart;
	unsigned char padding14[8];
	unsigned short charPos;
	unsigned short conCharPos;
};

extern void __cdecl GadgetTextEntrySetCursorPosition(GameWindow *, UnsignedInt);

// Retail body at 0x004BE800. Its address-derived name preserves the unresolved
// identity while expressing the selected-range operation proven by its body.
void __cdecl Rva004BE800(GameWindow *window)
{
	EntryData *entry = (EntryData *)window->winGetUserData();
	bool changed = false;
	const unsigned short &lo = entry->conCharPos < entry->charPos ? entry->conCharPos : entry->charPos;
	unsigned int lower = lo;
	const unsigned short &hi = entry->conCharPos > entry->charPos ? entry->conCharPos : entry->charPos;
	unsigned int upper = hi;

	unsigned int textLength = (unsigned int)entry->text->getTextLength();
	if (upper > textLength)
		upper = entry->text->getTextLength();

	if (upper != 0 && upper != lower) {
		UnicodeString current = entry->text->getText();
		UnicodeString prefix(current, 0, lower);
		{
			UnicodeString suffix(current, upper, current.getLength() - upper);
			((StringBase<WideChar> *)&prefix)->concat(*(const StringBase<WideChar> *)&suffix);
		}
		entry->text->setText(prefix);
		changed = true;
		GadgetTextEntrySetCursorPosition(window, lower);
		entry->conCharPos = lower;
		for (unsigned int count = (unsigned int)(upper - lower); count != 0; --count)
			entry->secretTextDisplay->removeLastChar();
	}

	entry->drawTextFromStart |= (unsigned char)changed;
}
