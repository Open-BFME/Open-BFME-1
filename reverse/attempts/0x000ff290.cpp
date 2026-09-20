// ?Rva000FF290@@YAXPAX@Z
// partial score=0.25 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: anonymous carved body at 0x000FF290 (452 bytes). vtable
// 0x01083B5C (only generated slots) is installed into a local
// PartitionFilterAcceptByKindOf, so this scans objects within a computed
// radius of the incoming object (this+0x70 * g_bfmeK1266A + this+0x3a4)
// through PartitionManager::iterateObjectsInRange (bfmeForwardWideC,
// BfmeWideResultForward.cpp), and for each candidate whose module-data
// getFinalOverride() flags clear four gates (+0xd0 bit 0x1000000, +0xc8
// bit 0x40, +0xcc bit 0x40000, this+0x344 bit 0, then +0xc8 bit 4 set)
// forwards it to g_bfmeTerrainVisual's vtable slot 0x5c(object,1,0). The
// caller and exact owning method are unproven (one carved caller, five
// resolved callees).

typedef float Real;

struct BitFlagsKindOf
{
	unsigned int m_bits[3];
};

extern const BitFlagsKindOf KINDOFMASK_NONE;

class PartitionFilter
{
public:
	virtual ~PartitionFilter();
	virtual bool shouldAccept(void *obj) const;
	virtual int getFilterID() const;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const BitFlagsKindOf &accept,
		const BitFlagsKindOf &reject);
};

struct BfmeWideResult
{
	unsigned char m_pad[8];
};

class PartitionManager
{
public:
	BfmeWideResult forwardWideC(Real x, Real y, Real z, int a, int b);
};

extern PartitionManager *ThePartitionManager;

extern "C" void *__cdecl bfmeGetFinalOverride(void *chain);

class Rva004FF290Object
{
public:
	void *m_moduleChain;
	unsigned char m_pad344[0x344];
	unsigned char m_flags344;
};

struct TerrainVisualLike
{
	void ***m_vptr;
};

extern TerrainVisualLike *g_bfmeTerrainVisual;

struct Rva004FF290Vector
{
	void *m_begin;
	void *m_endCapacity;
	void *m_end;
	void *m_endReserved;
};

extern "C" void *__cdecl bfmeGetFinalOverrideChain(void *object);

// address-derived identity: carved boundary evidence only, vtable
// 0x01083B5C has only generated slots
void Rva000FF290(void *thisObj)
{
	Rva004FF290Object *obj = (Rva004FF290Object *)thisObj;

	float radius = *(float *)((char *)obj + 0x70) * (*(float *)0x01075338)
		+ *(float *)((char *)obj + 0x3a4);

	PartitionFilterAcceptByKindOf filter(*(const BitFlagsKindOf *)0x012ed8b8,
		KINDOFMASK_NONE);

	Rva004FF290Vector iter;
	ThePartitionManager->forwardWideC((int)&iter, *(int *)&radius, 1,
		(int)&filter, 0);

	void **begin = (void **)iter.m_begin;
	void **end = (void **)iter.m_end;

	while (begin != end)
	{
		void *item = *begin;
		begin += 1;

		if (!item)
			continue;

		void *chain1 = *(void **)((char *)item + 4);
		if (chain1 && *(void **)((char *)chain1 + 4))
		{
			void *ov = bfmeGetFinalOverrideChain(chain1);
			if (*(unsigned int *)((char *)ov + 0xd0) & 0x1000000)
				continue;
		}

		void *chain2 = *(void **)((char *)item + 4);
		if (chain2 && *(void **)((char *)chain2 + 4))
		{
			void *ov = bfmeGetFinalOverrideChain(chain2);
			if (*(unsigned char *)((char *)ov + 0xc8) & 0x40)
				continue;
		}

		void *chain3 = *(void **)((char *)item + 4);
		if (chain3 && *(void **)((char *)chain3 + 4))
		{
			void *ov = bfmeGetFinalOverrideChain(chain3);
			if (*(unsigned int *)((char *)ov + 0xcc) & 0x40000)
				continue;
		}

		if (*(unsigned char *)((char *)item + 0x344) & 1)
			continue;

		void *chain4 = *(void **)((char *)item + 4);
		if (chain4 && *(void **)((char *)chain4 + 4))
		{
			void *ov = bfmeGetFinalOverrideChain(chain4);
			if (!(*(unsigned char *)((char *)ov + 0xc8) & 4))
				continue;
		}
		else
		{
			continue;
		}

		typedef void (__stdcall *NotifyFn)(void *, void *, int, int);
		(*(NotifyFn **)g_bfmeTerrainVisual->m_vptr)[0x5c / 4](
			g_bfmeTerrainVisual, item, 1, 0);
	}
}
