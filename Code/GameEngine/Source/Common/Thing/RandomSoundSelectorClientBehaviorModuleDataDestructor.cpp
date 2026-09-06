// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: RandomSoundSelectorClientBehaviorModuleData::~RandomSoundSelectorClientBehaviorModuleData,
// retail 0x0012BDD0, 107 bytes.
//
// Members destruct in reverse declared order: m_soundMap first (an out-of-line
// call to retail 0x00035B34, already pinned as thunks_025.cpp), then the
// 109-slot m_soundNames array inline (`if (slot) { slot->release(true);
// slot = 0; }` per element -- BfmeBaseVUQ destructor family shape: a small
// polymorphic pointer whose vtable slot 0 is called with argument true before
// the trivial ModuleData/BfmeBaseVUQ base restores the shared folded vtable
// at 0x01073744).
//
// See RandomSoundSelectorClientBehaviorFriendNewModuleDataThunk.cpp (the
// landed neighbour that names this class and its constructor) for the sibling
// factory function; that file's RandomSoundSelectorSoundNames/-Map are
// address-placeholders too, redeclared here with the layout this destructor's
// bytes actually prove.

// Non-virtual base whose destructor manually stamps the shared folded
// vtable-shaped constant 0x01073744 -- same technique as
// Rva000A1B30VectorHolderDestructor.cpp's Rva000A1B30Base. No entry-time
// store happens for this family member (retail has none), only this single
// tail store, so this is modelled without real C++ polymorphism.
extern int bfmeVtable0012BDD0[];

class ModuleDataBase0012BDD0
{
public:
	~ModuleDataBase0012BDD0() { m_table = bfmeVtable0012BDD0; }
	void *m_table;
	unsigned int m_baseField;
};

class RandomSoundSelectorSoundNamesEntry
{
public:
	virtual void release(bool now) = 0;                        ///< vtable +0x00
};

class RandomSoundSelectorSoundNames
{
public:
	~RandomSoundSelectorSoundNames()
	{
		for (int i = 0; i < 109; ++i)
		{
			RandomSoundSelectorSoundNamesEntry *entry = m_values[i];
			if (entry != 0)
			{
				entry->release(true);
				m_values[i] = 0;
			}
		}
	}

private:
	RandomSoundSelectorSoundNamesEntry *m_values[109];
};

class RandomSoundSelectorMap
{
public:
	~RandomSoundSelectorMap();                                 ///< out-of-line, pinned to retail 0x00035B34

private:
	void *m_node;
	unsigned int m_count;
	unsigned int m_reserved;
};

class RandomSoundSelectorClientBehaviorModuleData : public ModuleDataBase0012BDD0
{
public:
	~RandomSoundSelectorClientBehaviorModuleData();

private:
	RandomSoundSelectorSoundNames m_soundNames;
	RandomSoundSelectorMap m_soundMap;
	float m_defaultVolume;
	unsigned int m_selectionIndex;
	bool m_shuffle;
	bool m_enabled;
	unsigned char m_pad[2];
};

// @??1RandomSoundSelectorClientBehaviorModuleData@@UAE@XZ 0x0012BDD0
RandomSoundSelectorClientBehaviorModuleData::~RandomSoundSelectorClientBehaviorModuleData()
{
}
