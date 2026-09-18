// ?d_002d8c10@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.97 date=2026-09-18
// Retail 0x002D8C10 parser; the owning type is not independently identified.
// The record layout is three four-byte fields: string, string, and integer.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oi
// stlport

class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	void set(const char *text, int length);

private:
	void *m_data;
};

class BFMERetailAsciiString : public RetailLayoutString
{
public:
	BFMERetailAsciiString(const char *text);
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *separators);
	static int scanInt(const char *text);
};

#pragma intrinsic(strlen)
extern "C" unsigned int __cdecl strlen(const char *text);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva002D8C10Record
{
	BFMERetailAsciiString m_first;
	RetailLayoutString m_second;
	int m_number;

	Rva002D8C10Record()
		: m_first(reinterpret_cast<const char *>(0x0107301c)), m_second(), m_number(0)
	{
	}
};

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

void __cdecl d_002d8c10(INI *ini, void *, void *, const void *userData)
{
	Rva002D8C10Record *record = new Rva002D8C10Record;
	const char *token = ini->getNextTokenOrNull(0);
	if (token != 0)
		record->m_first.set(token, (int)strlen(token));
	else
		record->m_first.set(reinterpret_cast<const char *>(0x0107301c), 0);

	token = ini->getNextTokenOrNull(0);
	if (token != 0)
		record->m_number = INI::scanInt(token);
	else
		record->m_number = 0;

	token = ini->getNextTokenOrNull(0);
	if (token != 0)
	{
		const char *cursor = token;
		_ReadWriteBarrier();
		RetailLayoutString *second = &record->m_second;
		const char *start = cursor + 1;
		while (*cursor++ != 0)
			;
		second->set(token, (int)(cursor - start));
	}
	else
		record->m_second.set(0, 0);

	((_STL::vector<Rva002D8C10Record *> *)userData)->push_back(record);
}
