// ?getPerUnitSound@ThingTemplate@@QBEPBVAudioEventRTS@@ABVAsciiString@@@Z
// partial score=0.951 date=2026-09-09
class AudioEventRTS;
class AsciiString;

extern AudioEventRTS BfmeTheEmptyAudioEvent;

class BfmePerUnitSoundFinder
{
public:
	virtual void unused();
	virtual const AudioEventRTS *find(const AsciiString &name);
};

class BfmePerUnitSoundEntry
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28();
	virtual BfmePerUnitSoundFinder *getFinder();
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class BfmeOverridable : public Overridable
{
public:
	const AudioEventRTS *bfmeLookupPerUnitSound(const AsciiString &name);
};

__forceinline BfmeOverridable *resolveParent(BfmeOverridable *parent)
{
	if (parent->m_nextOverride != 0)
		return (BfmeOverridable *)parent->m_nextOverride->getFinalOverride();
	return parent;
}

class ThingTemplate
{
public:
	const AudioEventRTS *getPerUnitSound(const AsciiString &name) const;

private:
	void *m_vtable;
	BfmeOverridable *m_parent;
	unsigned char m_unreconstructed08[0x150];
	BfmePerUnitSoundEntry **m_perUnitSounds;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

const AudioEventRTS *ThingTemplate::getPerUnitSound(const AsciiString &name) const
{
	const AsciiString *soundName = &name;
	_ReadWriteBarrier();
	BfmePerUnitSoundEntry **entry = m_perUnitSounds;
	if (entry != 0)
	{
		do
		{
			BfmePerUnitSoundEntry *current = *entry;
			if (current == 0)
				break;
			BfmePerUnitSoundFinder *finder = current->getFinder();
			if (finder != 0)
			{
				const AudioEventRTS *sound = finder->find(*soundName);
				if (sound != 0)
					return sound;
			}
			entry++;
		} while (entry != 0);
	}

	const AudioEventRTS *sound;
	if (m_parent == 0)
		sound = ((BfmeOverridable *)0)->bfmeLookupPerUnitSound(*soundName);
	else
		sound = resolveParent(m_parent)->bfmeLookupPerUnitSound(*soundName);
	if (sound != 0)
		return sound;
	return &BfmeTheEmptyAudioEvent;
}
