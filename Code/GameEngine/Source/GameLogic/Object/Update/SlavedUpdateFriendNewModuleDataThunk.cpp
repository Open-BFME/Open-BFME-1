// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: SlavedUpdate::friend_newModuleData

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h
class SlavedUpdateModuleData
{
public:
	SlavedUpdateModuleData()
	{
		// Store order mirrors retail factory body.
		m_48 = 0;
		m_4c = 0;
		m_08 = 0;
		m_0c = 0;
		m_10 = 0;
		m_14 = 0;
		m_18 = 0;
		m_1c = 0;
		m_20 = 0;
		m_30 = 0;
		m_34 = 0;
		m_28 = 0;
		m_2c = 0;
		m_40 = 0;
		m_44 = 0;
		m_38 = 0;
		m_3c = 0;
		m_50 = 0;
	}
	virtual ~SlavedUpdateModuleData();
private:
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3c;
	unsigned int m_40;
	unsigned int m_44;
	unsigned int m_48;
	unsigned int m_4c;
	unsigned char m_50;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SlavedUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h
class SlavedUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SlavedUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlavedUpdate::friend_newModuleData(INI *ini)
{
	SlavedUpdateModuleData *data = new SlavedUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &SlavedUpdateFieldParse);
	return (ModuleData *)data;
}
