// ?parseFXListDefinition@FXListStore@@SAXPAVINI@@@Z
// partial score=0.78 date=2026-09-26
// ?parseFXListDefinition@FXListStore@@SAXPAVINI@@@Z
// Structural trial: use the pinned initializer ABI that returns this in EAX.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport

#include <hash_map>
#include "StringInline.h"

struct FieldParse;
enum NameKeyType { NAMEKEY_INVALID = 0 };
class INI { public: const char *getNextToken(const char *seps); void initFromINI(void *store, const FieldParse *parse); };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *name); };
extern NameKeyGenerator *TheNameKeyGenerator;
extern const FieldParse TheFXListFieldParse[];

class BfmeThingASA
{
public:
	BfmeThingASA *bfmeBaseASA(void *one);
	unsigned char m_storage[36];
};
#pragma comment(linker, "/alternatename:?bfmeBaseASA@BfmeThingASA@@QAEPAV1@PAX@Z=?bfmeBaseASA@BfmeThingASA@@QAEXPAX@Z")

class FXList
{
public:
	FXList(const FXList &);
	~FXList();
	void clear();
};

struct BfmeOutDOG { int m_bfmeA; unsigned char m_bfmeValue[36]; };
extern BfmeOutDOG *bfmeGoDOG(BfmeOutDOG *out, int *src, void *arg);
typedef _STL::hash_map<int, FXList, _STL::hash<int>, _STL::equal_to<int> > FXListMap;

class FXListStore
{
public:
	static void parseFXListDefinition(INI *ini);
	unsigned char m_pad[8];
	FXListMap m_fxmap;
};
extern FXListStore *TheFXListStore;

void FXListStore::parseFXListDefinition(INI *ini)
{
	const char *c = ini->getNextToken(0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(c);
	AsciiString name(c);
	BfmeThingASA built;
	BfmeOutDOG temporary;
	BfmeOutDOG *pair = bfmeGoDOG(&temporary, (int *)&key, built.bfmeBaseASA((void *)&name));
	struct RawPair { int key; unsigned char value[36]; } entry;
	entry.key = pair->m_bfmeA;
	new ((void *)entry.value) FXList(*(const FXList *)pair->m_bfmeValue);
	FXListMap::iterator it = TheFXListStore->m_fxmap.insert(*(const FXListMap::value_type *)&entry).first;
	FXList &fxl = (*it).second;
	fxl.clear();
	ini->initFromINI(&fxl, TheFXListFieldParse);
	((FXList *)entry.value)->~FXList();
	((FXList *)temporary.m_bfmeValue)->~FXList();
	((FXList *)&built)->~FXList();
}
