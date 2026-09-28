// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport
#include <stl/_config.h>
#include <string>

struct Rva009D8100Value
{
	void *m_value;
};

class Rva009D8100Owner
{
public:
	Rva009D8100Owner(const std::string &name, const Rva009D8100Value *value);

private:
	std::string m_name;
	void *m_value;
};

Rva009D8100Owner::Rva009D8100Owner(const std::string &name, const Rva009D8100Value *value)
	: m_name(name), m_value(value->m_value)
{
}
