// cl: /DNDEBUG /MD /GX- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ivendor/stlport /Ireference/shims/sweep
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Gen_t_00069cc0_p16cd
{
	int value[4];
};

typedef _STL::vector<Gen_t_00069cc0_p16cd> Rva0006A9D0Vector;

#pragma comment(linker, "/alternatename:??0?$vector@UGen_t_00069cc0_p16cd@@V?$allocator@UGen_t_00069cc0_p16cd@@@_STL@@@_STL@@QAE@ABV01@@Z=?j_0003ee4b@@YAXXZ")

class BfmeStateGQ
{
public:
	void bfmeSwapGQ(BfmeStateGQ *other);
};

class Rva0006A9D0State
{
public:
	Rva0006A9D0State(const Rva0006A9D0State &other)
		: m_value00(other.m_value00),
		  m_value04(other.m_value04),
		  m_values(other.m_values)
	{
		m_value18 = (int)m_values.end();
		m_value28 = 0.0f;
		m_value24 = 0.0f;
		m_value20 = 0.0f;
		m_value1C = 0.0f;
	}
	Rva0006A9D0State &operator=(const Rva0006A9D0State &other);

	int m_value00;
	int m_value04;
	Rva0006A9D0Vector m_values;
	int m_value14;
	int m_value18;
	float m_value1C;
	float m_value20;
	float m_value24;
	float m_value28;
};

Rva0006A9D0State &Rva0006A9D0State::operator=(const Rva0006A9D0State &other)
{
	Rva0006A9D0State copy(other);
	reinterpret_cast<BfmeStateGQ *>(this)->bfmeSwapGQ(
		reinterpret_cast<BfmeStateGQ *>(&copy));
	return *this;
}
