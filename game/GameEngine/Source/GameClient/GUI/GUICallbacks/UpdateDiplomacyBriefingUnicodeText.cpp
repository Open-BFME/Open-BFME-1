// Retail 0x004C4630: full 346-byte Unicode briefing-list updater.
// Named by the matched const-AsciiString wrapper at 0x004C47E0 and
// InGameUI subtitle callers. BFME stores Unicode strings, not the legacy
// AsciiString list. The BFME node allocator and STLport no-exception
// setting reproduce inlined list-node construction; /EHsc remains enabled.
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "string_base.h"
#include <algorithm>
#include <list>

template<> inline bool StringBase<unsigned short>::isEmpty() const
{
	return !m_data || m_data->length == 0;
}

#include "unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &text)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&text);
}

extern const char g_bfmeEmptyUnicode[];
inline int compareWideRuns(const unsigned short *s1, int len1,
	const unsigned short *s2, int len2)
{
	int minLen = len1;
	if (minLen >= len2)
		minLen = len2;
	const unsigned short *q = s2;
	const unsigned short *p = s1;
	if (minLen > 0) {
		do {
			if (*p != *q) {
				int diff = (int)(unsigned int)*p - (int)(unsigned int)*q;
				if (diff != 0)
					return diff;
				break;
			}
			++p;
			++q;
			--minLen;
		} while (minLen > 0);
	}
	return len1 - len2;
}
template<> inline int StringBase<unsigned short>::compare(
	const unsigned short *text, int len) const
{
	const int myLen = m_data ? m_data->length : 0;
	const unsigned short *data = m_data ? m_data->data :
		(const unsigned short *)g_bfmeEmptyUnicode;
	return compareWideRuns(data, myLen, text, len);
}
template<> inline int StringBase<unsigned short>::compare(
	const StringBase<unsigned short> &text) const
{
	int len = text.m_data ? text.m_data->length : 0;
	const unsigned short *data = text.m_data ? text.m_data->data :
		(const unsigned short *)g_bfmeEmptyUnicode;
	return compare(data, len);
}
inline bool operator==(const UnicodeString &left, const UnicodeString &right)
{
	return left.compare(right) == 0;
}

typedef int Int;
typedef bool Bool;
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow;
class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54();
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id);
};
extern GameWindowManager *TheWindowManager;

class InGameUI
{
public:
	char unknown[0x83c];
	Int messageColor1;
	Int messageColor2;

	Int getMessageColor(Int index) const
	{
		if (index % 2)
			return messageColor2;
		return messageColor1;
	}
};
extern InGameUI *TheInGameUI;

void GadgetListBoxReset(GameWindow *listbox);
Int GadgetListBoxGetNumEntries(GameWindow *listbox);
// Retail and GadgetListBoxAddEntryText_Thunk.cpp both use these six args.
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Int color, Int row, Int column, Bool overwrite);

typedef _STL::list<UnicodeString> BriefingList;
class BfmeGlobLF;
extern BfmeGlobLF *g_bfmeGlobLF;
#define theWindow ((GameWindow *)g_bfmeGlobLF)
extern BriefingList Rva00EF3884BriefingList;
#define theBriefingList Rva00EF3884BriefingList

void UpdateDiplomacyBriefingText(const UnicodeString &text, Bool clear)
{
	GameWindow *listboxSolo = TheWindowManager->winGetWindowFromId(theWindow,
		TheNameKeyGenerator->nameToKey("Diplomacy.wnd:ListboxSolo"));

	if (clear)
	{
		theBriefingList.clear();
		if (listboxSolo)
			GadgetListBoxReset(listboxSolo);
	}

	if (text.isEmpty())
		return;

	if (std::find(theBriefingList.begin(), theBriefingList.end(), text) !=
		theBriefingList.end())
		return;

	theBriefingList.push_back(text);
	if (!listboxSolo)
		return;

	Int numEntries = GadgetListBoxGetNumEntries(listboxSolo);
	GadgetListBoxAddEntryText(listboxSolo, text,
		TheInGameUI->getMessageColor(numEntries), -1, -1, true);
}
