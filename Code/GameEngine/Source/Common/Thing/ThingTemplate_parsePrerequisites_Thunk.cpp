// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// readable body of ?parsePrerequisites@ThingTemplate@@: Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp
// Open-BFME5: clean C++ for ThingTemplate::parsePrerequisites.
// Retail keeps instance in esi and INI in edi; CREATE_OVERRIDES (load-type
// at +8) erases m_prereqInfo [begin,end] at +0x2C4 via thiscall erase.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *store, const void *fieldParse);

	int m_unk0;
	int m_unk1;
	int m_loadType; // +8
};

class PrereqVector
{
public:
	// erase(first, last) — REL32 pins to retail range-destroy helper.
	void *erase(void *first, void *last);

	void *m_begin;
	void *m_end;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
protected:
	static void __cdecl parsePrerequisites(INI *ini, void *instance, void *store, const void *userData);
};

enum { INI_LOAD_CREATE_OVERRIDES = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
struct FieldParse
{
	const char *name;
	void (__cdecl *parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

void __cdecl parsePrerequisiteUnit(INI *, void *, void *, const void *);
void __cdecl parsePrerequisiteScience(INI *, void *, void *, const void *);

static const FieldParse s_prereqFieldParse[] =
{
	{ "Object", parsePrerequisiteUnit, 0, 0 },
	{ "Science", parsePrerequisiteScience, 0, 0 },
	{ 0, 0, 0, 0 }
};

// ?parsePrerequisites@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void __cdecl ThingTemplate::parsePrerequisites(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	unsigned char *self = (unsigned char *)instance;

	if (*(int *)((unsigned char *)ini + 8) == INI_LOAD_CREATE_OVERRIDES)
	{
		void *end = *(void **)(self + 0x2C8);
		void *beg = *(void **)(self + 0x2C4);
		PrereqVector *vec = (PrereqVector *)(self + 0x2C4);
		vec->erase(beg, end);
	}

	ini->initFromINI(self + 0x2C4, s_prereqFieldParse);
}
