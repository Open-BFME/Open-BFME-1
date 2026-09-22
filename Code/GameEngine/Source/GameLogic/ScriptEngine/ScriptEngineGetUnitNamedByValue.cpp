// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Retail0x0034F570/420B. Native GameLogic hash-map lookup must be visible:
// a declaration alone introduces an extra whole-pair EH-state store.
// All four retail unwind states are retained; no nothrow annotation is added.
// The emitted findObjectByID82B, pair destructor76B and tree find431B each
// independently match their physical retail targets9A510/DFB20/340080.
//
// The ScriptEngine vtable at 0x010E7A30 puts the body in slot 27 (+0x6c),
// through ILT 0x00022156.  Call sites name that slot's ABI
// ScriptEngine::getUnitNamedByValue(AsciiString); the vtable and matched
// virtual callers establish ScriptEngine as the owner.
// The body itself proves the owner layout: m_callingObject, m_conditionObject,
// the reference map at +0x16058, and the named-object range at +0x1709c.

#include "ascii_string.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>
#include <utility>

// Retail calls the StringBase<char> release body directly for the by-value
// argument and both local strings.  Keep the canonical AsciiString layout and
// make its destructor the same inline forwarder used by the recovered BFME
// ScriptEngine reference-map twins.
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

// The named-object tail calls the matched StringBase<char>::compare body
// through ILT 0x000220C5 (retail target 0x0005FEB0); calling the canonical
// base declaration keeps that contract instead of using ascii_string.h's
// inline AsciiString comparison implementation.
// This is a unit-name lookup, not the nearby flag family: the historical
// 0x00344B20 findFlag row returns a counter, while 0x00344E10 isFlag returns
// bool.  Neither is used here.
__forceinline int bfmeCompareAscii(const AsciiString &left,
	const AsciiString &right)
{
	return ((const StringBase<char> *)&left)->compare(
		*(const StringBase<char> *)&right);
}

class Object;
typedef int ObjectID;

// This is the matched BFME1 body at 0x0009A510, not the later ZH flat-vector
// replacement.  The ZH GameLogic.h keeps this hash_map implementation in a
// commented block; the matched BFME reconstruction is visible here so the
// caller sees the real bucket lookup and its actual non-throwing native path.
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

private:
	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;
};

inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;

	ObjectPtrHash::iterator it = m_objHash.find(id);
	if (it == m_objHash.end())
		return 0;

	return (*it).second;
}

extern GameLogic *TheBfmeGameLogic;

class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);
};

// The reference-map twins at 0x00345260/0x003455E0 prove this is an STLport
// map keyed by (canonical name, source name), with ObjectID as the mapped
// value.  Its _M_find body at 0x00340080 takes this map and a key reference,
// returns the tree node, and stores the mapped ID at node+0x18.
typedef std::pair<AsciiString, AsciiString> ScriptReferenceKey;

namespace _STL
{
template <> struct less<ScriptReferenceKey>
{
	bool operator()(const ScriptReferenceKey &left,
		const ScriptReferenceKey &right) const
	{
		return left.first.compare(right.first) < 0
			|| (!(right.first.compare(left.first) < 0)
				&& left.second.compare(right.second) < 0);
	}
};
}

typedef std::map<ScriptReferenceKey, ObjectID> ScriptReferenceMap;

struct NamedObjectEntry
{
	AsciiString m_name;
	Object *m_object;
};

class ScriptEngine
{
public:
#define SLOT(n) virtual void slot##n() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06)
	SLOT(07) SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
	SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20)
	SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26)
	virtual Object *getUnitNamedByValue(AsciiString name);
#undef SLOT

private:
	// The vptr occupies the first four bytes, hence 0x16054 reaches the
	// witnessed map at this+0x16058.
	char m_beforeReferenceMaps[0x16054];
	ScriptReferenceMap m_unitReferences;
	char m_beforeCallingObject[0x102c];
	Object *m_callingObject;       // +0x17090
	char m_betweenContextFields[4];
	Object *m_conditionObject;     // +0x17098
	NamedObjectEntry *m_namedObjectsBegin; // +0x1709c
	NamedObjectEntry *m_namedObjectsEnd;   // +0x170a0
};

#define BFME_THIS_OBJECT "<This Object>" // witnessed at retail VA010E7F94

Object *ScriptEngine::getUnitNamedByValue(AsciiString name)
{
	if (name.compare(BFME_THIS_OBJECT) == 0)
	{
		if (m_callingObject)
			return m_callingObject;
		return m_conditionObject;
	}

	{
		AsciiString canonical =
			((BfmeScriptEngineSlashName *)this)->bfmeName(name);
		ScriptReferenceKey key(canonical, name);
		ScriptReferenceMap::iterator found = m_unitReferences.find(key);
		if (found != m_unitReferences.end())
			return TheBfmeGameLogic->findObjectByID(found->second);
	}
	NamedObjectEntry *it = m_namedObjectsBegin;
	NamedObjectEntry *end = m_namedObjectsEnd;
	while (it != end)
	{
		if (bfmeCompareAscii(name, it->m_name) == 0)
			return it->m_object;
		++it;
	}

	return 0;
}
