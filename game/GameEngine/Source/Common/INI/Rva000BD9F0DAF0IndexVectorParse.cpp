// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// These are two BFME INI callbacks with the same source shape.  Each clears
// the destination vector, reads optional tokens, treats the literal None as
// an empty list, and appends the index returned by scanIndexList.  The retail
// bodies are distinct instantiations because their vector overflow calls land
// in different incremental-link aliases (0x004A7EB0 and 0x004BC8C0).
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;

// These are the already-proven four-byte POD vector element identities whose
// retail overflow bodies are the two incremental-link aliases used here.  The
// callback stores an index value in the element's first word; no class identity
// is inferred from these names.
struct Gen_t_000a8040_m4pod { int a[1]; };
struct Gen_t_000bd2f0_m4pod { int a[1]; };

// The operand at retail VA 0x0135933C is the MSVCR71 _strcmpi import.  Keep
// the import spelling exact; stricmp is a different CRT import identity.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0); // retail 0x008509C0
	static Int scanIndexList(const char *token, const char *const *names); // 0x008509E0
};

typedef _STL::vector<Gen_t_000a8040_m4pod> D9Vector;
typedef _STL::vector<Gen_t_000bd2f0_m4pod> DAVector;

// Address-derived callback names: the retail function signature is proven by
// the four callback slots and the stack cleanup in the complete COFF extent.
void Rva000BD9F0IndexVectorParse(INI *ini, void *, void *store,
	const void *userData)
{
	D9Vector *values = (D9Vector *)store;
	values->clear();
	for (const char *token = ini->getNextTokenOrNull(); token != 0;
		token = ini->getNextTokenOrNull())
	{
		if (_strcmpi(token, "None") == 0)
		{
			values->clear();
			return;
		}
		Gen_t_000a8040_m4pod value = {
			INI::scanIndexList(token, (const char *const *)userData)};
		values->push_back(value);
	}
}

void Rva000BDAF0IndexVectorParse(INI *ini, void *, void *store,
	const void *userData)
{
	DAVector *values = (DAVector *)store;
	values->clear();
	for (const char *token = ini->getNextTokenOrNull(); token != 0;
		token = ini->getNextTokenOrNull())
	{
		if (_strcmpi(token, "None") == 0)
		{
			values->clear();
			return;
		}
		Gen_t_000bd2f0_m4pod value = {
			INI::scanIndexList(token, (const char *const *)userData)};
		values->push_back(value);
	}
}
