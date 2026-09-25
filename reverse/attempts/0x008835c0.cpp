// ?Rva008835C0UpdateDescription@@YAXPAURva008835C0Owner@@PAXPBDZZ
// partial score=0.394558 date=2026-09-25
// ?d_008835c0@@YAXXZ
// Address-derived identity: updates the formatted description of an existing
// allocation record in the 0x2B7B-bucket tracker.
// cl: /DNDEBUG /MD /EHsc

#include <stdarg.h>
#include <string.h>

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);
extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(
	void *, unsigned long, unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(
	void *, unsigned long, void *);
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(
	char *, unsigned int, const char *, va_list);

struct Rva008835C0Record
{
	Rva008835C0Record *m_next;          // +0x00
	unsigned int m_field04;                // +0x04
	void *m_block;                      // +0x08
	unsigned int m_field0C;                // +0x0c
	unsigned int m_field10;              // +0x10
	char *m_description;                // +0x14
	char m_pad18[0x84];
	int m_field9C;                   // +0x9c
};

struct Rva008835C0Owner
{
	char m_pad00[0x0c];
	Rva008835C0Record *m_buckets[0x2b7b];
	char m_pad282c0[0x282c0 - 0x0c - 0x2b7b * 4];
	unsigned char m_disabled;           // +0x282c0
	char m_pad282c1[7];
	void *m_lock;                       // +0x282c8
};


void __cdecl Rva008835C0UpdateDescription(
	Rva008835C0Owner *owner, void *block, const char *format, ...)
{
	char buffer[0x200];
	if (owner->m_disabled)
		return;

	if (owner->m_lock)
		EnterCriticalSection(owner->m_lock);

	Rva008835C0Record **link =
		&owner->m_buckets[(unsigned int)block % 0x2b7b];
	while (*link && (*link)->m_block != block)
		link = &(*link)->m_next;

	Rva008835C0Record *record = *link;
	if (record && record->m_field9C < 0)
	{

	if (record->m_description)
	{
		HeapFree(GetProcessHeap(), 4, record->m_description);
	}

	if (format)
	{
		va_list args;
		va_start(args, format);
		if (_vsnprintf(buffer, sizeof(buffer), format, args) < 0)
			buffer[sizeof(buffer) - 1] = 0;
		va_end(args);

		unsigned int length = (unsigned int)strlen(buffer) + 1;
		record->m_description = (char *)HeapAlloc(GetProcessHeap(), 4, length);
		memcpy(record->m_description, buffer, length);
	}
	else
		record->m_description = 0;

	}
	if (owner->m_lock)
		LeaveCriticalSection(owner->m_lock);
}
