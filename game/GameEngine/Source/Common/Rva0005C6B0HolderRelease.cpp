// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the out-of-line release the destructor at 0x0005E1E0 tail jumps
// into. One pushed argument is cleaned with pop ecx, and the pointer is loaded
// into a register before the push rather than pushed straight from memory.

#include <stdlib.h>

class Rva0005C6B0Holder
{
public:
	void release(void);

private:
	char *m_text;
	char m_buffer[1];
};

// ?release@Rva0005C6B0Holder@@QAEXXZ
void Rva0005C6B0Holder::release(void)
{
	free(m_text);
}
