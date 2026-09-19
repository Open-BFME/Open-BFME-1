// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeContain module-data destructor in C++.

void __cdecl freeHordeContainOwnedBuffer(void *memory, unsigned int element_size);

class HordeContainMember70
{
public:
	~HordeContainMember70();
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
	HordeContainMember70 m_member34;
	HordeContainMember70 m_membera4;
	HordeContainMember4A m_member114;
	HordeContainMember4A m_member118;
	HordeContainOwnedBuffer m_member11c;
	HordeContainMember38 m_member120;
	HordeContainMember14 m_member158;
};

HordeContainModuleData::~HordeContainModuleData()
{
}
