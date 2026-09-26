#include "windows.h"

struct Rva00958A30Record
{
	char m_reserved[8];
	volatile LONG m_refs;
};

class Rva00958A30Holder
{
public:
	void incrementRef();
	Rva00958A30Record *m_record;
};

void Rva00958A30Holder::incrementRef()
{
	if (m_record != 0)
		InterlockedIncrement(&m_record->m_refs);
}
