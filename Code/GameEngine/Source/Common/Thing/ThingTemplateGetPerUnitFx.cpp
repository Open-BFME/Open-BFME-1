// ?getPerUnitFx@ThingTemplate@@QBEPAXH@Z
// Retail RVA 0x00416F20. The callers at 0x00416FA0 and 0x00416FC0 identify
// this body as ThingTemplate's indexed per-unit FX lookup.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeFxLookup
{
public:
	virtual void *bfmeFind(int index);
};

class BfmeFxProvider
{
public:
	virtual void bfmeSlot00(void); virtual void bfmeSlot04(void);
	virtual void bfmeSlot08(void); virtual void bfmeSlot0C(void);
	virtual void bfmeSlot10(void); virtual void bfmeSlot14(void);
	virtual void bfmeSlot18(void); virtual void bfmeSlot1C(void);
	virtual void bfmeSlot20(void); virtual void bfmeSlot24(void);
	virtual void bfmeSlot28(void);
	virtual BfmeFxLookup *bfmeGetLookup(void);
};

class BfmeSubBIA
{
public:
	int ask(void);

	void *m_vtable;
	BfmeSubBIA *m_bfmeNextOverride;
	char m_bfmeMid[0xD8];
	void *m_table[1];
};

class ThingTemplate : public BfmeSubBIA
{
public:
	void *getPerUnitFx(int index) const;

private:
	char m_bfmeMid[0x74];
	BfmeFxProvider **m_bfmeProviders;
};

void *ThingTemplate::getPerUnitFx(int index) const
{
	int idx = index;
	const ThingTemplate *self = this;
	BfmeFxProvider **provider = self->m_bfmeProviders;

	if (provider)
	{
		do
		{
			BfmeFxProvider *entry = *provider;
			if (entry == 0)
				break;

			BfmeFxLookup *lookup = entry->bfmeGetLookup();
			if (lookup)
			{
				void *fx = lookup->bfmeFind(idx);
				if (fx)
					return fx;
			}
		}
		while (++provider);
	}

	BfmeSubBIA *o = self->m_bfmeNextOverride;
	if (o && o->m_bfmeNextOverride)
		o = (BfmeSubBIA *)o->m_bfmeNextOverride->ask();

	void *fx = o->m_table[idx];
	if (fx)
		fx = (char *)fx + 4;
	else
	{
		// Keep MSVC's two retail return tails separate without emitting bytes.
		_ReadWriteBarrier();
		fx = 0;
	}
	return fx;
}
