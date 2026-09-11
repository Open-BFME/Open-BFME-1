// cl: /DNDEBUG /MD /EHsc

// Retail 0x004BE9C0 is the private character-insertion helper reached from
// GadgetTextEntryInput's GWM_IME_CHAR path.  The BFME EntryData layout differs
// from the ZH header: the text cursor and composition cursor are at +0x1c and
// +0x1e, while the draw flag is at +0x13.  Keep the recovered view local until
// the complete BFME gadget header is reconstructed.

typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;

class BfmeEntryString;

class GameWindow
{
public:
	void *winGetUserData();
};

bool __cdecl GadgetTextEntryInsertCharacter(
	GameWindow *window, UnsignedInt character);

template <typename T> class StringBase
{
public:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase() {}
	~StringBase() { releaseBuffer(); }

	void concat(const T *source, int length);
	void appendChar(T character)
	{
		T inserted = character;
		concat(&inserted, 1);
	}

	Header *m_data;

	private:
	friend bool __cdecl GadgetTextEntryInsertCharacter(
		GameWindow *window, UnsignedInt character);
	friend class BfmeEntryString;
	StringBase(const StringBase<T> &source);
	StringBase(const StringBase<T> &source, int start, int length);
	void releaseBuffer();
};

class BfmeEntryString
    : public StringBase<WideChar>
{
public:
	BfmeEntryString() {}
	BfmeEntryString(const BfmeEntryString &source)
		: StringBase<WideChar>(source) {}
	BfmeEntryString(const BfmeEntryString &source, int start, int length)
		: StringBase<WideChar>(source, start, length) {}
	~BfmeEntryString() {}
	using StringBase<WideChar>::concat;
	using StringBase<WideChar>::appendChar;
};

class BfmeEntryText
{
public:
	virtual void slot0();
	virtual void setText(BfmeEntryString text);
	virtual BfmeEntryString getText();
};

class BfmeEntryMaskedText
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void appendChar(int character);
};

struct BfmeEntryData
{
	BfmeEntryText *text;
	BfmeEntryMaskedText *secretTextDisplay;
	void *constructText;
	UnsignedInt flags;
	short maxTextLen;
	unsigned char receivedUnichar;
	unsigned char drawTextFromStart;
	unsigned char padding14[8];
	unsigned short charPos;
	unsigned short conCharPos;
};

typedef char BfmeEntryDataCharPosOffset[
	(sizeof(BfmeEntryData) >= 0x20) ? 1 : -1];

extern const char g_bfmeEmptyUnicode[];

extern bool __cdecl GadgetTextEntryValidateCharacter(
WideChar character, signed char flags);
extern void __cdecl GadgetTextEntryUpdateComposition(GameWindow *window);
extern void __cdecl GadgetTextEntrySetCursorPosition(
	GameWindow *window, UnsignedInt position);

typedef bool (__cdecl *BfmeCharacterValidator)(
	WideChar character, UnsignedInt flags);

// ?GadgetTextEntryInsertCharacter@@YA_NPAVGameWindow@@I@Z
bool __cdecl GadgetTextEntryInsertCharacter(
	GameWindow *window, UnsignedInt character)
{
	BfmeEntryData *entry =
		(BfmeEntryData *)window->winGetUserData();

	if (!((BfmeCharacterValidator)GadgetTextEntryValidateCharacter)(
		character, entry->flags))
		return false;

	if (entry->conCharPos != entry->charPos)
		GadgetTextEntryUpdateComposition(window);

	BfmeEntryString current = entry->text->getText();

	int currentLength = current.m_data ? current.m_data->length : 0;
	if (currentLength >= (short)entry->maxTextLen)
		return false;

	int prefixLength = entry->charPos;
	BfmeEntryString prefix(current, 0, prefixLength);
	prefix.appendChar((WideChar)character);

	{
		BfmeEntryString suffix(current, entry->charPos,
			(current.m_data ? current.m_data->length : 0) - entry->charPos);

		int suffixChars = suffix.m_data ? suffix.m_data->length : 0;
		const WideChar *suffixData = suffix.m_data
			? suffix.m_data->data
			: (const WideChar *)g_bfmeEmptyUnicode;
		prefix.concat(suffixData, suffixChars);
	}

	entry->text->setText(prefix);
	GadgetTextEntrySetCursorPosition(window, entry->charPos + 1);
	entry->conCharPos = entry->charPos;
	entry->secretTextDisplay->appendChar(0x2a);
	entry->drawTextFromStart = 1;

	return true;
}
