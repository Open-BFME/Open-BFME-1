// cl: /DNDEBUG /MD /GX- /O2 /Ob2

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *object, const FieldParse *fields);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	ModuleData() {}
	virtual ~ModuleData();

private:
	int m_moduleTagNameKey;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DRopeDraw.h
class W3DRopeDraw
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *W3DRopeDraw::friend_newModuleData(INI *ini)
{
	ModuleData *data = ::new ModuleData;
	if (ini)
		ini->initFromINI(data, 0);
	return data;
}
