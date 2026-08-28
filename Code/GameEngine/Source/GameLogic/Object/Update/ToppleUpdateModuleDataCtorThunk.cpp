// cl: /DNDEBUG /MD /EHsc

// Base, a string, four floats and a run of flags.
//
// Names come from retail's INI field table joined to upstream's parse table on
// the key; retail gives every offset, upstream only the word, and the offsets
// here were derived from the declaration sequence rather than the old m_NN
// names. The three Percent keys are the three floats and the five toppling
// flags are the five bytes at +0x24..+0x28, which is what pins the run.
//
// +0x010 previously read m_toppleFX. Retail's table puts StumpName there and
// ToppleFX at +0x008, upstream declares m_stumpName in that position, and the
// type here was already a string -- so the slot was right and only the name was
// wrong. ToppleFX and BounceFX are the two pointer-width slots ahead of it that
// had no name at all. +0x020 has no key in the table and keeps its offset name.
//
// The string at +0x10 is constructed inline -- one zeroed word through the lea
// that stays live -- and then cleared, which is the call to the private
// releaseBuffer. Clearing a string that was just zeroed looks redundant and is
// not optional: it is the only call in the function.
//
// Two unwind states counting up, base then string, so the string is the one
// destructible member.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString()
	{
		m_data = 0;
	}

	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void clear(void)
	{
		releaseBuffer();
	}

private:
	void releaseBuffer(void);

	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual ~ModuleData();

	unsigned int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ToppleUpdate.h
class ToppleUpdateModuleData : public ModuleData
{
public:
	ToppleUpdateModuleData();

private:
	int m_toppleFX;
	int m_bounceFX;
	BFMERetailAsciiString m_stumpName;
	float m_initialVelocityPercent;
	float m_initialAccelPercent;
	float m_bounceVelocityPercent;
	float m_20;
	bool m_killWhenToppled;
	bool m_killWhenStartToppled;
	bool m_killStumpWhenToppled;
	bool m_toppleLeftOrRightOnly;
	bool m_reorientToppledRubble;
};

// ??0ToppleUpdateModuleData@@QAE@XZ
ToppleUpdateModuleData::ToppleUpdateModuleData()
{
	m_toppleFX = 0;
	m_bounceFX = 0;
	m_stumpName.clear();
	m_initialVelocityPercent = 0.2f;
	m_bounceVelocityPercent = 0.2f;
	m_killWhenStartToppled = false;
	m_killStumpWhenToppled = false;
	m_toppleLeftOrRightOnly = false;
	m_reorientToppledRubble = false;
	m_killWhenToppled = true;
	m_initialAccelPercent = 0.01f;
	m_20 = 0.5f;
}
