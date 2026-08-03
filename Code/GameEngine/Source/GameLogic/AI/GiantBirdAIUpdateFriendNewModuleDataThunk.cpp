// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GiantBirdAIUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FirestormDynamicGeometryInfoUpdateModuleData
{
public:
	FirestormDynamicGeometryInfoUpdateModuleData();
	virtual ~FirestormDynamicGeometryInfoUpdateModuleData();

private:
	unsigned char m_pad[0x80];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GiantBirdAIUpdateFieldParse;

class GiantBirdAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GiantBirdAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GiantBirdAIUpdate::friend_newModuleData(INI *ini)
{
	FirestormDynamicGeometryInfoUpdateModuleData *data = new FirestormDynamicGeometryInfoUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &GiantBirdAIUpdateFieldParse);
	return (ModuleData *)data;
}
