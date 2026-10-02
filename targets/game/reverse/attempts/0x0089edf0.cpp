// ?rva0089EDF0@@YAXPAVBfmeStrVKI@@PBDZZ
// partial score=0.7344 date=2026-10-02
// ?rva0089EDF0@@YAXPAVBfmeStrVKI@@PBDZZ
// cl: /O2 /DNDEBUG /MD
// Bank only: native original method name remains unproved; address retained.
// Reuses the existing opaque cdecl binding: object then format on stack.
// Native identity is unproved. The buffer helper is synthetic and inlined.
// This body formats replacement text, unlike append sibling 0089ECD0.
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

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	typedef BfmeStringData3AF0 StringDataC;

	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	StringDataC *m_data;

	__forceinline void rva0089EDF0ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

};

void BfmeStrVKI::rva0089EDF0ChangeBuffer(unsigned int reserve, unsigned int offset,
	unsigned int copy, CBPushZero pushZero, unsigned int internalSize)
{
	StringDataC *oldData = m_data;
	BfmeStrVKI *self = this;
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
		self->m_data = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refCount;
	}

	if (--oldData->m_refCount == 0)
		g_bfmeStringPool1284->free(oldData);
}

void rva0089EDF0(BfmeStrVKI *self, const char *format, ...)
{
	unsigned int extra = strlen(format) * 4;
	unsigned int oldSize = 0;
	for (;;)
	{
		self->rva0089EDF0ChangeBuffer(oldSize + extra, 0, 0, BfmeStrVKI::CB_NO_PUSH_ZERO, 0);
		BfmeStrVKI::StringDataC *data = self->m_data;
		char *buffer = reinterpret_cast<char *>(data) + 8;
		int written = _vsnprintf(buffer + oldSize,
			data->m_maxSize - oldSize, format, reinterpret_cast<char *>(&format + 1));
		if (written >= 0)
		{
			buffer[oldSize + written] = 0;
			self->m_data->m_size = (unsigned short)(oldSize + written);
			self->m_data->m_hash = 0;
			return;
		}
		extra *= 2;
	}
}
