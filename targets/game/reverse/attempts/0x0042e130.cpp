// ?parseFXListDefinition@FXListStore@@SAXPAVINI@@@Z
// partial score=0.72 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Open-BFME5: FXListStore::parseFXListDefinition at 0x0042E130 (319B).
// Retail builds an AsciiString from the token, constructs FXList(name),
// insert_unique's the (NameKey, FXList) pair after hashtable::resize,
// then clear + initFromINI on the mapped value.  Field table 0x010F2118.

#include <hash_map>
#include "StringInline.h"

struct FieldParse;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *store, const FieldParse *parse);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	FXList(const AsciiString &name);
	FXList(const FXList &);
	~FXList();
	void clear();

private:
	void *m_vftable;
	void *m_nuggets;
	unsigned char m_flag08;
	unsigned char m_pad09[3];
	AsciiString m_name;
	unsigned char m_playEvenIfShrouded;
	unsigned char m_pad11[3];
	unsigned int m_trackingFrames;
	void *m_playTimes;
	unsigned int m_startCullingAbove;
	unsigned int m_cullAllAbove;
};

typedef _STL::hash_map<int, FXList, _STL::hash<int>, _STL::equal_to<int> > FXListMap;

class FXListStore
{
public:
	static void parseFXListDefinition(INI *ini);

	unsigned char m_pad[8];
	FXListMap m_fxmap;
};

extern FXListStore *TheFXListStore;
extern const FieldParse TheFXListFieldParse[];

// ?parseFXListDefinition@FXListStore@@SAXPAVINI@@@Z
void FXListStore::parseFXListDefinition(INI *ini)
{
	const char *c = ini->getNextToken(0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(c);
	AsciiString name(c);
	FXList built(name);
	FXListMap::value_type entry(key, built);
	FXListMap::iterator it = TheFXListStore->m_fxmap.insert(entry).first;
	FXList &fxl = (*it).second;
	fxl.clear();
	ini->initFromINI(&fxl, TheFXListFieldParse);
}
