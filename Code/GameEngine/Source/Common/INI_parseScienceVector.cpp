// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: INI::parseScienceVector, retail 0x000BCD80, 199 bytes. The body
// carried no ledger row; its name sat on a 5-byte thunk.
//
// The reference's body over the real STLport vector, with one BFME change:
// the token is looked up through the science store rather than INI::scanScience.
// Both clears
// inline to the same shape -- erase(begin(), end()), whose copy loop moves
// nothing and just resets the finish pointer -- and the token loop keeps the
// stricmp import in a register across iterations.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl stricmp(const char *string1, const char *string2);

enum ScienceType { SCIENCE_INVALID = -1 };

// BFME does not call INI::scanScience here: the token goes to the science
// store, whose pointer sits at 0x012ED7AC, through
// ScienceStore::friend_lookupScience at 0x000E7240.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Science.h
class ScienceStore
{
public:
	ScienceType friend_lookupScience(const char *name) const;
};

extern ScienceStore *TheScienceStore;

typedef _STL::vector<ScienceType> ScienceVec;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);	// retail 0x008509C0


	static void parseScienceVector(INI *ini, void *instance, void *store, const void *userData);
};

void INI::parseScienceVector(INI *ini, void *instance, void *store, const void *userData)
{
	ScienceVec *asv = (ScienceVec *)store;
	asv->clear();
	for (const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull())
	{
		if (stricmp(token, "None") == 0)
		{
			asv->clear();
			return;
		}
		asv->push_back(TheScienceStore->friend_lookupScience(token));
	}
}
