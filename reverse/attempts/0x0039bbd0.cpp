// ?bfmeIndexOf@BfmeSpecialPowerAllowanceStore@@AAEHPBVSpecialPowerTemplate@@@Z
// partial score=0.35 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BfmeSpecialPowerAllowanceStore::bfmeIndexOf, retail 0x0039BBD0,
// 195 bytes. Named by the already-matched _bfme_allows walk, which treats a
// negative answer as "allowed". Kept in its own TU so that caller cannot
// inline this body and break the 61-byte match at 0x0039BE50.
//
// Two nested pointer vectors: store+0x08/+0x0C of group records, each group
// holding a pointer vector at +0x14/+0x18. The search key is SpecialPower
// template+0x10 after the same one-level override walk _bfme_allows uses.
// The first next-override pointer is hoisted out of the inner loop; the
// inner and outer counts are re-read from the vectors each iteration.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable *friend_getFinalOverride(void);		// ILT 0x00048C61

	char m_bfmeHeadA[0x04];
	Overridable *m_bfmeNextOverride;			// +0x04
	char m_bfmeHeadB[0x10 - 0x08];
	void *m_bfmeKey;					// +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
};

class BfmeAllowanceGroup
{
public:
	char m_bfmeHead[0x14];
	void **m_bfmeBegin;					// +0x14
	void **m_bfmeEnd;					// +0x18
};

class BfmeSpecialPowerAllowanceStore
{
private:
	Int bfmeIndexOf(const SpecialPowerTemplate *tmpl);

	char m_bfmeHead[0x08];
	BfmeAllowanceGroup **m_bfmeBegin;			// +0x08
	BfmeAllowanceGroup **m_bfmeEnd;				// +0x0C
};

// ?bfmeIndexOf@BfmeSpecialPowerAllowanceStore@@AAEHPBVSpecialPowerTemplate@@@Z
Int BfmeSpecialPowerAllowanceStore::bfmeIndexOf(const SpecialPowerTemplate *tmpl)
{
	BfmeSpecialPowerAllowanceStore *self = this;
	BfmeAllowanceGroup **end = self->m_bfmeEnd;
	BfmeAllowanceGroup **begin = self->m_bfmeBegin;
	unsigned outer = (unsigned)(end - begin);
	unsigned i = 0;

	while (i < outer)
	{
		BfmeAllowanceGroup *group = begin[i];
		void **innerBegin = group->m_bfmeBegin;
		void **innerEnd = group->m_bfmeEnd;
		unsigned inner = (unsigned)(innerEnd - innerBegin);
		unsigned j = 0;
		Overridable *next = tmpl->m_bfmeNextOverride;

		while (j < inner)
		{
			const Overridable *finalTmpl;

			if (next)
			{
				if (next->m_bfmeNextOverride)
					finalTmpl = next->m_bfmeNextOverride->friend_getFinalOverride();
				else
					finalTmpl = next;
			}
			else
			{
				finalTmpl = tmpl;
			}

			if (innerBegin[j] == finalTmpl->m_bfmeKey)
				return (Int)i;

			++j;
			inner = (unsigned)(group->m_bfmeEnd - group->m_bfmeBegin);
		}

		++i;
		begin = self->m_bfmeBegin;
		end = self->m_bfmeEnd;
		outer = (unsigned)(end - begin);
	}

	return -1;
}
