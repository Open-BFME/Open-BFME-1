// ?parsePrerequisiteScienceOrGroup@@YAXPAVINI@@PAVProductionPrerequisite@@PAXPBX@Z
// partial score=0.15 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: anonymous carved body at 0x000BE440 (522 bytes). Retail parses
// Science prerequisites with an "OR" grouping extension over ZH's plain
// parsePrerequisiteScience (ParsePrerequisiteScienceThunk.cpp): tokens are
// read from the INI stream, "None" clears and stops, "OR" starts a new
// PrereqUnitRec group (via the already-matched gen_asm helper
// d_000be300, which indexes/grows the 12-byte-element m_prereqUnits
// vector), otherwise each token is looked up through
// ScienceStore::friend_lookupScience and appended to the current group's
// science list via the generated _M_insert_overflow thunk
// (0x00023588, Rva00023588ScienceVectorInsertThunk). At end of input the
// working ICoord2D-shaped group storage is compacted (divide-by-3 element
// count, vector<ICoord2D>::operator= copy per group) and the scratch
// vector-of-vectors is torn down. The exact 3-int meaning of PrereqUnitRec
// and the group compaction step are not independently proven; d_000be300
// remains an opaque (but already byte-matched) gen_asm callee.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *delims = 0);
};

class ScienceStore
{
public:
	ScienceType friend_lookupScience(const char *token);
};

extern ScienceStore *TheScienceStore;

extern "C" void *(__cdecl *g_lookup)(void *table, const char *key);

struct PrereqUnitRec
{
	unsigned int m_data[3];
};

class ProductionPrerequisite
{
public:
	_STL::vector<PrereqUnitRec> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<ScienceType> m_unused;
};

extern "C" void d_000be300(ProductionPrerequisite *self, int index);

extern "C" void Rva00023588ScienceVectorInsertThunk(
	_STL::vector<ScienceType> *v, ScienceType const *value, int a, int b);

// address-derived identity: only caller/method name unproven; matches the
// gen-thunk queue entry at 0x000083BE
void __cdecl parsePrerequisiteScienceOrGroup(INI *ini,
	ProductionPrerequisite *prereq, void *, const void *)
{
	d_000be300(prereq, 1);

	const char *token = ini->getNextTokenOrNull(0);

	while (token != 0)
	{
		if (g_lookup((void *)0x1082eec, token))
		{
			// "None": clear and stop entirely.
			break;
		}

		if (!g_lookup((void *)0x1082f50, token))
		{
			// Plain science token: append to the vector at the current
			// working PrereqUnitRec, growing it through d_000be300 when
			// it is the first token of a new group.
			if (((void **)&prereq->m_prereqUnits)[0] != ((void **)&prereq->m_prereqUnits)[1])
			{
				ScienceType science = TheScienceStore->friend_lookupScience(token);
				Rva00023588ScienceVectorInsertThunk(
					&prereq->m_prereqSciences, &science, 1, 1);
			}

			token = ini->getNextTokenOrNull(0);
			continue;
		}

		// "OR": start a new group.
		d_000be300(prereq, 1);
		token = ini->getNextTokenOrNull(0);
	}
}
