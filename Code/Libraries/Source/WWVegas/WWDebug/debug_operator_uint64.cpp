// cl: /DNDEBUG /MD /Oy- /EHsc

// Open-BFME-DS04: Debug::operator<<(unsigned __int64). Retail at 0x0088C2F0
// prefixes via AddOutput(m_prefix, strlen(m_prefix)), formats through
// _ui64toa into a stack buffer, then feeds the const char * stream at vtable
// +0x38. m_prefix sits at +0x9e70 and m_radix at +0x9e80 in the retail
// object, so the shim pads the members to those offsets.

#include <stdlib.h>
#include <string.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
public:
	virtual ~Debug();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual Debug &operator<<(char const *);
	Debug &operator<<(unsigned __int64);
	char m_pad[0x9e6c];
	char m_prefix[16];
	int m_radix;
private:
	void AddOutput(const char *, unsigned);
};

// Debug::operator<<(unsigned __int64)
Debug &Debug::operator<<(unsigned __int64 val)
{
	char help[64 + 1];
	AddOutput(m_prefix, strlen(m_prefix));
	return (*this) << _ui64toa(val, help, m_radix);
}
