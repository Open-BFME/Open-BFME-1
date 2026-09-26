// cl: /EHsc /MD /O2 /GR- /EHsc- /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x0039CB60 (314 bytes), between LightPointSystem::addLevel and
// INI::parseLightPointLevel and called once from bfmeGoBRB.  It finds the
// LightPointSystem level (final override) whose name matches and records its
// index in a unique-integer store, inlining the store's matched add
// (0x0039C8C0).  The method is not proven, so it keeps the address.

#include <cstring>

extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);

#define memmove (*bfme_memmove_ptr)
#include <vector>
#undef memmove

#include "ascii_string.h"

struct Gen_t_000bbe70_m4pod { int a[1]; };
bool operator==(const Gen_t_000bbe70_m4pod &, const Gen_t_000bbe70_m4pod &);
bool operator<(const Gen_t_000bbe70_m4pod &, const Gen_t_000bbe70_m4pod &);

namespace _STL
{
template <> struct __type_traits<Gen_t_000bbe70_m4pod> : __type_traits_aux<1> {};
}

class BfmeUniqueIntegerStoreC8C0
{
public:
	__forceinline void add(int value)
	{
		Gen_t_000bbe70_m4pod *at = m_values.begin();
		Gen_t_000bbe70_m4pod *end = m_values.end();
		while (at != end)
		{
			if (at->a[0] == value)
				return;
			++at;
		}
		Gen_t_000bbe70_m4pod *item = (Gen_t_000bbe70_m4pod *)&value;
		m_values.push_back(*item);
	}

private:
	char m_bfmePrefix[8];
	_STL::vector<Gen_t_000bbe70_m4pod> m_values;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	// A visible out-of-line body lets MSVC keep the name's data across the
	// call, as retail does; the call itself still binds to the pinned ILT.
	__declspec(noinline) const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

class LightPointLevel : public Overridable
{
public:
	unsigned char m_pad08[0x0c - 0x08];
	AsciiString m_name;
};

class LightPointSystem
{
public:
	void rva0039CB60(BfmeUniqueIntegerStoreC8C0 *indices, const AsciiString &name);

private:
	char m_pad[8];
	_STL::vector<LightPointLevel *> m_levels;
};

// ?rva0039CB60@LightPointSystem@@QAEXPAVBfmeUniqueIntegerStoreC8C0@@ABVAsciiString@@@Z
void LightPointSystem::rva0039CB60(BfmeUniqueIntegerStoreC8C0 *indices, const AsciiString &name)
{
	for (unsigned int i = 0; i < m_levels.size(); ++i)
	{
		const LightPointLevel *level = (const LightPointLevel *)m_levels[i]->getFinalOverride();
		if (level->m_name.compare(name) == 0)
		{
			indices->add(i);
			return;
		}
	}
}
