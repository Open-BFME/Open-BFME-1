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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

// Retail stores VA 0x004411C8: the matched ILT thunk ?j_000411c8@@YAXXZ.
void j_000411c8();

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
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))&j_000411c8);
	return (ModuleData *)data;
}
