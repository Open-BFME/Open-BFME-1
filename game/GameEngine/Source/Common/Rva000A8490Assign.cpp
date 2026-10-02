// cl: /O2 /Ob0 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "string_base.h"
#include <vector>

struct Gen_t_000a7cb0_p4pod;
struct ParticleSysBoneInfo;

// The two ILTs reach these existing vector assignments; keep their bodies
// in their owning translation units.
extern template class _STL::vector<Gen_t_000a7cb0_p4pod>;
extern template class _STL::vector<ParticleSysBoneInfo>;

class Rva000A8490Mid10
{
private:
	int m_00;
	int m_04;
	int m_08;
};

class Rva000A8490Mid24
{
private:
	int m_00;
};

class Rva000A8490
{
	virtual void handle();
	StringBase<char> m_04;
	StringBase<char> m_08;
	char m_0C;
	Rva000A8490Mid10 m_10;
	char m_1C;
	int m_20;
	Rva000A8490Mid24 m_24;

public:
	Rva000A8490 &operator=(const Rva000A8490 &other);
};

Rva000A8490 &Rva000A8490::operator=(const Rva000A8490 &other)
{
	m_04.set(other.m_04);
	m_08.set(other.m_08);
	m_0C = other.m_0C;
	*reinterpret_cast<_STL::vector<Gen_t_000a7cb0_p4pod> *>(&m_10) =
		*reinterpret_cast<const _STL::vector<Gen_t_000a7cb0_p4pod> *>(&other.m_10);
	m_1C = other.m_1C;
	m_20 = other.m_20;
	*reinterpret_cast<_STL::vector<ParticleSysBoneInfo> *>(&m_24) =
		*reinterpret_cast<const _STL::vector<ParticleSysBoneInfo> *>(&other.m_24);
	return *this;
}
