// ?getPerUnitSound@ThingTemplate@@QBEPBVAudioEventRTS@@ABVAsciiString@@@Z
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-

class AsciiString;
class AudioEventRTS;

class BfmeSoundLookup
{
public:
	virtual void bfmeLookupSlot00(void);
	virtual const AudioEventRTS *bfmeFind(const AsciiString &name);
};

class BfmeSoundProvider
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
	virtual BfmeSoundLookup *bfmeGetLookup(void);
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);
	const AudioEventRTS *bfmeLookupPerUnitSound(const AsciiString &name);

	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeNextOverride;
};

extern AudioEventRTS BfmeTheEmptyAudioEvent;

class ThingTemplate
{
public:
	const AudioEventRTS *getPerUnitSound(const AsciiString &name) const;

private:
	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeOverride;
	char m_bfmeMid[0x158 - 0x08];
	BfmeSoundProvider **m_bfmeProviders;
};

const AudioEventRTS *ThingTemplate::getPerUnitSound(const AsciiString &name) const
{
	BfmeSoundProvider **provider = m_bfmeProviders;

	if (provider)
	{
		do
		{
			BfmeSoundProvider *entry = *provider;

			if (entry == 0)
				break;

			BfmeSoundLookup *lookup = entry->bfmeGetLookup();

			if (lookup)
			{
				const AudioEventRTS *sound = lookup->bfmeFind(name);

				if (sound)
					return sound;
			}
		}
		while (++provider);
	}

	BfmeOverridable *o = m_bfmeOverride;
	if (o)
	{
		if (o->m_bfmeNextOverride)
			o = o->m_bfmeNextOverride->friend_getFinalOverride();
	}
	else
		o = 0;

	const AudioEventRTS *sound = o->bfmeLookupPerUnitSound(name);

	if (sound)
		return sound;

	return &BfmeTheEmptyAudioEvent;
}
