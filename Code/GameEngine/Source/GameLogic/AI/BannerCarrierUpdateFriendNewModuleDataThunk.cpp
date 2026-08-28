// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BannerCarrierUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BannerCarrierUpdateModuleData
{
public:
	BannerCarrierUpdateModuleData();
	virtual ~BannerCarrierUpdateModuleData();

private:
	unsigned char m_pad[0x3c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char BannerCarrierUpdateFieldParse;

class BannerCarrierUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BannerCarrierUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BannerCarrierUpdate::friend_newModuleData(INI *ini)
{
	BannerCarrierUpdateModuleData *data = new BannerCarrierUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &BannerCarrierUpdateFieldParse);
	return (ModuleData *)data;
}
