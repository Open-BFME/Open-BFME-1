// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006128F0: resolve an AsciiString through NameKeyGenerator, then
// search the LivingWorldManager tree at +0x27C.  The tree owns polymorphic
// pointers: the producer at 0x00614F50 allocates a 0x18-byte object, calls its
// constructor at 0x00618630, and stores the pointer through operator[] at
// 0x006148F0; the manager destructor at 0x00617FB0 calls
// mapped->vftable[0](1).  Keep the pointee neutral here because this lookup
// alone does not prove the concrete class.
//
// The map<int, BfmeLivingWorldMapObject *>::find instantiation has the same
// key-only 71-byte body as retail 0x00610950.  That body is byte-identical to
// 0x00473990, reached by the existing map<int, unsigned int>::find ILT at RVA
// 0x0000F03D; this is ICF evidence only, not evidence that the mapped value is
// an integer.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
// NameKeyType is an unscoped enum, not an int typedef: the return type is part
// of the mangled name retail spells ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z.
enum NameKeyType { };

// The tree at +0x27C is keyed on the plain int the map<int, ...>::find
// instantiation (the one this body byte-matches) is built with; the generator
// hands the key back as the enum above and the local is narrowed at the store.
typedef int NameKeyInt;

class AsciiString
{
public:
	char *m_data;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern const char g_bfmeEmptyAscii[];

class BfmeLivingWorldMapObject;
typedef _STL::map<NameKeyInt, BfmeLivingWorldMapObject *> BfmeLivingWorldNameMap;

class BfmeLivingWorldManager
{
public:
	void *rva006128f0(const AsciiString &name);

private:
	unsigned char m_unmodelled_000[0x27C];
	BfmeLivingWorldNameMap m_nameMap;
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

// ?rva006128f0@BfmeLivingWorldManager@@QAEPAXABVAsciiString@@@Z
void *BfmeLivingWorldManager::rva006128f0(const AsciiString &name)
{
	NameKeyInt key = (NameKeyInt)TheNameKeyGenerator->nameToKey(
		name.m_data != 0 ? name.m_data + 8 : g_bfmeEmptyAscii);
	if (key == 0)
	{
		return 0;
	}
	else
	{
		BfmeLivingWorldNameMap *table =
			&((BfmeLivingWorldManager *)TheLivingWorldManager)->m_nameMap;
		BfmeLivingWorldNameMap::iterator found = table->find(key);
		if (found == table->end())
			return 0;
		return (void *)found->second;
	}
}
