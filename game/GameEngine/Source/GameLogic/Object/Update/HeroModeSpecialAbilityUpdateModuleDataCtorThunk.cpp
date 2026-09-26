// cl: /DNDEBUG /MD /EHsc

// A base constructed out of line, this class's vptr, then a layout string set
// from an empty literal, then two fields.
//
// ecx is loaded with the member's address before the vptr store and reused for
// both its own zeroing and the set call that follows -- the thiscall argument
// set up early rather than a separate cursor. The length pushed is zero, which
// is the literal's own length.
//
// Two unwind states count the two destructible things standing when the call
// that can throw is made: the base and the member.
// The owner destructor passes the same +0x254 word directly to releaseBuffer;
// both retail string aliases resolve through that one witnessed body.
class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString() { releaseBuffer(); }

	void set(const char *text, int length);

private:
	void releaseBuffer();
	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();

	virtual ~SpecialAbilityUpdateModuleData();

private:
	unsigned char m_head[0x250];
};

class HeroModeSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	HeroModeSpecialAbilityUpdateModuleData();
	virtual ~HeroModeSpecialAbilityUpdateModuleData();

private:
	RetailLayoutString m_layout;
	int m_258;
	bool m_25c;
};

// ??0HeroModeSpecialAbilityUpdateModuleData@@QAE@XZ
HeroModeSpecialAbilityUpdateModuleData::HeroModeSpecialAbilityUpdateModuleData()
{
	m_layout.set("", 0);
	m_258 = 0;
	m_25c = false;
}

// Retail begins teardown with the member at +0x254, not a derived-vtable store.
class __declspec(novtable) HeroModeSpecialAbilityUpdateModuleData;

// ??1HeroModeSpecialAbilityUpdateModuleData@@UAE@XZ
HeroModeSpecialAbilityUpdateModuleData::~HeroModeSpecialAbilityUpdateModuleData()
{
}
