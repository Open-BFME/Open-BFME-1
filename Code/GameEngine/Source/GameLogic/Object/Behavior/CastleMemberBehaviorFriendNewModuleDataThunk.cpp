// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CastleMemberBehavior::friend_newModuleData factory.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CastleMemberBehaviorModuleData
{
public:
	CastleMemberBehaviorModuleData();
	virtual ~CastleMemberBehaviorModuleData();

private:
	unsigned char m_pad[0x26];
};

class MultiIniFieldParse;
class Gen00850920;

void Rva0036CDB0(Gen00850920 *table);

class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

class CastleMemberBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CastleMemberBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CastleMemberBehavior::friend_newModuleData(INI *ini)
{
	CastleMemberBehaviorModuleData *data = new CastleMemberBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			(void (__cdecl *)(MultiIniFieldParse &))&Rva0036CDB0);
	return (ModuleData *)data;
}
