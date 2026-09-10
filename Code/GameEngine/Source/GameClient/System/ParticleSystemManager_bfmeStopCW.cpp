// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// Open-BFME5: the BFME particle-manager stop helper reached by
// BfmeHostCW::bfmeSpawnCW.  The target's retail body is 0x005CB590 (81 bytes).
// stlport

#define _STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_OWN_NAMESPACE 1
#include <hash_map>

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class AsciiStringCompareShim
{
public:
	int compare(const AsciiStringCompareShim &other) const;

private:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}

	int compare(const AsciiString &other) const
	{
		return ((const AsciiStringCompareShim *)this)->compare(
			(const AsciiStringCompareShim &)other);
	}

	~AsciiString() {}
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace rts
{
	template <class T>
	struct hash
	{
		unsigned int operator()(T value) const;
	};
}

class ParticleSystemTemplate
{
public:
	virtual ~ParticleSystemTemplate();

	void deleteInstance()
	{
		delete this;
	}
};

typedef _STL::hash_map<AsciiString, ParticleSystemTemplate *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > BfmeTemplateMap;

// This address-derived name is an existing route label, not a claim about the
// retail value class.  Its ABI is identical to the manager's value type; the
// cast below selects that known callee while preserving the real find route.
class Rva005C9B80Mapped
{
public:
	virtual ~Rva005C9B80Mapped();

	void deleteInstance()
	{
		delete this;
	}
};

typedef _STL::hash_map<AsciiString, Rva005C9B80Mapped *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > RetailEraseMap;

class ParticleSystemManager
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void reset();

	void bfmeStopCW(const AsciiString &name);

private:
	unsigned char m_beforeMap[0x98];
	BfmeTemplateMap m_templateMap;
};

void ParticleSystemManager::bfmeStopCW(const AsciiString &name)
{
	BfmeTemplateMap::iterator find(m_templateMap.find(name));
	if (find == m_templateMap.end())
		return;

	reset();
	(*find).second->deleteInstance();
	((RetailEraseMap &)m_templateMap).erase(
		(RetailEraseMap::iterator &)find);
}
