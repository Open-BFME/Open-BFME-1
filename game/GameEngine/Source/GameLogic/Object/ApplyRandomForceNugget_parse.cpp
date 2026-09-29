// cl: /DNDEBUG /MD /EHsc
// Retail 0x001D8800, 64 bytes: ApplyRandomForceNugget::parse in the BFME layout.
//
// Identity: the ObjectCreationList FieldParse table entry "ApplyRandomForce" points here.
// The body reads the four-row FieldParse table at VA 0x0109F6D8 (MinForceMagnitude at +0x04
// and MaxForceMagnitude at +0x08 through parseReal, MinForcePitch at +0x0C and MaxForcePitch
// at +0x10 through parseAngleReal), which fixes the 0x14-byte layout. Zero Hour's nugget has a
// fifth field (spin rate) that BFME lacks, so the class is spelled here against the retail
// layout. The vtable at VA 0x0109F0F4 is the one the constructor at 0x001D5F00 installs.

class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *, const FieldParse *);
	static void parseReal(INI *, void *, void *, const void *);
	static void parseAngleReal(INI *, void *, void *, const void *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationNugget
{
public:
	virtual void create();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationList
{
public:
	void addObjectCreationNugget(ObjectCreationNugget *);
};

extern int R2Data0109F0F4;

class ApplyRandomForceNugget
{
public:
	static void parse(INI *ini, void *instance, void *store, const void *userData);
};

struct Rva001D8800Nugget
{
	Rva001D8800Nugget()
	{
		m_minMag = 0;
		m_maxMag = 0;
		m_minPitch = 0;
		m_maxPitch = 0;
		m_vtable = &R2Data0109F0F4;
	}

	void *m_vtable;
	int m_minMag;
	int m_maxMag;
	int m_minPitch;
	int m_maxPitch;
};

// ?parse@ApplyRandomForceNugget@@SAXPAVINI@@PAX1PBX@Z
void ApplyRandomForceNugget::parse(INI *ini, void *instance, void *store, const void *userData)
{
	static const FieldParse myFieldParse[] =
	{
		{ "MinForceMagnitude", INI::parseReal, 0, 0x04 },
		{ "MaxForceMagnitude", INI::parseReal, 0, 0x08 },
		{ "MinForcePitch", INI::parseAngleReal, 0, 0x0C },
		{ "MaxForcePitch", INI::parseAngleReal, 0, 0x10 },
		{ 0, 0, 0, 0 }
	};

	Rva001D8800Nugget *nugget = new Rva001D8800Nugget;
	ini->initFromINI(nugget, myFieldParse);
	((ObjectCreationList *)instance)->addObjectCreationNugget((ObjectCreationNugget *)nugget);
}
