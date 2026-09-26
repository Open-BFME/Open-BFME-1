// cl: /DNDEBUG /MD /EHsc

// FILE: BfmeAptScreenObjectivesProvideText.cpp
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

typedef bool Bool;
typedef int Int;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiStringData
{
public:
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_allocated;
	char m_chars[1];
};

class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	~AsciiString() { releaseBuffer(); }

	AsciiString &operator=(const AsciiString &that);

	AsciiStringData *m_data;

protected:
	void releaseBuffer();
};

class Glo012F1028Type;

extern Glo012F1028Type *Glo012F1028;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CampaignManager.h
class CampaignManager
{
public:
	AsciiString rva003BF580(Int objective);
};

class GameLogic
{
public:
	unsigned char m_unmodelled000[0x10c];
	Int m_gameMode;
};

extern GameLogic *TheBfmeGameLogic;

struct Rva00026AB2Vec12
{
	unsigned int size() const { return m_finish - m_start; }
	AsciiString *begin() { return m_start; }
	AsciiString &operator[](unsigned int index) { return *(begin() + index); }

	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unmodelled000[0x1208];
	Rva00026AB2Vec12 m_vec1208;
};

extern GlobalData *TheWritableGlobalData;

void d_0052ae20(void);
typedef Int (__cdecl *Rva0052AE20Fn)(Int);

class BfmeAptScreenObjectives
{
public:
	void bfmeProvideObjectiveText(const char *selector, void *value, Bool setting);

private:
	unsigned char m_unmodelled000[0x264];
	Int m_screenType;
};

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

	if (TheBfmeGameLogic->m_gameMode == 7)
	{
		if ((unsigned)index >= TheWritableGlobalData->m_vec1208.size())
			return;
		text = TheWritableGlobalData->m_vec1208[index];
	}
	else
	{
		Int objective = ((Rva0052AE20Fn)d_0052ae20)(index);
		if (objective >= 0)
			text = ((CampaignManager *)Glo012F1028)->rva003BF580(objective);
	}

	if (text.m_data != 0 && text.m_data->m_length != 0
		&& text.m_data->m_length + 2 < 255)
	{
		output[0] = '$';
		strcpy(output + 1, text.m_data->m_chars);
	}
}
