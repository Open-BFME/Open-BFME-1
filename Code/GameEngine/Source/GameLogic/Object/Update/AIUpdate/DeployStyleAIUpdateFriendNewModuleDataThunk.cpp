// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DeployStyleAIUpdate::friend_newModuleData factory.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DeployStyleAIUpdateModuleDataBaseShim
{
public:
	void construct();
};

class DeployStyleAIUpdateModuleDataVtbl
{
public:
	DeployStyleAIUpdateModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x6c];
};

class __declspec(novtable) DeployStyleAIUpdateModuleData
{
public:
	DeployStyleAIUpdateModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x6c];
};

DeployStyleAIUpdateModuleData::DeployStyleAIUpdateModuleData()
{
	((DeployStyleAIUpdateModuleDataBaseShim *)this)->construct();
	((DeployStyleAIUpdateModuleDataVtbl *)this)->DeployStyleAIUpdateModuleDataVtbl::DeployStyleAIUpdateModuleDataVtbl();
	*(unsigned int *)((char *)this + 0x64) = 0x0;
	*(unsigned int *)((char *)this + 0x68) = 0x0;
	*((unsigned char *)this + 0x6c) = 0x0;
	*((unsigned char *)this + 0x6d) = 0x0;
	*((unsigned char *)this + 0x6e) = 0x0;
}

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl DeployStyleAIUpdateFieldParse(MultiIniFieldParse &parse);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeployStyleAIUpdate.h
class DeployStyleAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DeployStyleAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DeployStyleAIUpdate::friend_newModuleData(INI *ini)
{
	DeployStyleAIUpdateModuleData *data = new DeployStyleAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &DeployStyleAIUpdateFieldParse);
	return (ModuleData *)data;
}
