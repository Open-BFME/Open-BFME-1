// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// ScriptEngine reference copying: team003455E0 and unit00345260,413B each.
// Matched ScriptActions reference setters prove both public identities.
// Native maps have a pair<AsciiString,AsciiString> key; named insertion
// results finish record temporaries before copying the four-byte mapped ID.
// Retail EH maps prove eight unwind states. All seven emitted helpers were
// independently compared with their aligned retail call targets.

#include "ascii_string.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <utility>

// Defined in Common/game_type.h. MSVC supports this opaque enum declaration.
enum ObjectID;

template<>
inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class BfmeScriptEngineSlashName
{
public:
	AsciiString bfmeName(AsciiString &name);
};

typedef std::pair<AsciiString, AsciiString> Rva003455E0Key;

namespace _STL
{
template<> struct less<Rva003455E0Key>
{
	bool operator()(const Rva003455E0Key &left,
		const Rva003455E0Key &right) const
	{
		return left.first.compare(right.first) < 0
			|| (!(right.first.compare(left.first) < 0)
				&& left.second.compare(right.second) < 0);
	}
};
}

typedef unsigned int Rva003455E0MappedValue;
typedef std::map<Rva003455E0Key, Rva003455E0MappedValue>
	Rva003455E0Map;

typedef std::map<Rva003455E0Key, ObjectID> Rva00345260Map;

class ScriptEngine
{
	char m_beforeReferenceMaps[0x16058];
	Rva00345260Map m_unitReferences;
	Rva003455E0Map m_teamReferences;

public:
	void copyTeamReference(const AsciiString &name, AsciiString source);
	void copyUnitReference(const AsciiString &name, AsciiString source);
};

void ScriptEngine::copyTeamReference(const AsciiString &name,
	AsciiString source)
{
	if (source.isEmpty())
		return;

	AsciiString canonical =
		((BfmeScriptEngineSlashName *)this)->bfmeName(source);
	Rva003455E0Key sourceKey(canonical, source);

	Rva003455E0Map::iterator found = m_teamReferences.find(sourceKey);
	if (found == m_teamReferences.end())
		return;

	Rva003455E0Key destinationKey(
		*(const AsciiString *)((const char *)this + 0x17088), name);
	Rva003455E0MappedValue initial = 0;
	std::pair<Rva003455E0Map::iterator, bool> result =
		m_teamReferences.insert(std::make_pair(destinationKey, initial));
	result.first->second = found->second;
}

void ScriptEngine::copyUnitReference(const AsciiString &name,
	AsciiString source)
{
	if (source.isEmpty())
		return;

	AsciiString canonical =
		((BfmeScriptEngineSlashName *)this)->bfmeName(source);
	Rva003455E0Key sourceKey(canonical, source);

	Rva00345260Map::iterator found = m_unitReferences.find(sourceKey);
	if (found == m_unitReferences.end())
		return;

	Rva003455E0Key destinationKey(
		*(const AsciiString *)((const char *)this + 0x17088), name);
	ObjectID initial = static_cast<ObjectID>(0);
	std::pair<Rva00345260Map::iterator, bool> result =
		m_unitReferences.insert(std::make_pair(destinationKey, initial));
	result.first->second = found->second;
}
