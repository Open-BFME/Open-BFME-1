// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: ContestableContainModuleData ctor
// Base call, zeros at +0x17c/+0x180, then vtbl, then more field zeros.

class ContestableContainModuleDataBase
{
public:
	ContestableContainModuleDataBase();
	virtual void contestableContainModuleDataBaseAnchor();

private:
	unsigned char m_pad[0x178];
};

extern "C" char ContestableContainModuleData_vtbl;

class __declspec(novtable) ContestableContainModuleData
	: public ContestableContainModuleDataBase
{
public:
	ContestableContainModuleData();

private:
	unsigned int m_17c;
	unsigned int m_180;
	unsigned int m_184;
	unsigned int m_188;
	unsigned int m_18c;
	unsigned int m_190;
	unsigned int m_194;
	unsigned int m_198;
	unsigned int m_19c;
	unsigned int m_1a0;
	unsigned int m_1a4;
};

// ??0ContestableContainModuleData@@QAE@XZ
ContestableContainModuleData::ContestableContainModuleData()
{
	*reinterpret_cast<unsigned int volatile *>(&m_17c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_180) = 0;
	*reinterpret_cast<char *volatile *>(this) =
		&ContestableContainModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_184) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_188) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_18c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_19c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_1a0) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_1a4) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_190) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_194) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_198) = 0;
}
