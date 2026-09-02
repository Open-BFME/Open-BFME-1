// cl: /DNDEBUG /MD /EHsc
#include <string.h>

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

#define BFME_PROTO_CTOR( NAME )                                               \
	class NAME : public GenBase009EB7D0                                       \
	{                                                                         \
	public:                                                                   \
		NAME(const char *name, int first, int second);                        \
	private:                                                                  \
		void *m_ptr;                                                          \
		StringClass m_name;                                                   \
		int m_first;                                                          \
		int m_second;                                                         \
	};                                                                        \
	NAME::NAME(const char *name, int first, int second)                       \
		: m_ptr(0),                                                           \
		  m_name(name),                                                       \
		  m_first(first),                                                     \
		  m_second(second)                                                    \
	{                                                                         \
	}

BFME_PROTO_CTOR( Rva00970880Proto )
BFME_PROTO_CTOR( Rva00970EC0Proto )
BFME_PROTO_CTOR( Rva009712A0Proto )
BFME_PROTO_CTOR( Rva00971670Proto )
BFME_PROTO_CTOR( Rva00971CE0AggregatePrototype )
BFME_PROTO_CTOR( Rva009723C0Proto )
