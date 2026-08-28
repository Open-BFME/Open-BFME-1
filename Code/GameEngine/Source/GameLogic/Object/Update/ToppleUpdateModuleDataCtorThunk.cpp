// cl: /DNDEBUG /MD /EHsc

// Base, a string, four floats and a run of flags.
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
	int m_08;
	int m_0c;
	BFMERetailAsciiString m_toppleFX;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
	bool m_24;
	bool m_25;
	bool m_26;
	bool m_27;
	bool m_28;
};

// ??0ToppleUpdateModuleData@@QAE@XZ
ToppleUpdateModuleData::ToppleUpdateModuleData()
{
	m_08 = 0;
	m_0c = 0;
	m_toppleFX.clear();
	m_14 = 0.2f;
	m_1c = 0.2f;
	m_25 = false;
	m_26 = false;
	m_27 = false;
	m_28 = false;
	m_24 = true;
	m_18 = 0.01f;
	m_20 = 0.5f;
}
