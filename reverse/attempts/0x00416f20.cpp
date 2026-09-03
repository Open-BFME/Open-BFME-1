// ?getPerUnitFx@ThingTemplate@@QBEPAXH@Z
// partial score=0.8 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-

class BfmeFxLookup
{
public:
	virtual void *bfmeFind(int index);
};

class BfmeFxProvider
{
public:
	virtual void bfmeSlot00(void);
	virtual void bfmeSlot04(void);
	virtual void bfmeSlot08(void);
	virtual void bfmeSlot0C(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot1C(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot28(void);
	virtual BfmeFxLookup *bfmeGetLookup(void);
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);

	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeNextOverride;
	char m_bfmeMid[0xE0 - 0x08];
	void *m_table[1];
};

class ThingTemplate
{
public:
	void *getPerUnitFx(int index) const;

private:
	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeOverride;
	char m_bfmeMid[0x158 - 0x08];
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

	BfmeOverridable *o = self->m_bfmeOverride;
	if (o && o->m_bfmeNextOverride)
		o = o->m_bfmeNextOverride->friend_getFinalOverride();

	void *fx = o->m_table[idx];
	if (fx)
		return (char *)fx + 4;
	return 0;
}
