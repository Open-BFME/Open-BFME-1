// ??0Rva0006AF00Entry@@QAE@PAVINI@@@Z
// partial score=0.15 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Open-BFME7: 0x0006AF00 (188 B), BFME-only (InPadding/OutPadding/Key are
// not in the Zero Hour reference tree). Builds a three-entry FieldParse
// table naming string literals "InPadding" (VA 0x1075AB8), "OutPadding"
// (VA 0x1075AA8) and "Key" (VA 0x1075AA4) -- the first two through the
// already-matched INI::parseIndexList, the third through the thunk at
// 0x0003A562 with userData 4 and offset 8 -- runs ini->initFromINI(this,
// table) and destructs a local temporary (j_00024000) before returning.
// This reads as a keyframe (curve control point) constructor called with
// a single INI* argument (thiscall, ret 4). Field offsets/table shape are
// a rough reconstruction; not yet byte-verified.

typedef int Int;

struct FieldParse;

class INI
{
public:
	static void parseIndexList( INI *ini, void *instance, void *store, const void *userData );
	void initFromINI( void *instance, const FieldParse *table );
};

struct FieldParseEntry
{
	const char *m_name;
	void (*m_parse)( INI *, void *, void *, const void * );
	const void *m_userData;
	Int m_offset;
};

class Rva0006AF00KeyIndices
{
public:
	Int m_a;
	Int m_b;
};

extern "C" void __cdecl Rva0006AF00ParseKey( INI *ini, void *instance, void *store, const void *userData );

class Rva0006AF00Entry
{
public:
	Rva0006AF00Entry( INI *ini );
};

// ??0Rva0006AF00Entry@@QAE@PAVINI@@@Z
Rva0006AF00Entry::Rva0006AF00Entry( INI *ini )
{
	Rva0006AF00KeyIndices indices;
	indices.m_a = 0;
	indices.m_b = 0;

	FieldParseEntry table[ 3 ] =
	{
		{ "InPadding",  INI::parseIndexList, (const void *)0, 0 },
		{ "OutPadding", INI::parseIndexList, (const void *)0, 0 },
		{ "Key",        Rva0006AF00ParseKey, (const void *)4, 8 },
	};

	ini->initFromINI( this, (const FieldParse *)table );
}
