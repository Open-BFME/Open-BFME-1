// ?append@Rva0019BE80TeamRec@@QAEHPBVDict@@@Z
// Retail 0x0019BA40, 331 bytes. Address-derived owner retains the banked
// names; its three-pointer vector and two shorts occupy receiver +0x0C..0x1B.
// Native Dict declarations reproduce the already-matched callee contracts.
// The catch handler begins at the next retail address, 0x0019BB8B; MSVC emits
// its 21-byte handler immediately after this function's claimed extent.
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy- /Ob1 /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/Dict.h"
#include <vector>

struct Gen_t_0019a890_p16cd
{
	short next;
	short previous;
	short reserved;
	short free;
	int generation;
	Dict dict;

	Gen_t_0019a890_p16cd()
		: next(0), previous(0), reserved(0), free(0), generation(0), dict()
	{
	}

	__forceinline Gen_t_0019a890_p16cd(const Gen_t_0019a890_p16cd &other)
		: next(other.next), previous(other.previous), reserved(other.reserved),
		  free(other.free), generation(other.generation), dict(other.dict)
	{
	}
};

class Rva0019BE80TeamRec
{
public:
	int append(const Dict *dict);

private:
	char m_prefix[0xc];
	_STL::vector<Gen_t_0019a890_p16cd,
		_STL::allocator<Gen_t_0019a890_p16cd> > m_teams;
	short m_numActive;
	short m_freeHead;

	public:
	void updateTeam(int index);
};

int Rva0019BE80TeamRec::append(const Dict *dict)
{
	if (m_freeHead == 0)
	{
		int index = (int)m_teams.size();
		{
			Gen_t_0019a890_p16cd team;
			m_teams.push_back(team);
		}
		m_freeHead = (short)index;
	}

	int index = m_freeHead;
	Gen_t_0019a890_p16cd *team = m_teams.begin() + index;
	team->dict.clear();
	if (dict)
		team->dict = *dict;
	try
	{
		updateTeam(index);
	}
	catch (...)
	{
		team->dict.clear();
		throw;
	}
	m_freeHead = team->next;
	m_teams[m_teams[0].previous].next = (short)index;
	team->previous = m_teams[0].previous;
	team->next = 0;
	m_teams[0].previous = (short)index;
	++m_numActive;
	return index;
}
