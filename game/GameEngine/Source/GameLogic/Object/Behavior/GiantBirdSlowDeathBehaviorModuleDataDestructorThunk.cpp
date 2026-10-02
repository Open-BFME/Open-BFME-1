// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GiantBirdSlowDeathBehaviorModuleData dtor. SEH GiantBirdSlowDeathBehaviorModuleDataMember @+0x1b4 then base.

// The member is released through the ILT at 0x00026F35, which jumps to the
// AudioEventRTS destructor at 0x000B31F0, so it carries that class's name.
// The destructor is declared non-virtual because that call site is the SCALAR
// AudioEventRTS destructor the ledger names at 0x000B31F0; the 77-byte virtual
// body is a different address.  m_pad stays 4 bytes to hold the offset.
class AudioEventRTS
{
public:
	~AudioEventRTS();
private:
	unsigned char m_pad[4];
};

class GiantBirdSlowDeathBehaviorModuleDataBase
{
public:
	virtual ~GiantBirdSlowDeathBehaviorModuleDataBase();
private:
	unsigned char m_pad[0x1b0];
};

class __declspec(novtable) GiantBirdSlowDeathBehaviorModuleData : public GiantBirdSlowDeathBehaviorModuleDataBase
{
public:
	virtual ~GiantBirdSlowDeathBehaviorModuleData();
private:
	AudioEventRTS m_member;
};

// ??1GiantBirdSlowDeathBehaviorModuleData@@UAE@XZ
GiantBirdSlowDeathBehaviorModuleData::~GiantBirdSlowDeathBehaviorModuleData()
{
}
