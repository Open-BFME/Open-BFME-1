// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RubbleRiseUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RubbleRiseUpdateModuleData
{
public:
	RubbleRiseUpdateModuleData();
	virtual ~RubbleRiseUpdateModuleData();

private:
	unsigned char m_pad[0xd0];
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

// Retail stores VA 0x004333D9: the matched ILT thunk ?j_000333d9@@YAXXZ.
void j_000333d9();

class RubbleRiseUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RubbleRiseUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RubbleRiseUpdate::friend_newModuleData(INI *ini)
{
	RubbleRiseUpdateModuleData *data = new RubbleRiseUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))&j_000333d9);
	return (ModuleData *)data;
}
