// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// AudioManager per-time-of-day priority+volume override lookup, called from
// AudioManager::addAudioEventEx. Class layout (owner
// padb8[0xb8] + Entry[3] of 0x1c4B each, with an inline find-style helper at
// Entry+0x1b8) is proven by the already-landed 0x006AE150 body
// (game/GameEngine/Source/Common/Rva006AE150ScaledValue.cpp) and by the
// already-landed find-in-map wrapper pattern in
// game/GameEngine/Source/Common/BfmeConv906.cpp (BfmeThingPE::bfmeGoPE),
// which calls the very same pinned ?bfmeFindPE@BfmeSubPE@@QAEPAHH@Z used
// here. AudioEventRTS::m_eventInfo at +0x08 is proven by
// game/GameEngine/Source/Common/Audio/AudioEventRTS_bfmeGenerateFilename.cpp.

#define BfmeZeroRange (*(const float *)0x01075350)

enum AudioPriority { AP_RVA006AD590_PLACEHOLDER };

union Rva006AD590Slot
{
	int m_asInt;
	float m_asFloat;
};

// Same pinned lookup used by BfmeThingPE::bfmeGoPE (BfmeConv906.cpp).
struct BfmeSubPE
{
	int *m_bfmeFirst;
	int *bfmeFindPE(int k);
};

class Rva006AD590Info
{
public:
	virtual ~Rva006AD590Info();
	virtual int getNameKey() const;

	char m_pad04[0x0c];
	Rva006AD590Slot m_priority;	// +0x10
	char m_pad14[4];
	float m_defaultVolume;			// +0x18
};

class AudioEventRTS
{
public:
	void setAudioPriority(AudioPriority newPriority);
	void setVolume(float vol);

	char m_pad00[8];
	Rva006AD590Info *m_eventInfo;	// +0x08
	char m_pad0c[0x1c];
	int m_timeOfDay;				// +0x28
};

class Rva006AD590Entry
{
public:
	Rva006AD590Slot *find(int key)
	{
		int *r = m_map.bfmeFindPE(key);
		if (r == m_map.m_bfmeFirst)
			return 0;
		return (Rva006AD590Slot *)((char *)r + 0x14);
	}

	char m_pad[0x1b8];
	BfmeSubPE m_map;				// +0x1b8
	char m_tail[0x1c4 - 0x1b8 - 4];
};

class Rva006AD590Owner
{
public:
	void bfmeAdjustPriorityAndVolume(AudioEventRTS *event);

private:
	char m_padb8[0xb8];
	Rva006AD590Entry m_entries[3];
};

void Rva006AD590Owner::bfmeAdjustPriorityAndVolume(AudioEventRTS *event)
{
	int timeOfDay = event->m_timeOfDay;
	int key = event->m_eventInfo->getNameKey();

	Rva006AD590Slot *slot = m_entries[timeOfDay].find(key);
	if (slot)
	{
		event->setAudioPriority((AudioPriority)slot->m_asInt);
		Rva006AD590Info *info = event->m_eventInfo;
		float priority = info->m_priority.m_asFloat;
		if (priority > BfmeZeroRange)
		{
			float ratio = slot->m_asFloat / priority;
			event->setVolume(ratio * info->m_defaultVolume);
		}
	}
	else
	{
		event->setAudioPriority((AudioPriority)event->m_eventInfo->m_priority.m_asInt);
		event->setVolume(event->m_eventInfo->m_defaultVolume);
	}
}
