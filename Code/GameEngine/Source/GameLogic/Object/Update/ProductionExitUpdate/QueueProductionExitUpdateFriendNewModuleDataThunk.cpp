// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: QueueProductionExitUpdate::friend_newModuleData
// Inline ModuleData ctor so the TU only exports the factory symbol.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/QueueProductionExitUpdate.h
class QueueProductionExitUpdateModuleData
{
public:
	QueueProductionExitUpdateModuleData()
	{
		m_a = 0;
		m_b = 0;
		m_c = 0;
		m_d = 0;
		m_e = 0;
		m_f = 0;
		m_g = 0;
		m_h = 0;
		m_i = 0;
		m_j = 0;
		m_k = 0;
		m_l = 0;
	}
	virtual ~QueueProductionExitUpdateModuleData();
private:
	unsigned int m_pad;
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
	unsigned int m_d;
	unsigned int m_e;
	unsigned int m_f;
	unsigned int m_g;
	unsigned char m_h;
	unsigned char m_pad1;
	unsigned char m_pad2;
	unsigned char m_pad3;
	unsigned int m_i;
	unsigned int m_j;
	unsigned char m_k;
	unsigned char m_l;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char QueueProductionExitUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/QueueProductionExitUpdate.h
class QueueProductionExitUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@QueueProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *QueueProductionExitUpdate::friend_newModuleData(INI *ini)
{
	QueueProductionExitUpdateModuleData *data = new QueueProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &QueueProductionExitUpdateFieldParse);
	return (ModuleData *)data;
}
