// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift PassiveAreaEffectBehaviorModuleData dtor MASM to clean C++.
// Retail destroys the Buffer member at this+0x20 and the 12-byte member at
// this+0x14 under one SEH frame, then runs the inlined base dtor.

class PassiveAreaEffectBehaviorModuleDataMember
{
public:
	~PassiveAreaEffectBehaviorModuleDataMember();

private:
	unsigned char m_data[0xc];
};

class Buffer
{
public:
	~Buffer();
};

class PassiveAreaEffectBehaviorModuleDataBase
{
public:
	virtual ~PassiveAreaEffectBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x10];
};

class __declspec(novtable) PassiveAreaEffectBehaviorModuleData
	: public PassiveAreaEffectBehaviorModuleDataBase
{
public:
	virtual ~PassiveAreaEffectBehaviorModuleData();

private:
	PassiveAreaEffectBehaviorModuleDataMember m_member;
	Buffer m_buffer;
};

// ??1PassiveAreaEffectBehaviorModuleData@@UAE@XZ
PassiveAreaEffectBehaviorModuleData::~PassiveAreaEffectBehaviorModuleData()
{
}
