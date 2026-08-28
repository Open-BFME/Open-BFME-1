// cl: /DNDEBUG /MD /Oy- /EHsc

// Debug::operator<<(signed __int64), retail at 0x0088C290. It emits the
// configured prefix, formats in the selected radix, then streams the result.

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
	Debug &operator<<(__int64);
	char m_pad[0x9e6c];
	char m_prefix[16];
	int m_radix;

private:
	void AddOutput(const char *, unsigned);
};

Debug &Debug::operator<<(__int64 val)
{
	char help[64 + 1];
	AddOutput(m_prefix, strlen(m_prefix));
	return (*this) << _i64toa(val, help, m_radix);
}
