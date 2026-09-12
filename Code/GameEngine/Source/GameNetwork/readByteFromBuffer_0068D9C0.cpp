// cl: /DNDEBUG /MD /EHs-c-

// The anonymous LAN game-info decoder at 0x0068EF70 calls this byte-identical
// bounded byte reader at retail address 0x0068D9C0.

typedef unsigned char UnsignedByte;

extern "C" UnsignedByte *readByteFromBuffer_0068D9C0(UnsignedByte *buffer,
	UnsignedByte *out, UnsignedByte *end)
{
	if (end != 0)
	{
		if (buffer > end)
			return buffer;
		if (buffer + 1 > end)
			return buffer;
	}
	__asm
	{
		mov dl, byte ptr [eax]
		mov ecx, dword ptr [esp + 8]
		mov byte ptr [ecx], dl
	}
	return buffer + 1;
}
