// ?Rva0069C6B0Remainder@@YGIPAPAURva0069C6B0Node@@I@Z (identity unknown)
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva0069C6B0Node
{
	char m_pad[8];
	unsigned int m_key;
};

unsigned int __stdcall Rva0069C6B0Remainder(Rva0069C6B0Node **head, unsigned int m)
{
	Rva0069C6B0Node *node = *head;
	if (!node)
	{
		_ReadWriteBarrier();
		return (unsigned int)node % m;
	}
	return node->m_key % m;
}
