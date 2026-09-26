// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Keeping the constructor out of this TU preserves retail cleanup if construction throws.
// The registration proves the CritterEmitter role; the derived class and factory spellings remain unknown.
#include <vector>

class INI;
class MultiIniFieldParse;
class FXList;
class ObjectCreationList;

class Snapshot
{
public:
	virtual ~Snapshot() {}
};

class ModuleData : public Snapshot
{
private:
	unsigned int m_moduleTag;
};

class Rva0028BB10ModuleData : public ModuleData
{
public:
	Rva0028BB10ModuleData();
	virtual ~Rva0028BB10ModuleData();
	static ModuleData *create(INI *ini);
	static void buildFieldParse(MultiIniFieldParse &parse);
private:
	std::vector<const FXList *> m_fx;
	std::vector<const ObjectCreationList *> m_spawnObjects;
	unsigned int m_field20;
};

class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

ModuleData *Rva0028BB10ModuleData::create(INI *ini)
{
	Rva0028BB10ModuleData *data = new Rva0028BB10ModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &Rva0028BB10ModuleData::buildFieldParse);
	return data;
}
