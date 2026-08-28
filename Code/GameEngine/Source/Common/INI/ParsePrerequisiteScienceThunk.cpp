// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(int);
	static ScienceType scanScience(const char *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
	struct PrereqUnitRec
	{
		unsigned int m_data[3];
		~PrereqUnitRec();
	};

	ProductionPrerequisite();
	~ProductionPrerequisite();

	void addSciencePrereq(ScienceType science)
	{
		m_prereqSciences.push_back(science);
	}

private:
	_STL::vector<PrereqUnitRec> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<ScienceType> m_unused;
};

// ?parsePrerequisiteScience@@YAXPAVINI@@PAX1PBX@Z
void __cdecl parsePrerequisiteScience(INI *ini, void *instance, void *,
	const void *)
{
	_STL::vector<ProductionPrerequisite> *prerequisites =
		static_cast<_STL::vector<ProductionPrerequisite> *>(instance);

	ProductionPrerequisite prerequisite;
	prerequisite.addSciencePrereq(INI::scanScience(ini->getNextToken(0)));
	prerequisites->push_back(prerequisite);
}
