// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x00725B70, 111 bytes. Four repetitions of one idiom:
//
//   cmp ecx, edi        edi is a hoisted zero, used by four tests and four
//   je next             stores
//   dec [ecx + 4]       release a reference
//   jne next            and only when it reaches zero
//   mov eax, [ecx]      go through vtable slot 0, no arguments
//   call [eax]
//   next: [member] = edi
//
// which is the WW3D reference-pointer release: null check, Release_Ref, then
// clear. Release_Ref itself inlines to the dec/jne pair because dec sets the
// zero flag, so the count and its test are one instruction and a branch.
//
// The members go in the order +0xD8, +0xE8, +0xE4, +0xE0 -- not offset order,
// which is why they have to be written out one at a time rather than swept.
//
// The last two bytes are xor eax,eax, so this is not the void ?Free@ the
// symbol table has pinned at ILT 0x00014BC3: it hands back a zero. WW3D's own
// convention for a Free is to return WW3DErrorType, and WW3D_ERROR_OK is that
// zero, so that is the signature used here -- a different decorated name from
// the void one, which stays where it is.

enum WW3DErrorType
{
	WW3D_ERROR_OK = 0
};

class BfmeRefCounted
{
public:
	virtual void Delete_Self(void) = 0;				// vtable slot 0

	void Release_Ref(void)
	{
		m_bfmeRefCount--;

		if (m_bfmeRefCount == 0)
			Delete_Self();
	}

	int m_bfmeRefCount;						// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/distlod.h
class DistLODClass
{
private:
	WW3DErrorType Free(void);

	char m_bfmeHead[0xD8];
	BfmeRefCounted *m_bfme00D8;					// +0xD8
	BfmeRefCounted *m_bfme00DC;					// +0xDC
	BfmeRefCounted *m_bfme00E0;					// +0xE0
	BfmeRefCounted *m_bfme00E4;					// +0xE4
	BfmeRefCounted *m_bfme00E8;					// +0xE8
};

WW3DErrorType DistLODClass::Free(void)
{
	if (m_bfme00D8)
	{
		m_bfme00D8->Release_Ref();
		m_bfme00D8 = 0;
	}

	if (m_bfme00E8)
	{
		m_bfme00E8->Release_Ref();
		m_bfme00E8 = 0;
	}

	if (m_bfme00E4)
	{
		m_bfme00E4->Release_Ref();
		m_bfme00E4 = 0;
	}

	if (m_bfme00E0)
	{
		m_bfme00E0->Release_Ref();
		m_bfme00E0 = 0;
	}

	return WW3D_ERROR_OK;
}
