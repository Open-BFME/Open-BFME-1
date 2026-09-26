// ?d_000da060@@YAXXZ
// partial score=0.4 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>

#include "ascii_string.h"

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};

template <>
struct hash<AsciiString>
{
	unsigned int operator()(AsciiString value) const
	{
		return static_cast<unsigned int>(_STL::__stl_hash_string(value.str()));
	}
};
}

typedef _STL::pair<const AsciiString, float> Rva000DA060Pair;

typedef _STL::hashtable<Rva000DA060Pair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva000DA060Pair>, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000DA060Pair> > Rva000DA060Rooms;

typedef _STL::map<AsciiString, float> Rva000DA060FloatMap;

struct Rva000DA060Range
{
	unsigned int m_count;
	Rva000DA060FloatMap *m_map;
};

class Rva000DA060Owner
{
public:
	virtual ~Rva000DA060Owner();
	virtual void completeDestructor();
	virtual bool slot_08();
#define RVA_PAD(name) virtual void name();
	RVA_PAD(slot_0C)
	RVA_PAD(slot_10)
	RVA_PAD(slot_14)
	RVA_PAD(slot_18)
	RVA_PAD(slot_1C)
	RVA_PAD(slot_20)
	RVA_PAD(slot_24)
	RVA_PAD(slot_28)
	RVA_PAD(slot_2C)
	RVA_PAD(slot_30)
	RVA_PAD(slot_34)
	RVA_PAD(slot_38)
	RVA_PAD(slot_3C)
	RVA_PAD(slot_40)
	RVA_PAD(slot_44)
	RVA_PAD(slot_48)
	RVA_PAD(slot_4C)
	RVA_PAD(slot_50)
	RVA_PAD(slot_54)
	RVA_PAD(slot_58)
	RVA_PAD(slot_5C)
	RVA_PAD(slot_60)
	RVA_PAD(slot_64)
#undef RVA_PAD
	virtual void rewriteKey(const AsciiString &key);
	virtual void writeValue(float &value);
	virtual void slot_70();
	virtual void getRange(void *range);
};

void __stdcall Rva000DA060_trial6(Rva000DA060Owner *owner,
	Rva000DA060Rooms *rooms)
{
	if (owner->slot_08())
	{
		unsigned int count = *reinterpret_cast<unsigned int *>(
			reinterpret_cast<char *>(rooms) + 0x10);
		owner->getRange(&count);
		Rva000DA060Rooms::iterator it = rooms->begin();
		while (it._M_cur != 0)
		{
			AsciiString key = it->first;
			float value = it->second;
			owner->rewriteKey(key);
			owner->writeValue(value);
			++it;
		}
		return;
	}

	Rva000DA060Range range;
	range.m_count = 0;
	range.m_map = 0;
	owner->getRange(&range);
	for (unsigned int i = 0; i < range.m_count; ++i)
	{
		AsciiString key;
		float value = 0.0f;
		owner->rewriteKey(key);
		owner->writeValue(value);
		(*range.m_map)[key] = value;
	}
}
