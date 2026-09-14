// cl: /DNDEBUG /MD /EHs-c-
// Out-of-line growth routine used by the retail conversion buffers.

#include <stdlib.h>

typedef unsigned int UnsignedInt;
typedef long HRESULT;

#define W3_E_OUTOFMEMORY ((HRESULT)0x8007000EL)

extern "C" __declspec(noreturn) void __stdcall W3AtlThrow(HRESULT hr);

class Rva0005CBD0Buffer
{
public:
	void grow(UnsignedInt size);
	char *m_cursor;
	char m_buffer[0x80];
};

// ?grow@Rva0005CBD0Buffer@@QAEXI@Z
void Rva0005CBD0Buffer::grow(UnsignedInt size)
{
	char *block = (char *)malloc(size);
	if (block == 0) {
		W3AtlThrow(W3_E_OUTOFMEMORY);
	}
	m_cursor = block;
}
