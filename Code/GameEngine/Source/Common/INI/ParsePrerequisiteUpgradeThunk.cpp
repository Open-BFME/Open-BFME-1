// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

class INI
{
public:
	const char *getNextToken(int);
};

class UpgradeTemplate;
class Rva00144100Item;

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		unsigned int m_data[3];
		~PrereqUnitRec();
	};

	ProductionPrerequisite();
	~ProductionPrerequisite();

	void addUpgradePrereq(const UpgradeTemplate *upgrade)
	{
		m_prereqUpgrades.push_back(
			reinterpret_cast<Rva00144100Item *>(
				const_cast<UpgradeTemplate *>(upgrade)));
	}

private:
	_STL::vector<PrereqUnitRec> m_prereqUnits;
	_STL::vector<int> m_prereqSciences;
	_STL::vector<Rva00144100Item *> m_prereqUpgrades;
};

const UpgradeTemplate *bfmeFindUpgradeByName(const char *name);

// ?parsePrerequisiteUpgrade@@YAXPAVINI@@PAX1PBX@Z
void __cdecl parsePrerequisiteUpgrade(INI *ini, void *instance, void *,
	const void *)
{
	_STL::vector<ProductionPrerequisite> *prerequisites =
		static_cast<_STL::vector<ProductionPrerequisite> *>(instance);

	ProductionPrerequisite prerequisite;
	prerequisite.addUpgradePrereq(
		bfmeFindUpgradeByName(ini->getNextToken(0)));
	prerequisites->push_back(prerequisite);
}
