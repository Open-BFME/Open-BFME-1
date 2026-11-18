// cl: /DNDEBUG /MD /EHsc

// FILE: BfmeAptScreenObjectivesProvide.cpp
// The ObjectiveN and ObjectiveNStatus providers of the Objectives and
// PlayerStatus APT screens, and the slot-to-objective helper both call.
// Retail calls 0x0052AE20 directly (no ILT) from both providers, and VC7.1
// emits a direct call only to a function in the same TU, so the helper is a
// file-static here with its two callers, in retail's address order.
//
// The ObjectiveNStatus provider of the Objectives and PlayerStatus APT
// screens.  The constructor at 0x0052C660, landed in AptScreenFactories.cpp,
// registers ILT 0x00001DF2 against the name it builds as "Objective%d" plus
// "Status", and that thunk jumps here, so this is the method the constructor
// already declares as bfmeProvideObjectiveStatus.
//
// It writes "00" into the caller's buffer, then overwrites the two digits
// with the complete and indexed flags of the objective the helper at
// 0x0052AE20 picks.  Writing the first two bytes as strcpy of the literal is
// what makes MSVC keep the buffer in edi and the objective in esi, the way
// retail does; assigning the bytes one at a time swaps the two registers.
//
// m_screenType is the field the constructor initialises to 2 at +0x264.
//
// The ObjectiveN provider of the Objectives and PlayerStatus APT screens.
// The constructor at 0x0052C660, in AptScreenFactories.cpp, registers ILT
// 0x0001BBA8 against the name it builds as "Objective%d", and that thunk
// jumps here, so this is the method the constructor already declares as
// bfmeProvideObjectiveText.
//
// In game mode 7 the text comes from the vector at GlobalData +0x1208.
// Otherwise the helper at 0x0052AE20 turns the slot index into an objective
// index and the campaign singleton at 0x012F1028 supplies the string.  A
// non-empty string shorter than 253 characters is written to the caller's
// buffer behind a '$'.
//
// Two shapes matter for the bytes.  Asking the vector for its size through an
// inline size() loads m_finish before m_start, the order retail uses.  Reading
// m_start through an inline begin() puts the element address in eax; indexing
// the member directly puts it in edx.

#include <string.h>

#include "../../../Include/Common/ScalarTypes.h"


// class-gate: allow AsciiString the private view is the byte-proved codegen view of
// bfmeProvideObjectiveText (303/303): ascii_string.h refuses its m_data reads (C2248,
// header_adopt_blocked.tsv) and its getLength()/str() spelling drifts 72 bytes from +0x28.
class AsciiStringData
{
public:
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_allocated;
	char m_chars[1];
};


// Retail inlines this wrapper into StringBase<char> directly; declare just the
// StringBase<char> members it reaches (see build/whatif/wrapfix.py).
template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
public:
	void set(const StringBase<T> &other);
private:
	void releaseBuffer();
};
class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	~AsciiString() { releaseBuffer(); }

	AsciiString &operator=(const AsciiString &that) { ((StringBase<char> *)this)->set(*(const StringBase<char> *)&that); return *this; }

	AsciiStringData *m_data;

protected:
	void releaseBuffer();
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class CampaignManager
{
public:
	unsigned char isMissionObjectiveComplete(Int index);
	unsigned char isMissionObjectiveIndexed(Int index);
	unsigned char isMissionObjectiveEligible(Int index);
	AsciiString rva003BF580(Int objective);
};

class Rva003BDF70Owner
{
public:
	Int combinedSpanCount();
};

class GameLogic
{
public:
	unsigned char m_unmodelled000[0x10c];
	Int m_gameMode;
};

extern GameLogic *TheGameLogic;

struct Rva00026AB2Vec12
{
	unsigned int size() const { return m_finish - m_start; }
	AsciiString *begin() { return m_start; }
	AsciiString &operator[](unsigned int index) { return *(begin() + index); }

	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};

class GlobalData
{
public:
	unsigned char m_unmodelled000[0x1208];
	Rva00026AB2Vec12 m_vec1208;
};

extern GlobalData *TheWritableGlobalData;

class BfmeAptScreenObjectives
{
public:
	void bfmeProvideObjectiveStatus(const char *selector, void *value, Bool setting);
	void bfmeProvideObjectiveText(const char *selector, void *value, Bool setting);

private:
	unsigned char m_unmodelled000[0x264];
	Int m_screenType;
};

// Retail 0x0052AE20 (77 B): the index of the slot-th eligible mission
// objective among the campaign's objectives, or -1. Address-derived name.
// Two shapes matter: the countdown runs on the parameter itself (a local copy
// swaps the count and countdown registers), and the cursor is copied only
// after the bounds check (copying first places the copy ahead of the branch).
static Int rva0052AE20(Int slot)
{
	if (TheLivingWorldLogic == 0)
		return -1;

	bool more = true;
	Int count = ((Rva003BDF70Owner *)TheLivingWorldLogic)->combinedSpanCount();
	Int cursor = 0;
	Int current;

	while (more)
	{
		if (cursor >= count)
			return -1;
		current = cursor;
		++cursor;
		if (!((CampaignManager *)TheLivingWorldLogic)->isMissionObjectiveEligible(current))
			continue;
		if (slot <= 0)
			return current;
		--slot;
	}
}

// @?bfmeProvideObjectiveStatus@BfmeAptScreenObjectives@@QAEXPBDPAX_N@Z 0x0052AE80
void BfmeAptScreenObjectives::bfmeProvideObjectiveStatus(
	const char *selector, void *value, Bool setting)
{
	char *output = (char *)value;
	strcpy(output, "00");

	if (m_screenType != 0)
		return;

	Int index = (Int)selector;
	if (index < 0 || index >= 9)
		return;
	if (setting)
		return;
	if (TheGameLogic->m_gameMode == 7)
		return;

	Int objective = rva0052AE20(index);
	if (objective < 0)
		return;

	output[0] = ((CampaignManager *)TheLivingWorldLogic)->isMissionObjectiveComplete(objective)
		? '1' : '0';
	output[1] = ((CampaignManager *)TheLivingWorldLogic)->isMissionObjectiveIndexed(objective)
		? '1' : '0';
	output[2] = 0;
}

// @?bfmeProvideObjectiveText@BfmeAptScreenObjectives@@QAEXPBDPAX_N@Z 0x0052B8A0
void BfmeAptScreenObjectives::bfmeProvideObjectiveText(
	const char *selector, void *value, Bool setting)
{
	char *output = (char *)value;
	output[0] = 0;

	if (m_screenType != 0)
		return;

	Int index = (Int)selector;
	if (index < 0 || index >= 9)
		return;
	if (setting)
		return;

	AsciiString text;

	if (TheGameLogic->m_gameMode == 7)
	{
		if ((unsigned)index >= TheWritableGlobalData->m_vec1208.size())
			return;
		text = TheWritableGlobalData->m_vec1208[index];
	}
	else
	{
		Int objective = rva0052AE20(index);
		if (objective >= 0)
			text = ((CampaignManager *)TheLivingWorldLogic)->rva003BF580(objective);
	}

	if (text.m_data != 0 && text.m_data->m_length != 0
		&& text.m_data->m_length + 2 < 255)
	{
		output[0] = '$';
		strcpy(output + 1, text.m_data->m_chars);
	}
}
