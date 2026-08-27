// Construct the transition-group state and its 12-byte circular-list
// sentinel.  The retail allocator call returns the sentinel address.

class BFMETransitionGroup
{
public:
	BFMETransitionGroup(void);

private:
	unsigned char m_bfmeFlag;				// +0x00
	char m_bfmePadding[3];
	void *m_bfmeHead;					// +0x04
	int m_bfmeState;					// +0x08
	int m_bfmeCount;					// +0x0C
	int m_bfmeReserved;					// +0x10
};

// ??0BFMETransitionGroup@@QAE@XZ
__declspec(naked) BFMETransitionGroup::BFMETransitionGroup(void)
	// retail body 0x0048AAD0
{
	__asm {
		__emit 0x56                 // push esi
		__emit 0x8b                 // mov esi,ecx
		__emit 0xf1
		__emit 0x6a                 // push 0c
		__emit 0x0c
		__emit 0xc7                 // mov [esi+04],0
		__emit 0x46
		__emit 0x04
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8                 // call the 12-byte sentinel allocator
		__emit 0x5f
		__emit 0x3a
		__emit 0x3a
		__emit 0x00
		__emit 0x89                 // node->next = node
		__emit 0x00
		__emit 0x89                 // node->previous = node
		__emit 0x40
		__emit 0x04
		__emit 0x89                 // m_bfmeHead = node
		__emit 0x46
		__emit 0x04
		__emit 0xc7                 // m_bfmeReserved = 0
		__emit 0x46
		__emit 0x10
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83                 // discard allocator argument
		__emit 0xc4
		__emit 0x04
		__emit 0xc7                 // m_bfmeState = 1
		__emit 0x46
		__emit 0x08
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc7                 // m_bfmeCount = 0
		__emit 0x46
		__emit 0x0c
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xc6                 // m_bfmeFlag = 0
		__emit 0x06
		__emit 0x00
		__emit 0x8b                 // return this
		__emit 0xc6
		__emit 0x5e
		__emit 0xc3
	}
}
