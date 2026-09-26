// cl: /DNDEBUG /MD /EHsc
//
// Retail LivingWorldRegion spawn-data family.  The campaign parser constructs
// 0xF4-byte regions through 0x0061AF80, which installs vtable 0x01117258 and
// initializes the vector at +0xD4.  The destructor at 0x0061A780 destroys that
// same vector.  Manager code calls 0x0061A860 to assign it, while 0x003C75A0
// iterates the campaign's region pointers and calls 0x0061AB60.
//
// The vector's lexical member name is unknown.  Rva0076F980Mid is a lexically
// neutral typed view of its actual three-pointer vector<AsciiString> ABI.

class AsciiString;

class Rva0076F980Mid
{
public:
	Rva0076F980Mid &operator=(const Rva0076F980Mid &other);
	AsciiString *erase(AsciiString *first, AsciiString *last);

	void clear(void)
	{
		erase(m_begin, m_end);
	}

private:
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

void *bfmeMakeBNG(void *one, void *two);

class LivingWorldRegion
{
public:
	void rva0061A860(
		const Rva0076F980Mid &names,
		unsigned int spawnNumber,
		unsigned int startNumber,
		unsigned int replaceDelay,
		unsigned char oneShot,
		unsigned char reclaimOrphans,
		unsigned char requireSpawner);
	void rva0061AB60(void);
	void rva0061B100(void);

private:
	unsigned char m_unmodelled00[0xA8];
	unsigned char m_active;					// +0xA8
	unsigned char m_unmodelledA9[0x0B];
	void *m_madeBNG;					// +0xB4
	unsigned char m_unmodelledB8[0x0C];
	unsigned int m_spawnNumber;				// +0xC4
	unsigned int m_startNumber;				// +0xC8
	unsigned int m_replaceDelay;				// +0xCC
	unsigned char m_oneShot;					// +0xD0
	unsigned char m_reclaimOrphans;				// +0xD1
	unsigned char m_alignment[2];
	Rva0076F980Mid m_names;					// +0xD4
	unsigned char m_unmodelledE0[8];
	unsigned char m_requireSpawner;				// +0xE8
};

void LivingWorldRegion::rva0061A860(
	const Rva0076F980Mid &names,
	unsigned int spawnNumber,
	unsigned int startNumber,
	unsigned int replaceDelay,
	unsigned char oneShot,
	unsigned char reclaimOrphans,
	unsigned char requireSpawner)
{
	m_names = names;
	m_spawnNumber = spawnNumber;
	m_startNumber = startNumber;
	m_replaceDelay = replaceDelay;
	m_oneShot = oneShot;
	m_reclaimOrphans = reclaimOrphans;
	m_requireSpawner = requireSpawner;
}

void LivingWorldRegion::rva0061AB60(void)
{
	m_names.clear();
	m_spawnNumber = 0;
	m_startNumber = 0;
	m_replaceDelay = 0;
	m_oneShot = 0;
	m_reclaimOrphans = 0;
	m_requireSpawner = 0;
}

// 0x0061AB60 plus the +0xA8 state reset and +0xB4 recreation.  Keeping one
// zero local reproduces retail's single xor and EBX reuse.
void LivingWorldRegion::rva0061B100(void)
{
	unsigned int z = 0;
	m_active = (unsigned char)z;
	m_madeBNG = bfmeMakeBNG((void *)z, (void *)z);
	m_names.clear();
	m_spawnNumber = z;
	m_startNumber = z;
	m_replaceDelay = z;
	m_oneShot = (unsigned char)z;
	m_reclaimOrphans = (unsigned char)z;
	m_requireSpawner = (unsigned char)z;
}
