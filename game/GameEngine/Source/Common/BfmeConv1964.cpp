typedef bool Bool;

enum KindOfType
{
	KINDOF_INVALID = 0
};

// The kind query this TU calls is Thing::isKindOf(KindOfType) const; the real
// header declares the class, this TU only adds the member it calls.
#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType t) const;
#include "Thing/thing.h"
#undef THING_TU_MEMBERS

class BfmeInfoERW
{
public:
	unsigned char m_bfmeHeadERW[0x24];
	int m_bfmeValueERW;
};

// Retail reaches all three through the five-byte ILT thunks below, not
// through a body of their own: dis_retail 0x001CAA80 shows
// `mov ecx, ...; call ?j_0002369b@@YAXXZ`, `mov ecx, esi; call
// ?j_000212d8@@YAXXZ` and `mov ecx, esi; call ?j_00016d0b@@YAXXZ`, and
// the ledger defines exactly those names in game/gen_small/thunks_016,
// _015 and _010. Spell the references as the ledger spells them; the
// register cast below supplies the thiscall view the thunks tail-jump with.
extern void j_0002369b();
extern void j_000212d8();
extern void j_00016d0b();

class BfmeSubERWReceiver
{
};

template <class T> __forceinline T BfmeSubERWMember(void (*raw)())
{
	union
	{
		void (*raw)();
		T member;
	} fn;

	fn.raw = raw;

	return fn.member;
}

typedef BfmeInfoERW *(BfmeSubERWReceiver::*SubERWInfoFn)(void);
typedef char (BfmeSubERWReceiver::*SubERWFlagFn)(void);

#define SUB_ERW_CALL(T, obj, fn) \
	(((BfmeSubERWReceiver *)(obj))->*BfmeSubERWMember<T>(fn))

class BfmeSubERW;

class BfmeHostERW
{
public:
	int bfmeQueryERW();

	unsigned char m_bfmeHeadERW[0x1d0];
	BfmeSubERW *m_bfmeSubERW;
	unsigned char m_bfmeMidERW[0x104];
	unsigned char m_bfmeFlagsERW;
};

int BfmeHostERW::bfmeQueryERW()
{
	BfmeSubERW *sub = m_bfmeSubERW;

	if (sub != 0)
	{
		BfmeInfoERW *info = SUB_ERW_CALL(SubERWInfoFn, sub, j_0002369b)();

		if (info != 0)
		{
			if ((m_bfmeFlagsERW & 2) != 0)
				return -1;

			if (!((Thing *)((char *)this - 0x6c))->isKindOf((KindOfType)0x36))
			{
				sub = m_bfmeSubERW;

				if (sub != 0 && !SUB_ERW_CALL(SubERWFlagFn, sub, j_000212d8)() && !SUB_ERW_CALL(SubERWFlagFn, sub, j_00016d0b)())
					return info->m_bfmeValueERW;
			}
		}
	}

	return -1;
}
