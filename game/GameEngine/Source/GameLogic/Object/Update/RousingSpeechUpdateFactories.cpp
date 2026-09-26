// cl: /DNDEBUG /MD /EHsc
// RousingSpeechUpdate factories: 0x284-byte data and 0xfc-byte instance.
// Retail EH metadata links 0x0011C640 to 0x00BFFDC0 and 0x0011C6C0
// to 0x00BFFDE0; both cleanup handlers release the failed allocation.

class INI;
class Thing;
class Module;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RousingSpeechUpdateModuleData
{
public:
	RousingSpeechUpdateModuleData();
	virtual ~RousingSpeechUpdateModuleData();

private:
	unsigned char m_pad[0x280];
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

extern "C" void __cdecl RousingSpeechUpdateFieldParse(MultiIniFieldParse &parse);

class RousingSpeechUpdate
{
public:
	RousingSpeechUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xfc];
};

// ?friend_newModuleData@RousingSpeechUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RousingSpeechUpdate::friend_newModuleData(INI *ini)
{
	RousingSpeechUpdateModuleData *data = new RousingSpeechUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &RousingSpeechUpdateFieldParse);
	return (ModuleData *)data;
}

// ?friend_newModuleInstance@RousingSpeechUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RousingSpeechUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new RousingSpeechUpdate(thing, data);
}
