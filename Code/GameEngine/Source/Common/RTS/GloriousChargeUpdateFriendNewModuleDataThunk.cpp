// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GloriousChargeUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GloriousChargeUpdateModuleData
{
public:
	GloriousChargeUpdateModuleData();
	virtual ~GloriousChargeUpdateModuleData();

private:
	unsigned char m_pad[0x25c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GloriousChargeUpdateFieldParse;

class GloriousChargeUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GloriousChargeUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GloriousChargeUpdate::friend_newModuleData(INI *ini)
{
	GloriousChargeUpdateModuleData *data = new GloriousChargeUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &GloriousChargeUpdateFieldParse);
	return (ModuleData *)data;
}
