// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
	struct PrereqUnitRec
	{
	public:
		unsigned int m_data[3];
		~PrereqUnitRec();
	};

	class ScienceType
	{
	public:
		ScienceType() : m_value(0) {}
		ScienceType(const ScienceType &rhs) : m_value(rhs.m_value) {}
		ScienceType &operator=(const ScienceType &rhs)
		{
			m_value = rhs.m_value;
			return *this;
		}

	private:
		int m_value;
	};

	ProductionPrerequisite();

private:
	std::vector<PrereqUnitRec> m_prereqUnits;
	std::vector<ScienceType> m_prereqSciences;
	std::vector<ScienceType> m_unused;
};

// ??0ProductionPrerequisite@@QAE@XZ
ProductionPrerequisite::ProductionPrerequisite()
{
	m_prereqUnits.clear();
	m_prereqSciences.clear();
}
