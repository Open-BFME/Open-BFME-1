// ?rva00734790@Rva00734790Owner@@QAEXH@Z
// partial score=0.63 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// BFME W3DTreeBuffer per-tree topple/push-aside fade update, retail
// 0x00734790 (218 bytes).
//
// Identity: same owner as the landed 0x00733F50/0x00733FD0 and banked
// 0x00734180 -- 0xE8-byte tree-record stride, +0x2A7CB0 numTrees guard.
// This body walks tree[index], decrements an UnsignedInt countdown at
// +0x284, divides it by a per-tree-type duration read from
// (this+0x2A7CDC+state*0x5C)+0x4C, and forwards the resulting fraction
// through the landed Rva00739900Forward(void*, int-bits-of-float) to the
// tree's m_toppleObject (+0x288, fraction as-is) and m_pushAsideObject
// (+0x28C, g_bfmeDefaultBU minus the fraction). Two busy-flag guards
// (+0x274 nonzero or +0x230 nonzero) skip straight to the removal call
// unconditionally; the normal path only removes when the freshly re-read
// countdown has reached zero. Removal goes through the landed
// removeTreeAtIndex thunk j_0001512c (target FUN_00b33fd0 == 0x00733FD0).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

extern const float g_bfmeDefaultBU;

extern "C" unsigned char Rva00739900Forward(void *object, int value);
extern void j_0001512c(void);

struct Rva00734790TreeTypeData
{
	unsigned char m_pad00[0x4C];
	UnsignedInt m_duration;
};

struct Rva00734790TreeType
{
	Rva00734790TreeTypeData *m_data;
	unsigned char m_pad04[0x5C - 4];
};

class Rva00734790Owner
{
public:
	void rva00734790(Int index);

private:
	unsigned char m_pad0000[0x2A7CB0];
	Int m_numTrees;
};

// ?rva00734790@Rva00734790Owner@@QAEXH@Z
void Rva00734790Owner::rva00734790(Int index)
{
	if (index >= m_numTrees)
		return;

	unsigned char *tree = reinterpret_cast<unsigned char *>(this) + (unsigned)index * 0xE8;
	Int state0 = *(Int *)(tree + 0x1F0);

	if (state0 < 0)
		return;

	if (*(UnsignedByte *)(tree + 0x274) != 0)
		goto do_remove;
	if (*(Int *)(tree + 0x230) != 0)
		goto do_remove;

	{
		UnsignedInt count = *(UnsignedInt *)(tree + 0x284) - 1;
		*(UnsignedInt *)(tree + 0x284) = count;
		float fraction = (float)count;

		Rva00734790TreeType *type = reinterpret_cast<Rva00734790TreeType *>(
			reinterpret_cast<unsigned char *>(this) + 0x2A7CDC + state0 * 0x5C);
		float durationF = (float)type->m_data->m_duration;

		fraction /= durationF;

		void *toppleObject = *(void **)(tree + 0x288);
		if (toppleObject)
			Rva00739900Forward(toppleObject, *(int *)&fraction);

		void *pushAsideObject = *(void **)(tree + 0x28C);
		if (pushAsideObject) {
			float inverse = g_bfmeDefaultBU - fraction;
			Rva00739900Forward(pushAsideObject, *(int *)&inverse);
		}

		if (*(Int *)(tree + 0x284) != 0)
			return;
	}

do_remove:
	{
		typedef void (Rva00734790Owner::*RemoveOperation)(Int);
		union {
			void (*function)(void);
			RemoveOperation member;
		} removeCast;
		removeCast.function = j_0001512c;
		(this->*removeCast.member)(index);
	}
}
