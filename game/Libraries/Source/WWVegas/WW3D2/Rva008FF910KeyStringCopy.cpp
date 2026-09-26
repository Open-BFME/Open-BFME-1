// stlport
// cl: /O2 /Ob0 /MD /D_STLP_USE_STATIC_LIB
#include <string>

class Rva008FF910
{
	unsigned m_key;
	_STL::string m_value;

public:
	Rva008FF910(const Rva008FF910 &other);
};

Rva008FF910::Rva008FF910(const Rva008FF910 &other)
	: m_key(other.m_key), m_value(other.m_value)
{
}
