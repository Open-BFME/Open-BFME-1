// ?d_009064f0@@YAXXZ
// partial score=0.75 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc

#include <string.h>
#pragma intrinsic(strlen, memcpy)

extern "C" const char *__stdcall DXGetErrorString9A(long hresult);

#define BFME_STRING_EMPTY (*(char **)0x012D9124)

class StringClass
{
public:
	StringClass(const char *string, bool hint_temporary = false)
		: m_Buffer(BFME_STRING_EMPTY)
	{
		int len = string ? (int)strlen(string) : 0;
		if (hint_temporary || len > 0)
			Get_String(len + 1, hint_temporary);
		*this = string;
	}
	~StringClass() { Free_String(); }
	const StringClass &operator=(const char *string)
	{
		if (string != 0) {
			int len = (int)strlen(string);
			Uninitialised_Grow(len + 1);
			Store_Length(len);
			memcpy(m_Buffer, string, len + 1);
		}
		return *this;
	}
	operator const char *() const { return m_Buffer; }

private:
	struct Header { int allocated_length; int length; };
	void Get_String(int length, bool is_temp);
	void Uninitialised_Grow(int length);
	void Free_String();
	void Store_Length(int length)
	{
		if (m_Buffer != BFME_STRING_EMPTY)
			((Header *)m_Buffer - 1)->length = length;
	}
	char *m_Buffer;
};

class Debug
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual Debug &WriteInt(int);
	virtual void v12();
	virtual void v13();
	virtual Debug &WriteString(const char *);
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void SetPrefixAndRadix(const char *, int);
};

// ?DX8ErrorTranslator@@YA_NAAVDebug@@JPAX@Z
bool __cdecl DX8ErrorTranslator(Debug &debug, long hresult, void *user)
{
	StringClass error(DXGetErrorString9A(hresult));
	debug.WriteString((const char *)0x01132DD4);
	debug.SetPrefixAndRadix((const char *)0x01132DD4, 16);
	debug.WriteInt((int)user);
	debug.SetPrefixAndRadix((const char *)0x0107301C, 10);
	debug.WriteString((const char *)0x010E6E8C);
	debug.WriteString((const char *)error);
	debug.WriteString((const char *)0x01082804);
	return true;
}
