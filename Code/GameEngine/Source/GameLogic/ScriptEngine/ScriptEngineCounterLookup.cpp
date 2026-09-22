// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ScriptEngine::bfmeCounter at00344C50/348B, named by matched counter callers
// through ILT00019ADD. The key has TWO AsciiStrings; the third live string
// is canonicalization's temporary, not another key field. Matched insertion
//003419F0 and its node allocation0033F4B0 prove key8 + counter8 at node+18.
// Native make_pair0033B800 (46B) and insert_unique003419F0 (505B) independently
// match. The comparator follows the latter's witnessed lexicographic order.
// A named insertion result completes pair temporaries before computing the
// returned counter address, matching the retail10-state unwind map.
#include "ascii_string.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <utility>
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;
};

class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);
};

typedef std::pair<AsciiString, AsciiString> Rva00344C50Key;

namespace _STL
{
template<> struct less<Rva00344C50Key>
{
	bool operator()(const Rva00344C50Key &left, const Rva00344C50Key &right) const
	{
		return left.first.compare(right.first) < 0
			|| (!(right.first.compare(left.first) < 0)
				&& left.second.compare(right.second) < 0);
	}
};
}

typedef std::map<Rva00344C50Key, ScriptCounter> Rva00344C50CounterMap;

typedef std::map<Rva00344C50Key, bool> Rva00344F40FlagMap;
typedef char CounterMapHasRetailSize[sizeof(Rva00344C50CounterMap) == 12 ? 1 : -1];

class ScriptEngine
{
	char m_beforeCounterMap[0x16040];
	Rva00344C50CounterMap m_counters;
	Rva00344F40FlagMap m_flags;

protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	bool *bfmeFlagForWrite(AsciiString name);
};

ScriptCounter *ScriptEngine::bfmeCounter(AsciiString name)
{
	AsciiString canonical = ((BfmeScriptEngineSlashName *)this)->bfmeName(name);
	Rva00344C50Key key(canonical, name);
	ScriptCounter initial = {0, false, false};
	std::pair<Rva00344C50CounterMap::iterator, bool> result =
		m_counters.insert(std::make_pair(key, initial));
	return &result.first->second;
}

// The adjacent writable-flag getter uses the same key and lifetime sequence.
// Matched setFlag/evaluateFlag callers prove bool storage, and retail uses
// the next twelve-byte map at +1604C. Its native insert_unique is00341C70.
bool *ScriptEngine::bfmeFlagForWrite(AsciiString name)
{
	AsciiString canonical = ((BfmeScriptEngineSlashName *)this)->bfmeName(name);
	Rva00344C50Key key(canonical, name);
	bool initial = false;
	std::pair<Rva00344F40FlagMap::iterator, bool> result =
		m_flags.insert(std::make_pair(key, initial));
	return &result.first->second;
}
