// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LevelGrantSpecialPowerModuleData scalar deleting destructor.
// The matched constructor at 0x0025FEF0 installs vtable 0x010B5CD8;
// slot zero reaches this wrapper through ILT 0x00048E14.

class Buffer
{
public:
	~Buffer();

private:
	unsigned char m_pad[ 4 ];
};

class LevelGrantSpecialPowerModuleDataBase
{
public:
	virtual ~LevelGrantSpecialPowerModuleDataBase();

private:
	unsigned char m_pad[ 0x25c ];
};

class LevelGrantSpecialPowerModuleData : public LevelGrantSpecialPowerModuleDataBase
{
public:
	__declspec(noinline) virtual ~LevelGrantSpecialPowerModuleData();

private:
	Buffer m_buffer;
};

LevelGrantSpecialPowerModuleData::~LevelGrantSpecialPowerModuleData()
{
}
