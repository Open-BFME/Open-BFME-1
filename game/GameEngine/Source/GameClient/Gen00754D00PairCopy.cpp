// cl: /EHsc
// stlport
// STLport tree payload copy at retail 0x00754D00.

#include <map>
#include <new>
#include <string>

struct Gen_t_00770a90_k4
{
	_STL::string m_key;
};

struct Gen_t_00770a90_p12cd
{
	_STL::string m_value0;
	_STL::string m_value1;
	int m_value24;
	int m_value28;

	Gen_t_00770a90_p12cd()
	{
	}

	__forceinline Gen_t_00770a90_p12cd(const Gen_t_00770a90_p12cd &other)
		: m_value0(other.m_value0),
		  m_value1(other.m_value1),
		  m_value24(other.m_value24),
		  m_value28(other.m_value28)
	{
	}
};

typedef _STL::pair<const Gen_t_00770a90_k4, Gen_t_00770a90_p12cd>
	Gen00770A90Pair;

namespace _STL
{
	template<> struct pair<const Gen_t_00770a90_k4, Gen_t_00770a90_p12cd>
	{
		_STL::string m_key;
		_STL::string m_value0;
		_STL::string m_value1;
		int m_value24;
		int m_value28;

		__declspec(noinline) pair(const pair &other)
			: m_key(other.m_key),
			  m_value0(other.m_value0),
			  m_value1(other.m_value1),
			  m_value24(other.m_value24),
			  m_value28(other.m_value28)
		{
		}
	};
}

Gen00770A90Pair *copy_gen_pair(Gen00770A90Pair *result,
	const Gen00770A90Pair &other)
{
	return new (result) Gen00770A90Pair(other);
}
