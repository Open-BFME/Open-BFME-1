// cl: /DNDEBUG /MD /EHsc
//
// Gen00606F70::~Gen00606F70 at retail 0x00606F70.
// The seven range-loop callers use this same 0x1F0-byte element layout. The
// destructor evidence fixes the 109 pointer slots at +0x28 and the
// RandomSoundSelectorMap member at +0x1DC.

class Gen00606F70Entry
{
public:
	virtual void release(bool now);
};

class RandomSoundSelectorMap
{
public:
	~RandomSoundSelectorMap();

private:
	void *m_node;
	unsigned int m_count;
	unsigned int m_reserved;
};

class Gen00606F70SoundNames
{
public:
	~Gen00606F70SoundNames()
	{
		for (int i = 0; i < 109; ++i)
		{
			Gen00606F70Entry *entry = m_entries[ i ];
			if (entry != 0)
			{
				entry->release( true );
				m_entries[ i ] = 0;
			}
		}
	}

private:
	Gen00606F70Entry *m_entries[ 109 ];
};

class Gen00606F70
{
public:
	~Gen00606F70();

private:
	unsigned char m_prefix[ 0x28 ];
	Gen00606F70SoundNames m_soundNames;
	RandomSoundSelectorMap m_soundMap;
	unsigned char m_tail[ 0x08 ];
};

// ??1Gen00606F70@@QAE@XZ
Gen00606F70::~Gen00606F70()
{
}
