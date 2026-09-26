// Two more bodies the ledger had cut into pieces.
//
// 0x000C8990 zeroes +0x04 and +0x08 out of one xor and then stores its
// argument at +0x0C. The ledger kept the first eight bytes and claimed the
// rest as an alias of AudioEventRTS::setPlayingHandle, whose parameter is what
// names the argument type here.
//
// 0x0007B5A0 walks a chain of next pointers at +0x04 until one is null and
// stores the argument there. MSVC duplicates the store rather than branching
// back to it, so the empty case is its own three instructions -- which is why
// the ledger had this in three pieces, one of them a byte-dump row Ghidra
// already attributes to this function.
//
// The lea of ecx+4 before each test is the address of the link being examined;
// the load through it is the step.

typedef unsigned int UnsignedInt;

class Gen_000c8990
{
public:
	void bfmeSetPlaying(UnsignedInt handle);

private:
	char m_bfmeHead[0x04];
	int m_bfme0004;							// +0x04
	int m_bfme0008;							// +0x08
	UnsignedInt m_bfme000C;						// +0x0C
};

class Gen_0007b5a0
{
public:
	void bfmeAppend(void *value);

private:
	char m_bfmeHead[0x04];
	Gen_0007b5a0 *m_bfmeNext;					// +0x04
};

// ?bfmeSetPlaying@Gen_000c8990@@QAEXI@Z
void Gen_000c8990::bfmeSetPlaying(UnsignedInt handle)
{
	m_bfme0004 = 0;
	m_bfme0008 = 0;
	m_bfme000C = handle;
}

// ?bfmeAppend@Gen_0007b5a0@@QAEXPAX@Z
void Gen_0007b5a0::bfmeAppend(void *value)
{
	Gen_0007b5a0 *node = this;

	while (node->m_bfmeNext)
		node = node->m_bfmeNext;

	node->m_bfmeNext = (Gen_0007b5a0 *)value;
}
