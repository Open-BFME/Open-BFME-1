// cl: /DNDEBUG /MD /EHsc
// BFME W3DModelDrawModuleData constructor at retail 0x002136E0.
// The 0x64-byte ModuleData base and the derived field offsets are established
// by the constructor stores and the adjacent matched destructor at 0x00213750.

class W3DModelDrawModuleDataBase
{
public:
	W3DModelDrawModuleDataBase();
	virtual ~W3DModelDrawModuleDataBase();

private:
	unsigned char m_pad[0x60];
};

class W3DModelDrawModuleData : public W3DModelDrawModuleDataBase
{
public:
	W3DModelDrawModuleData();
	virtual ~W3DModelDrawModuleData();

private:
	unsigned int m_64;
	unsigned int m_68;
	unsigned char m_6c;
	unsigned char m_pad6d[3];
	unsigned int m_70;
	unsigned int m_74;
	unsigned int m_78;
	unsigned int m_7c;
};

W3DModelDrawModuleData::W3DModelDrawModuleData()
{
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_7c = 0;
	m_74 = 0;
	m_78 = 0;
	m_70 = 0xffffffff;
}
