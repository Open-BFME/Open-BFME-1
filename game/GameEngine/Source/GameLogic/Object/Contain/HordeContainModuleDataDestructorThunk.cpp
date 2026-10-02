// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeContain module-data destructor in C++.

void __cdecl freeHordeContainOwnedBuffer(void *memory, unsigned int element_size);

// Both 0x70-byte members are released through the ILT at 0x00026F35, which
// jumps to the AudioEventRTS destructor at 0x000B31F0, so both carry that
// class's name and its BFME 0x70-byte footprint.  The destructor is declared
// non-virtual because that call site is the SCALAR AudioEventRTS destructor
// (the ledger's name for 0x000B31F0); the 77-byte virtual body is elsewhere.
class AudioEventRTS
{
public:
	~AudioEventRTS();
private:
	unsigned char m_storage[0x70];
};

class HordeContainMember4A
{
public:
	~HordeContainMember4A();
private:
	unsigned int m_value;
};

class HordeContainOwnedBuffer
{
public:
	~HordeContainOwnedBuffer()
	{
		cleanup();
		if (m_memory)
			freeHordeContainOwnedBuffer(m_memory, 0x24);
	}

private:
	void cleanup();
	void *m_memory;
};

class HordeContainMember38
{
public:
	~HordeContainMember38();
private:
	unsigned char m_storage[0x38];
};

class HordeContainMember14
{
public:
	~HordeContainMember14();
private:
	unsigned char m_storage[0x14];
};

class HordeContainModuleDataBase
{
public:
	virtual ~HordeContainModuleDataBase() {}
private:
	unsigned char m_prefix[0x30];
};

class __declspec(novtable) HordeContainModuleData : public HordeContainModuleDataBase
{
public:
	virtual ~HordeContainModuleData();
private:
	AudioEventRTS m_member34;
	AudioEventRTS m_membera4;
	HordeContainMember4A m_member114;
	HordeContainMember4A m_member118;
	HordeContainOwnedBuffer m_member11c;
	HordeContainMember38 m_member120;
	HordeContainMember14 m_member158;
};

HordeContainModuleData::~HordeContainModuleData()
{
}
