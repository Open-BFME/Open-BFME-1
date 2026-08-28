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
class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString();

	void set(const char *text, int length);

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
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
