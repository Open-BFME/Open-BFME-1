// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: UpgradeSoundSelectorClientBehavior's mapped-sound query.
// The secondary SoundSelectorInterface walks 0x210-byte upgrade records, tests
// the attached object against each record, and returns the mapped sound value.

typedef bool Bool;

extern "C" void *__cdecl memset(void *, int, unsigned int);

#include <bitset>

class ModuleData
{
public:
	virtual void anchor();

	unsigned int m_moduleTagNameKey;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	struct Data
	{
		int references;
		unsigned short length;
		unsigned short reserved;
		char text[1];
	};

	Data *m_data;

public:
	bool isEmpty() const
	{
		return !m_data || m_data->length == 0;
	}

	bool isNone() const;
	const char *str() const
	{
		return m_data ? m_data->text : (const char *)0x0107388B;
	}

	void set(const AsciiString &source);
	AsciiString &operator=(const AsciiString &source)
	{
		set(source);
		return *this;
	}
	~AsciiString();
};

class UpgradeTemplate
{
public:
	unsigned int getUpgradeMask() const
	{
		return m_upgradeMask;
	}

private:
	char m_unmodelled[0x20];
	unsigned int m_upgradeMask;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

class INIException
{
public:
	char *m_failureMessage;
	int m_argCount;
	INIException(int argCount, const char *message, ...);
	INIException(const INIException &that);
	~INIException();
};

extern UpgradeCenter *TheUpgradeCenter;

class Rva006083A0StringVector
{
public:
	typedef const AsciiString *const_iterator;

	bool empty() const
	{
		return m_begin == m_end;
	}

	const_iterator begin() const
	{
		return m_begin;
	}

	const_iterator end() const
	{
		return m_end;
	}

	void clear()
	{
		erase(m_begin, m_end);
	}

private:
	__forceinline AsciiString *erase(AsciiString *first, AsciiString *last)
	{
		AsciiString *source = last;
		AsciiString *destination = first;
		int count = m_end - last;
		while (count > 0)
		{
			*destination = *source;
			++source;
			++destination;
			--count;
		}

		AsciiString *oldEnd = m_end;
		for (AsciiString *current = destination; current != oldEnd; ++current)
			current->~AsciiString();
		m_end = destination;
		return first;
	}

	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct Rva006083A0MaskWords
{
	unsigned int values[6];

	Rva006083A0MaskWords()
	{
		memset(this, 0, sizeof(*this));
	}

	void clear()
	{
		values[0] = 0;
		values[1] = 0;
		values[2] = 0;
		values[3] = 0;
		values[4] = 0;
		values[5] = 0;
	}

	void set(unsigned int bit)
	{
		unsigned int *word = &values[bit >> 5];
		*word |= 1u << (bit & 0x1f);
	}
};

class Rva006083A0UpgradeMask
{
public:
	void clear()
	{
		m_bits.reset();
	}

	void set(unsigned int bit)
	{
		m_bits._Unchecked_set(bit);
	}

private:
	_STL::bitset<192> m_bits;
};

class Rva006083A0SoundUpgrade
{
public:
	void buildMasks(unsigned int *first, unsigned int *second);
	Bool matchesObject(void *object);

private:
	Rva006083A0UpgradeMask m_firstMask;
	Rva006083A0UpgradeMask m_secondMask;
	Rva006083A0StringVector m_firstNames;
	Rva006083A0StringVector m_secondNames;
};

class BfmeK1114
{
public:
	char bfmeChk1114(int index);
};

// ?buildMasks@Rva006083A0SoundUpgrade@@QAEXPAI0@Z
void Rva006083A0SoundUpgrade::buildMasks(unsigned int *first, unsigned int *second)
{
	if (!m_firstNames.empty() || !m_secondNames.empty())
	{
		m_firstMask.clear();
		m_secondMask.clear();

		Rva006083A0StringVector::const_iterator it;
		for (it = m_firstNames.begin(); it != m_firstNames.end(); ++it)
		{
			const UpgradeTemplate *theTemplate =
				TheUpgradeCenter->findUpgrade(*it);
			if (!theTemplate && !it->isEmpty() && !it->isNone())
			{
				throw INIException(3,
					"An upgrade module references %s, which is not an Upgrade", it->str());
			}

			m_firstMask.set(theTemplate->getUpgradeMask());
		}

		for (it = m_secondNames.begin(); it != m_secondNames.end(); ++it)
		{
			const UpgradeTemplate *theTemplate =
				TheUpgradeCenter->findUpgrade(*it);
			if (!theTemplate && !it->isEmpty() && !it->isNone())
			{
				throw INIException(3,
					"An upgrade module references %s, which is not an Upgrade", it->str());
			}

			m_secondMask.set(theTemplate->getUpgradeMask());
		}

		m_firstNames.clear();
		m_secondNames.clear();
	}

	*(Rva006083A0MaskWords *)first =
		*(Rva006083A0MaskWords *)&m_firstMask;
	*(Rva006083A0MaskWords *)second =
		*(Rva006083A0MaskWords *)&m_secondMask;
}

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
