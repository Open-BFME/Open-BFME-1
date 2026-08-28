// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RandomSoundSelectorClientBehavior::friend_newModuleData factory, retail 0x0012BE60,
// converted out of a machine byte dump.
//
// Every module's data factory is this same body -- allocate the module data,
// hand it and the class's field-parse table to INI::initFromINI when there is
// an INI to parse from, return it -- so only the registration block names it,
// by pushing this address beside the AsciiString "RandomSoundSelectorClientBehavior".
//
// Retail allocates 0x1D4 bytes, which is sizeof(RandomSoundSelectorClientBehaviorModuleData) with its
// vptr, and calls the constructor through 0x0001F528.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ModuleData
{
public:
	virtual ~ModuleData();

private:
	unsigned int m_baseField;
};

class RandomSoundSelectorSoundNames
{
public:
	RandomSoundSelectorSoundNames()
	{
		for (int i = 0; i < 109; ++i)
			m_values[i] = 0;
	}
	~RandomSoundSelectorSoundNames();

private:
	unsigned int m_values[109];
};

class RandomSoundSelectorMap
{
	struct Node
	{
		unsigned char m_flag;
		unsigned char m_pad[3];
		unsigned int m_value;
		Node *m_next;
		Node *m_previous;
		unsigned char m_payload[0x74];
	};

public:
	RandomSoundSelectorMap()
	{
		m_node = 0;
		m_node = (Node *)operator new(sizeof(Node));
		m_count = 0;
		m_node->m_flag = 0;
		m_node->m_value = 0;
		m_node->m_next = m_node;
		m_node->m_previous = m_node;
	}
	~RandomSoundSelectorMap();

private:
	Node *m_node;
	unsigned int m_count;
	unsigned int m_reserved;
};

class RandomSoundSelectorClientBehaviorModuleData : public ModuleData
{
public:
	RandomSoundSelectorClientBehaviorModuleData();
	virtual ~RandomSoundSelectorClientBehaviorModuleData();

private:
	RandomSoundSelectorSoundNames m_soundNames;
	RandomSoundSelectorMap m_soundMap;
	float m_defaultVolume;
	unsigned int m_selectionIndex;
	bool m_shuffle;
	bool m_enabled;
	unsigned char m_pad[2];
};

// ??0RandomSoundSelectorClientBehaviorModuleData@@QAE@XZ
RandomSoundSelectorClientBehaviorModuleData::RandomSoundSelectorClientBehaviorModuleData()
	: m_defaultVolume(0.5f),
	  m_selectionIndex(0),
	  m_shuffle(false),
	  m_enabled(true)
{
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RandomSoundSelectorClientBehaviorFieldParse;

class RandomSoundSelectorClientBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RandomSoundSelectorClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RandomSoundSelectorClientBehavior::friend_newModuleData(INI *ini)
{
	RandomSoundSelectorClientBehaviorModuleData *data = new RandomSoundSelectorClientBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &RandomSoundSelectorClientBehaviorFieldParse);
	return (ModuleData *)data;
}
