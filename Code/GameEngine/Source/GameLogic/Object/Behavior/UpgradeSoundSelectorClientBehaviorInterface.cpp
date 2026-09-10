// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UpgradeSoundSelectorClientBehavior's mapped-sound query.
// The secondary SoundSelectorInterface walks 0x210-byte upgrade records, tests
// the attached object against each record, and returns the mapped sound value.

typedef bool Bool;

extern "C" void *__cdecl memset(void *, int, unsigned int);

class ModuleData
{
public:
	virtual void anchor();

	unsigned int m_tag;
};

class ClientUpdateModule
{
public:
	virtual void anchor();

	ModuleData *m_moduleData;
	void *m_drawable;
};

struct BfmeSlotSD;
struct BfmeKeySD;

class SoundSelectorInterface
{
public:
	virtual BfmeSlotSD *findMappedSound(BfmeKeySD *key) = 0;
};

class BfmeMapSD
{
public:
	BfmeSlotSD *bfmeFindSD(BfmeKeySD *key);

	BfmeSlotSD *m_header;
	char m_pad[8];
};

struct SoundUpgradeRecord
{
	char m_body[0x1fc];
	BfmeMapSD m_map;
};

class UpgradeSoundSelectorClientBehaviorModuleData : public ModuleData
{
public:
	SoundUpgradeRecord *m_start;
	SoundUpgradeRecord *m_finish;
	SoundUpgradeRecord *m_end;
};

class UpgradeSoundSelectorClientBehavior : public ClientUpdateModule,
	public SoundSelectorInterface
{
public:
	virtual BfmeSlotSD *findMappedSound(BfmeKeySD *key);
};

class Rva006083A0SoundUpgrade
{
public:
	void buildMasks(unsigned int *first, unsigned int *second);
	Bool matchesObject(void *object);
};

class BfmeK1114
{
public:
	char bfmeChk1114(int index);
};

struct Rva006083A0MaskWords
{
	unsigned int values[6];
	Rva006083A0MaskWords()
	{
		memset(this, 0, sizeof(*this));
	}
};

// The two masks are populated by the existing 0x00608090 helper through its ILT.
#pragma comment(linker, "/alternatename:?buildMasks@Rva006083A0SoundUpgrade@@QAEXPAI0@Z=?j_0000f187@@YAXXZ")

// ?matchesObject@Rva006083A0SoundUpgrade@@QAE_NPAX@Z
Bool Rva006083A0SoundUpgrade::matchesObject(void *object)
{
	Rva006083A0MaskWords first;
	Rva006083A0MaskWords second;
	buildMasks(first.values, second.values);

	BfmeK1114 *upgrade = (BfmeK1114 *)object;
	int i;
	for (i = 0; i < 0xc0; ++i)
	{
		if ((first.values[(unsigned int)i >> 5] & (1u << (i & 0x1f))) &&
			!upgrade->bfmeChk1114(i))
			return false;
		if ((second.values[(unsigned int)i >> 5] & (1u << (i & 0x1f))) &&
			upgrade->bfmeChk1114(i))
			return false;
	}
	return true;
}

// 0x006083A0 tests the record's upgrade mask against the attached object.
#pragma comment(linker, "/alternatename:?matchesObject@Rva006083A0SoundUpgrade@@QAE_NPAX@Z=?j_000420b9@@YAXXZ")

// The existing BfmeMapSD implementation is reached through this ILT.
#pragma comment(linker, "/alternatename:?bfmeFindSD@BfmeMapSD@@QAEPAUBfmeSlotSD@@PAUBfmeKeySD@@@Z=?j_00020e7d@@YAXXZ")

// ?findMappedSound@UpgradeSoundSelectorClientBehavior@@UAEPAUBfmeSlotSD@@PAUBfmeKeySD@@@Z
BfmeSlotSD *UpgradeSoundSelectorClientBehavior::findMappedSound(BfmeKeySD *key)
{
	UpgradeSoundSelectorClientBehaviorModuleData *data =
		(UpgradeSoundSelectorClientBehaviorModuleData *)m_moduleData;
	void *drawable = m_drawable;
	void *upgrade = *(void **)((char *)drawable + 0xfc);
	if (upgrade == 0)
		return 0;

	SoundUpgradeRecord *finish = data->m_finish;
	for (SoundUpgradeRecord *record = data->m_start; record != finish;
		record = (SoundUpgradeRecord *)((char *)record + 0x210))
	{
		if (((Rva006083A0SoundUpgrade *)record)->matchesObject(upgrade))
		{
			BfmeMapSD *map = &record->m_map;
			BfmeSlotSD *node = map->bfmeFindSD(key);
			if (node == map->m_header)
				continue;
			void *sound = (void *)((char *)node + 0x14);
			if (sound != 0)
				return (BfmeSlotSD *)sound;
		}
	}
	return 0;
}
