// cl: /DNDEBUG /MD /EHs-c-
// Lift GarrisonContainModuleData::parseInitialRoster to clean C++.
//
// The standard INI roster parse: a required name token, then an optional count
// token which defaults to 1 when absent. Both token calls pass a null separator
// list, which is where the two `push 0` come from.
//
// The name's length is measured inline rather than left to the string class --
// retail walks the bytes and subtracts, which is MSVC's strlen intrinsic -- and
// the walk is guarded, so a null name stores a length of zero rather than
// running off. The result goes to AsciiString::set with an explicit length, not
// through assignment.
//
// The roster fields sit at instance+0x174 and instance+0x178. The third and
// fourth parameters are unused; being cdecl, nothing pops them.

typedef int Int;

extern "C" unsigned int __cdecl strlen(const char *s);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void set(const char *s, Int len);					///< ILT thunk at 0x00887D20

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps = 0);		///< ILT thunk at 0x00850970
	const char *getNextTokenOrNull(const char *seps = 0);	///< ILT thunk at 0x008509C0
	static Int scanInt(const char *s);					///< ILT thunk at 0x00852620
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
class GarrisonContainModuleData
{
public:
	static void parseInitialRoster(INI *, void *, void *, const void *);

private:
	unsigned char m_unreconstructed_00[0x174];
	AsciiString m_initialRosterName;					///< retail this+0x174
	Int m_initialRosterCount;							///< retail this+0x178
};

// ?parseInitialRoster@GarrisonContainModuleData@@SAXPAVINI@@PAX1PBX@Z
void GarrisonContainModuleData::parseInitialRoster(INI *ini, void *instance, void *store,
	const void *userData)
{
	const char *name = ini->getNextToken();
	const char *countToken = ini->getNextTokenOrNull();
	Int count = countToken ? INI::scanInt(countToken) : 1;

	GarrisonContainModuleData *self = (GarrisonContainModuleData *)instance;
	self->m_initialRosterName.set(name, name ? (Int)strlen(name) : 0);
	self->m_initialRosterCount = count;
}
