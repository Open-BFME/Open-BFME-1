// ?rva008C6AD0@@YAPAVAptValue@@PAXH@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008C6AD0 (233 bytes, ret then int3 padding): an Apt callback of
// the (void *, int count) shape of its neighbour 0x008C6800 that converts the
// value on top of the Apt stack to an AptBoolean.  No caller, data reference
// or dispatch-table slot names it, so the name keeps the address.  The +4
// type/defined bits and the +8 Boolean payload follow AptValue_toNumber.cpp
// and AptBooleanCreate.cpp; with no arguments it returns g_bfmeFallbackDB.
//
// Shape: the two number tests are one inline predicate with early returns,
// and the per-type conversion is a second inline helper written as an if
// chain; retail keeps its `cmp 5/6/7` chain and duplicate number compare.
// The case-5 Boolean goes through a named local (retail spills it into the
// count argument's home).  The non-number path's `!check && number != 0`
// keeps its compare as the copy the helper's number case jumps back into.
class Rva8CD130Value;

class AptValue
{
public:
	float toNumber();
	int getType() const { return m_valueBits & 63; }
	bool isUndefined() const { return ((m_valueBits >> 15) & 1) == 0; }

	void *m_vtable;
	unsigned int m_valueBits;
	bool m_boolean;
};

class AptBoolean : public AptValue
{
public:
	static AptBoolean *Create(bool value);
};

struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue **m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue *g_bfmeFallbackDB;
extern const float g_rva01075350;

bool __cdecl Rva008C4A30Check(Rva8CD130Value *value);

static __forceinline bool isNumber(const AptValue *value)
{
	if (value->getType() == 6 && !value->isUndefined())
		return true;
	if (value->getType() == 7 && !value->isUndefined())
		return true;
	return false;
}

static __forceinline AptBoolean *toBooleanValue(AptValue *value)
{
	int type = value->getType();
	if (type == 5)
	{
		bool b = value->m_boolean;
		return AptBoolean::Create(b);
	}
	if (type == 6 || type == 7)
	{
		if (value->toNumber() == g_rva01075350)
			return AptBoolean::Create(false);
		return AptBoolean::Create(true);
	}
	return AptBoolean::Create(false);
}

AptValue *rva008C6AD0(void *, int count)
{
	if (count == 0)
		return g_bfmeFallbackDB;

	Rva008AE770Stack &stack = Rva008AE770TheStack;
	AptValue *value = stack.m_rva01338750[stack.m_count - 1];
	int type = value->getType();
	if (type >= 12 && type <= 19 && !value->isUndefined())
		return AptBoolean::Create(true);
	if (type == 27 && !value->isUndefined())
		return AptBoolean::Create(true);
	if (value == g_bfmeFallbackDB)
		return AptBoolean::Create(false);
	if (!isNumber(value))
	{
		if (!Rva008C4A30Check((Rva8CD130Value *)value) && value->toNumber() != g_rva01075350)
			return AptBoolean::Create(true);
		return AptBoolean::Create(false);
	}
	return toBooleanValue(value);
}
