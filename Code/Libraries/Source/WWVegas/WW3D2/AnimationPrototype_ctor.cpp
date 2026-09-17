// cl: /DNDEBUG /MD /EHsc
#include <string.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	StringClass(const char *string);
	~StringClass();
	StringClass &operator=(const char *string);
	static char *m_EmptyString;
	char *m_Buffer;

private:
	void Get_String(int length, bool is_temp);
};

inline StringClass::StringClass(const char *string)
	: m_Buffer(m_EmptyString)
{
	int len = string ? (int)strlen(string) : 0;
	if (len > 0)
		Get_String(len + 1, false);
	*this = string;
}

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
	virtual void handle();

private:
	char m_pad[0x10];
};

class Rva0090BD60Proto : public GenBase009EB7D0
{
public:
	Rva0090BD60Proto(const char *name, int first, int second);

private:
	void *m_ptr;
	StringClass m_name;
	int m_first;
	int m_second;
};

Rva0090BD60Proto::Rva0090BD60Proto(const char *name, int first, int second)
	: m_ptr(0),
	  m_name(name),
	  m_first(first),
	  m_second(second)
{
}
