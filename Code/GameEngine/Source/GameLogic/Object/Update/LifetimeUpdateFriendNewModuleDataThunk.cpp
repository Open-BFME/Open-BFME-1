// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LifetimeUpdate::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LifetimeUpdate.h
class LifetimeUpdateModuleData {
public:
	LifetimeUpdateModuleData();
	virtual ~LifetimeUpdateModuleData();
private:
	unsigned char m_pad[0x14];
};
class INI { public: void initFromINI(void *what, const void *parseTable); };
extern "C" char LifetimeUpdateFieldParse;
class LifetimeUpdate { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *LifetimeUpdate::friend_newModuleData(INI *ini) {
	LifetimeUpdateModuleData *data = new LifetimeUpdateModuleData;
	if (ini) ini->initFromINI(data, &LifetimeUpdateFieldParse);
	return (ModuleData *)data;
}
