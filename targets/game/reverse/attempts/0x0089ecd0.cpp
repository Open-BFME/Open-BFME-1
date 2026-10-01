// ?rva0089ECD0@Rva0089ECD0@@QAAXPBDZZ
// partial score=0.7273 date=2026-10-01
// cl: /O2 /DNDEBUG /MD
// Bank only: native original method name remains unproved; address retained.
// Physical retail ABI is cdecl member varargs (this then format on stack).
// Header declarations retain the genuine _vsnprintf four-argument contract;
// _CRTIMP is empty to emit the actual retail import-thunk route, not direct IAT.
// The allocator/free slots are both at actual global 01337A30; do not reuse
// the historical g_bfmeAllocVKJ pin at F37A30. No shared declarations changed.

#define _CRTIMP
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#pragma intrinsic(memcpy)

struct BfmeStringPool3AF0
{
	void *(__cdecl *allocate)(unsigned int);
	void (__cdecl *free)(void *storage);
};

struct EAStringData
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

extern EAStringData g_emptyStringData;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class Rva0089ECD0
{
	typedef EAStringData StringDataC;

	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	StringDataC *m_data;

	__forceinline void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

public:
	void rva0089ECD0(const char *format, ...);
};

void Rva0089ECD0::ChangeBuffer(unsigned int reserve, unsigned int offset,
	unsigned int copy, CBPushZero pushZero, unsigned int internalSize)
{
	StringDataC *oldData = m_data;
	Rva0089ECD0 *self = this;
	if (oldData->m_refCount == 1 && reserve <= oldData->m_maxSize)
	{
		self->m_data->m_size = (unsigned short)internalSize;
		self->m_data->m_hash = 0;
		if (pushZero != CB_NO_PUSH_ZERO)
			((char *)self->m_data + sizeof(StringDataC))[internalSize] = 0;
		return;
	}

	if (reserve != 0)
	{
		unsigned int allocationSize = (reserve + (reserve >> 3) + 0xc) & ~3;
		self->m_data = (StringDataC *)g_bfmeStringPool1284->allocate(allocationSize);
		self->m_data->m_refCount = 1;
		self->m_data->m_maxSize = (unsigned short)(allocationSize - 9);
		self->m_data->m_size = (unsigned short)internalSize;
		self->m_data->m_hash = 0;
		memcpy((char *)self->m_data + sizeof(StringDataC),
		    (char *)oldData + sizeof(StringDataC) + offset, copy);
		if (pushZero != CB_NO_PUSH_ZERO)
			((char *)self->m_data + sizeof(StringDataC))[internalSize] = 0;
	}
	else
	{
		self->m_data = &g_emptyStringData;
		++g_emptyStringData.m_refCount;
	}

	if (--oldData->m_refCount == 0)
		g_bfmeStringPool1284->free(oldData);
}

void Rva0089ECD0::rva0089ECD0(const char *format, ...)
{
	unsigned int extra = strlen(format) * 4;
	unsigned int oldSize = m_data->m_size;
	for (;;)
	{
		ChangeBuffer(oldSize + extra, 0, 0, CB_NO_PUSH_ZERO, 0);
		StringDataC *data = m_data;
		int written = _vsnprintf(reinterpret_cast<char *>(data) + 8 + oldSize,
			data->m_maxSize - oldSize, format, reinterpret_cast<char *>(&format + 1));
		if (written >= 0)
		{
			(reinterpret_cast<char *>(data) + 8)[oldSize + written] = 0;
			m_data->m_size = (unsigned short)(oldSize + written);
			m_data->m_hash = 0;
			return;
		}
		extra *= 2;
	}
}
