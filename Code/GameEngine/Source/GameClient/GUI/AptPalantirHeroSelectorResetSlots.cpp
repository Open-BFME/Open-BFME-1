// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include <algorithm>
#include <list>

struct Rva0058D930ListEntry
{
	unsigned char bytes[ 12 ];
};

// The 24-byte slot the landed constructor (0x00595AC0) fills m_slots with.
// The name is fixed by the pinned fill instance at 0x0058ACB0.
struct Gen_p24pod
{
	_STL::list<Rva0058D930ListEntry>::iterator m_bfmeABC;
	int m_bfmeBBC;
	int m_bfmeCBC;
	int m_bfmeDBC;
	int m_bfmeEBC;
	bool m_bfmeFBC;
	bool m_bfmeGBC;
};

// Layout witnessed by ??0AptPalantirHeroSelector@@QAE@XZ (0x00595AC0).
class AptPalantirHeroSelector
{
public:
	void rva0058d930();

private:
	bool m_active;
	_STL::list<Rva0058D930ListEntry> m_heroes;
	Gen_p24pod m_slots[ 17 ];
	bool m_selectAll;
	int m_window;
};

// 0x0058D930: the only caller is the anonymous ?d_00595e60, so no caller,
// vtable or string names this method; it keeps the address token (an
// earlier Bfme*-generator name, bfmeResetBC, had no evidence).
// Clears both flags, then refills every slot with the constructor's empty
// value (end iterator, 0, three -1s, two false flags).
void AptPalantirHeroSelector::rva0058d930()
{
	m_active = false;
	m_selectAll = false;

	Gen_p24pod param;
	param.m_bfmeABC = m_heroes.end();
	param.m_bfmeBBC = 0;
	param.m_bfmeCBC = -1;
	param.m_bfmeDBC = -1;
	param.m_bfmeEBC = -1;
	param.m_bfmeFBC = false;
	param.m_bfmeGBC = false;
	std::fill( m_slots, m_slots + 17, param );
}
