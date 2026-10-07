// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GloriousChargeUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class MultiIniFieldParse;

class GloriousChargeUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &p);	// 0x0025E7F0 via ILT 0x00018D5E
	GloriousChargeUpdateModuleData();
	virtual ~GloriousChargeUpdateModuleData();

private:
	unsigned char m_pad[0x25c];
};

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
		ini->initFromINIMultiProc(data, &GloriousChargeUpdateModuleData::buildFieldParse);
	return (ModuleData *)data;
}
