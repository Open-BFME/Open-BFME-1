// cl: /DNDEBUG /MD /EHsc

// FILE: BfmeAptScreenObjectivesProvide.cpp
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

#include <string.h>

typedef bool Bool;
typedef int Int;

class Glo012F1028Type;

extern Glo012F1028Type *Glo012F1028;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CampaignManager.h
class CampaignManager
{
public:
	unsigned char isMissionObjectiveComplete(Int index);
	unsigned char isMissionObjectiveIndexed(Int index);
};

class GameLogic
{
public:
	unsigned char m_unmodelled000[0x10c];
	Int m_gameMode;
};

extern GameLogic *TheBfmeGameLogic;

// The retail REL32 at +0x4A lands on 0x0052AE20, whose ledger row is still
// the byte dump ?d_0052ae20@@YAXXZ.  The call site proves the ABI: one dword
// pushed, caller-cleaned with add esp 4, result tested as a signed int.
void d_0052ae20(void);
typedef Int (__cdecl *Rva0052AE20Fn)(Int);

class BfmeAptScreenObjectives
{
public:
	void bfmeProvideObjectiveStatus(const char *selector, void *value, Bool setting);

private:
	unsigned char m_unmodelled000[0x264];
	Int m_screenType;
};

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
	if (TheBfmeGameLogic->m_gameMode == 7)
		return;

	Int objective = ((Rva0052AE20Fn)d_0052ae20)(index);
	if (objective < 0)
		return;

	output[0] = ((CampaignManager *)Glo012F1028)->isMissionObjectiveComplete(objective)
		? '1' : '0';
	output[1] = ((CampaignManager *)Glo012F1028)->isMissionObjectiveIndexed(objective)
		? '1' : '0';
	output[2] = 0;
}
