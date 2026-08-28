// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1SpecialPowerStore@@: Code/GameEngine/Source/Common/RTS/SpecialPower.cpp

// Delete every element, clear the vector, zero one field, then let the member
// and the base tear themselves down.
//
// size() is recomputed on each iteration rather than hoisted, which is what
// `i < v.size()` compiles to, and the comparisons are jb and jbe -- unsigned, so
// the index is unsigned too. A signed loop counter would give jl.
//
// The clear() is the degenerate erase(begin(), end()): the compare of finish
// against itself and the branch that can never be taken are what is left of the
// range copy once both ends are the same pointer.
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate
{
public:
	virtual ~SpecialPowerTemplate();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerStore : public SubsystemInterface
{
public:
	virtual ~SpecialPowerStore();

private:
	std::vector<SpecialPowerTemplate *> m_templates;
	int m_14;
};

// ??1SpecialPowerStore@@UAE@XZ
SpecialPowerStore::~SpecialPowerStore()
{
	for (unsigned int i = 0; i < m_templates.size(); i++) {
		delete m_templates[i];
	}

	m_templates.clear();
	m_14 = 0;
}
