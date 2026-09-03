// cl: /DNDEBUG /MD /EHsc
// Two-token INI callback: retain a name and its integer value in an STLport
// vector supplied as the user-data argument.

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

class AsciiString
{
    char *m_text;

public:
    AsciiString() : m_text(0) {}
    ~AsciiString();
    void set(const char *text, int length);
};

class INI
{
public:
    const char *getNextToken(const char *separators);
    const char *getNextTokenOrNull(const char *separators);
    static int scanInt(const char *text);
};

namespace _STL
{
template <typename T>
class allocator
{
};

template <typename T, typename Allocator>
class vector
{
public:
    void push_back(const T &value);
};
}

struct Gen_t_00375e50_p8cd
{
    AsciiString m_name;
    int m_value;
};

class Gen_00375FF0
{
public:
	static void parse(INI *ini, void *instance, const void *userData);
};

void __cdecl Gen_00375FF0::parse(register INI *ini, void *, const void *userData)
{
	Gen_t_00375e50_p8cd value;
	const char *name = ini->getNextToken(0);
	if (name != 0) {
		value.m_name.set(name, (int)strlen(name));

		const char *number = ini->getNextTokenOrNull(0);
		if (number != 0) {
			value.m_value = INI::scanInt(number);
			((_STL::vector<Gen_t_00375e50_p8cd,
						   _STL::allocator<Gen_t_00375e50_p8cd> > *)userData)->push_back(value);
		}
	}
}
