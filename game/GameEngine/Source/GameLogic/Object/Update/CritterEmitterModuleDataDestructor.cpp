// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Only this destructor view suppresses the derived vtable store; the constructor must retain it.
// The registration proves the CritterEmitter role; the original derived class spelling remains unknown.
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

class __declspec(novtable) Rva0028BB10ModuleData : public ModuleData
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

Rva0028BB10ModuleData::~Rva0028BB10ModuleData()
{
}
