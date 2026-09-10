// ?bfmeForward@Gen_003C6340Target@@QAEXPAX@Z
// partial score=0.78 date=2026-09-09
// stlport
// Thirty-six guarded delegates, written from the shape they share.
//
// Each reads one pointer -- a member at a fixed offset, or a global -- and
// tail-jumps to the same call when it is not null. The jump only appears
// because the callee takes exactly the arguments the wrapper was handed; the
// false path falls through to whatever constant the body returns.
//
// Three decoding rules carry the whole family. The ret immediate divided by
// four is the argument count. The width of the constant on the fall-through
// path fixes the return type: xor al,al and mov al,1 are Bool, xor eax,eax,
// or eax,-1 and mov eax,imm are Int, and no constant at all is void. And the
// source of the pointer fixes the calling convention: a member read through
// ecx is a thiscall member, a global read is a free function, __stdcall when
// it has arguments to clean and __cdecl when it has none.

typedef bool Bool;

// The guarded delegate at 0x003C6340 tail-jumps through ILT 0x0000600F to
// this target.  Retail walks and erases one matching AsciiString from the
// three-pointer range at +0xD4.  Keep the string/vector layout TU-local: the
// target's caller proves the method identity, while the body only needs the
// already-matched StringBase set and AsciiString destructor callees.
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)
extern const char Rva006A16B0Empty[];

struct Gen_003C6340StringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_length;
	unsigned short m_pad;
};

class AsciiString
{
public:
	__forceinline int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherText = other.m_data ? (const char *)(other.m_data + 1) : Rva006A16B0Empty;
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? (const char *)(m_data + 1) : Rva006A16B0Empty;
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisText, otherText, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	__forceinline bool operator==(const AsciiString &other) const
	{
		return compare(other) == 0;
	}

	void set(const AsciiString &other);
	~AsciiString();

private:
	Gen_003C6340StringData *m_data;
};

struct Gen_003C6340Vector
{
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;

	__forceinline void erase(AsciiString *position)
	{
		int count = m_finish - (position + 1);
		if (count > 0)
		{
			AsciiString *source = position + 1;
			AsciiString *result = position;
			while (count > 0)
			{
				result->set(*source);
				++source;
				++result;
				--count;
			}
		}
		--m_finish;
		m_finish->~AsciiString();
	}
};

class Gen_000C9770Target
{
public:
	void bfmeForward(void *a0);		// retail 0x000107D5
};
class Gen_000C9770
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x220];
	Gen_000C9770Target *m_bfmeImpl;				// +0x220
};
class Gen_000C9B40Target
{
public:
	void bfmeForward(void *a0);		// retail 0x0004AFAC
};
class Gen_000C9B40
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x67C];
	Gen_000C9B40Target *m_bfmeImpl;				// +0x67C
};
class Gen_001BF950Target
{
public:
	int bfmeForward(void *a0, void *a1);		// retail 0x000044C6
};
class Gen_001BF950
{
public:
	int bfmeForward(void *a0, void *a1);

private:
	char m_bfmeHead[0x1EC];
	Gen_001BF950Target *m_bfmeImpl;				// +0x1EC
};
class Gen_001D5EE0Target
{
public:
	void bfmeForward(void *a0, void *a1);		// retail 0x0002133C
};
class Gen_001D5EE0
{
public:
	void bfmeForward(void *a0, void *a1);

private:
	char m_bfmeHead[0x4];
	Gen_001D5EE0Target *m_bfmeImpl;				// +0x4
};
class Gen_002DDCC0Target
{
public:
	void bfmeForward(void *a0, void *a1);		// retail 0x00022D86
};
class Gen_002DDCC0
{
public:
	void bfmeForward(void *a0, void *a1);

private:
	char m_bfmeHead[0x64];
	Gen_002DDCC0Target *m_bfmeImpl;				// +0x64
};
class Gen_002F1290Target
{
public:
	void bfmeForward(void *a0);		// retail 0x00005E25
};
extern Gen_002F1290Target *TheBfmeTarget_002F1290;			// 0x12f1028
class Gen_003C6340Target
{
public:
	void bfmeForward(void *a0);		// retail 0x0000600F

private:
	char m_bfmeHead[0xD4];
	Gen_003C6340Vector m_bfmeValues;
};

// ?bfmeForward@Gen_003C6340Target@@QAEXPAX@Z
void Gen_003C6340Target::bfmeForward(void *a0)
{
	AsciiString *value = static_cast<AsciiString *>(a0);
	Gen_003C6340Vector &values = m_bfmeValues;
	AsciiString *current = values.m_start;
	while (current != values.m_finish)
	{
		if (*current == *value)
		{
			values.erase(current);
			return;
		}
		++current;
	}
}

class Gen_003C6340
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x8];
	Gen_003C6340Target *m_bfmeImpl;				// +0x8
};
class Gen_004125F0Target
{
public:
	void bfmeForward(void *a0, void *a1);		// retail 0x0002A8D3
};
class Gen_004125F0
{
public:
	void bfmeForward(void *a0, void *a1);

private:
	char m_bfmeHead[0x3BC];
	Gen_004125F0Target *m_bfmeImpl;				// +0x3BC
};
class Gen_00429F60Target
{
public:
	void bfmeForward(void *a0, void *a1);		// retail 0x00022D86
};
class Gen_00429F60
{
public:
	void bfmeForward(void *a0, void *a1);

private:
	char m_bfmeHead[0xB4];
	Gen_00429F60Target *m_bfmeImpl;				// +0xB4
};
class Gen_0042E700Target
{
public:
	int bfmeForward(void *a0, void *a1, void *a2);		// retail 0x0002282C
};
class Gen_0042E700
{
public:
	int bfmeForward(void *a0, void *a1, void *a2);

private:
	char m_bfmeHead[0xB0];
	Gen_0042E700Target *m_bfmeImpl;				// +0xB0
};
class Gen_0043A570Target
{
public:
	void bfmeForward(void *a0);		// retail 0x0002B526
};
class Gen_0043A570
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x4];
	Gen_0043A570Target *m_bfmeImpl;				// +0x4
};
class Gen_0043BC10Target
{
public:
	void bfmeForward(void *a0, void *a1);		// retail 0x000198B2
};
class Gen_0043BC10
{
public:
	void bfmeForward(void *a0, void *a1);

private:
	char m_bfmeHead[0x81C];
	Gen_0043BC10Target *m_bfmeImpl;				// +0x81C
};
class Gen_005169E0Target
{
public:
	bool bfmeForward(void *a0);		// retail 0x00024B7C
};
extern Gen_005169E0Target *TheBfmeTarget_005169E0;			// 0x12f7730
class Gen_0060D600Target
{
public:
	void bfmeForward(void *a0);		// retail 0x00017544
};
class Gen_0060D600
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x28C];
	Gen_0060D600Target *m_bfmeImpl;				// +0x28C
};
class Gen_00681960Target
{
public:
	void bfmeForward(void *a0);		// retail 0x0001D1BA
};
class Gen_00681960
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x8];
	Gen_00681960Target *m_bfmeImpl;				// +0x8
};
class Gen_00681B60Target
{
public:
	int bfmeForward(void);		// retail 0x0000355D
};
class Gen_00681B60
{
public:
	int bfmeForward(void);

private:
	char m_bfmeHead[0x8];
	Gen_00681B60Target *m_bfmeImpl;				// +0x8
};
class Gen_00681B80Target
{
public:
	int bfmeForward(void);		// retail 0x0004A291
};
class Gen_00681B80
{
public:
	int bfmeForward(void);

private:
	char m_bfmeHead[0x8];
	Gen_00681B80Target *m_bfmeImpl;				// +0x8
};
class Gen_00681DD0Target
{
public:
	bool bfmeForward(void *a0);		// retail 0x000486B2
};
class Gen_00681DD0
{
public:
	bool bfmeForward(void *a0);

private:
	char m_bfmeHead[0x8];
	Gen_00681DD0Target *m_bfmeImpl;				// +0x8
};
class Gen_00688AB0Target
{
public:
	void bfmeForward(void *a0);		// retail 0x00012F03
};
extern Gen_00688AB0Target *TheBfmeTarget_00688AB0;			// 0x12f4998
class Gen_006BC890Target
{
public:
	void bfmeForward(void *a0);		// retail 0x008F8110
};
class Gen_006BC890
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x7C];
	Gen_006BC890Target *m_bfmeImpl;				// +0x7C
};
class Gen_006BE210Target
{
public:
	bool bfmeForward(void *a0, void *a1);		// retail 0x00020923
};
extern Gen_006BE210Target *TheBfmeTarget_006BE210;			// 0x12f7fe0
class Gen_006C7690Target
{
public:
	void bfmeForward(void *a0);		// retail 0x0000DB11
};
class Gen_006C7690
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x30B0];
	Gen_006C7690Target *m_bfmeImpl;				// +0x30B0
};
class Gen_006C8870Target
{
public:
	void bfmeForward(void *a0);		// retail 0x00014051
};
class Gen_006C8870
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x3098];
	Gen_006C8870Target *m_bfmeImpl;				// +0x3098
};
class Gen_006C89D0Target
{
public:
	int bfmeForward(void *a0, void *a1);		// retail 0x0002E771
};
class Gen_006C89D0
{
public:
	int bfmeForward(void *a0, void *a1);

private:
	char m_bfmeHead[0x30B4];
	Gen_006C89D0Target *m_bfmeImpl;				// +0x30B4
};
class Gen_006C8A60Target
{
public:
	bool bfmeForward(void *a0);		// retail 0x0001F640
};
class Gen_006C8A60
{
public:
	bool bfmeForward(void *a0);

private:
	char m_bfmeHead[0x3094];
	Gen_006C8A60Target *m_bfmeImpl;				// +0x3094
};
class Gen_006C8A80Target
{
public:
	bool bfmeForward(void *a0);		// retail 0x00027B0B
};
class Gen_006C8A80
{
public:
	bool bfmeForward(void *a0);

private:
	char m_bfmeHead[0x3094];
	Gen_006C8A80Target *m_bfmeImpl;				// +0x3094
};
class Gen_006C8C00Target
{
public:
	void bfmeForward(void *a0);		// retail 0x00002257
};
class Gen_006C8C00
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x30B4];
	Gen_006C8C00Target *m_bfmeImpl;				// +0x30B4
};
class Gen_00730E00Target
{
public:
	void bfmeForward(void *a0);		// retail 0x0001E597
};
class Gen_00730E00
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x10];
	Gen_00730E00Target *m_bfmeImpl;				// +0x10
};
class Gen_00730E60Target
{
public:
	int bfmeForward(void *a0, void *a1);		// retail 0x0001847B
};
class Gen_00730E60
{
public:
	int bfmeForward(void *a0, void *a1);

private:
	char m_bfmeHead[0x10];
	Gen_00730E60Target *m_bfmeImpl;				// +0x10
};
class Gen_00730F10Target
{
public:
	bool bfmeForward(void *a0);		// retail 0x000164FF
};
class Gen_00730F10
{
public:
	bool bfmeForward(void *a0);

private:
	char m_bfmeHead[0x10];
	Gen_00730F10Target *m_bfmeImpl;				// +0x10
};
class Gen_00730F50Target
{
public:
	void bfmeForward(void *a0);		// retail 0x00047604
};
class Gen_00730F50
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x10];
	Gen_00730F50Target *m_bfmeImpl;				// +0x10
};
class Gen_0075BE40Target
{
public:
	void bfmeForward(void *a0);		// retail 0x0002B526
};
class Gen_0075BE40
{
public:
	void bfmeForward(void *a0);

private:
	char m_bfmeHead[0x17C];
	Gen_0075BE40Target *m_bfmeImpl;				// +0x17C
};
class Gen_0094BFA0Target
{
public:
	void bfmeForward(void);		// retail 0x009EB7A0
};
class Gen_0094BFA0
{
public:
	void bfmeForward(void);

private:
	char m_bfmeHead[0x4];
	Gen_0094BFA0Target *m_bfmeImpl;				// +0x4
};
class Gen_0094BFB0Target
{
public:
	void bfmeForward(void);		// retail 0x009EB7A0
};
class Gen_0094BFB0
{
public:
	void bfmeForward(void);

private:
	char m_bfmeHead[0x4];
	Gen_0094BFB0Target *m_bfmeImpl;				// +0x4
};
class Gen_009EBB40Target
{
public:
	int bfmeForward(void);		// retail 0x009EE620
};
extern Gen_009EBB40Target *TheBfmeTarget_009EBB40;			// 0x134faac
class Gen_009EBB60Target
{
public:
	int bfmeForward(void);		// retail 0x009EDE40
};
extern Gen_009EBB60Target *TheBfmeTarget_009EBB60;			// 0x134faac

// ?bfmeForward@Gen_000C9770@@QAEXPAX@Z
void Gen_000C9770::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_000C9B40@@QAEXPAX@Z
void Gen_000C9B40::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_001BF950@@QAEHPAX0@Z
int Gen_001BF950::bfmeForward(void *a0, void *a1)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a0, a1);

	return 0;
}
// ?bfmeForward@Gen_001D5EE0@@QAEXPAX0@Z
void Gen_001D5EE0::bfmeForward(void *a0, void *a1)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0, a1);
}
// ?bfmeForward@Gen_002DDCC0@@QAEXPAX0@Z
void Gen_002DDCC0::bfmeForward(void *a0, void *a1)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0, a1);
}
// ?bfmeForward_002F1290@@YGXPAX@Z
void __stdcall bfmeForward_002F1290(void *a0)
{
	if (TheBfmeTarget_002F1290)
		TheBfmeTarget_002F1290->bfmeForward(a0);
}
// ?bfmeForward@Gen_003C6340@@QAEXPAX@Z
void Gen_003C6340::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_004125F0@@QAEXPAX0@Z
void Gen_004125F0::bfmeForward(void *a0, void *a1)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0, a1);
}
// ?bfmeForward@Gen_00429F60@@QAEXPAX0@Z
void Gen_00429F60::bfmeForward(void *a0, void *a1)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0, a1);
}
// ?bfmeForward@Gen_0042E700@@QAEHPAX00@Z
int Gen_0042E700::bfmeForward(void *a0, void *a1, void *a2)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a0, a1, a2);

	return 0;
}
// ?bfmeForward@Gen_0043A570@@QAEXPAX@Z
void Gen_0043A570::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_0043BC10@@QAEXPAX0@Z
void Gen_0043BC10::bfmeForward(void *a0, void *a1)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0, a1);
}
// ?bfmeForward_005169E0@@YG_NPAX@Z
bool __stdcall bfmeForward_005169E0(void *a0)
{
	if (TheBfmeTarget_005169E0)
		return TheBfmeTarget_005169E0->bfmeForward(a0);

	return false;
}
// ?bfmeForward@Gen_0060D600@@QAEXPAX@Z
void Gen_0060D600::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_00681960@@QAEXPAX@Z
void Gen_00681960::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_00681B60@@QAEHXZ
int Gen_00681B60::bfmeForward(void)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward();

	return -1;
}
// ?bfmeForward@Gen_00681B80@@QAEHXZ
int Gen_00681B80::bfmeForward(void)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward();

	return 0x31;
}
// ?bfmeForward@Gen_00681DD0@@QAE_NPAX@Z
bool Gen_00681DD0::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a0);

	return false;
}
// ?bfmeForward_00688AB0@@YGXPAX@Z
void __stdcall bfmeForward_00688AB0(void *a0)
{
	if (TheBfmeTarget_00688AB0)
		TheBfmeTarget_00688AB0->bfmeForward(a0);
}
// ?bfmeForward@Gen_006BC890@@QAEXPAX@Z
void Gen_006BC890::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward_006BE210@@YG_NPAX0@Z
bool __stdcall bfmeForward_006BE210(void *a0, void *a1)
{
	if (TheBfmeTarget_006BE210)
		return TheBfmeTarget_006BE210->bfmeForward(a0, a1);

	return false;
}
// ?bfmeForward@Gen_006C7690@@QAEXPAX@Z
void Gen_006C7690::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_006C8870@@QAEXPAX@Z
void Gen_006C8870::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_006C89D0@@QAEHPAX0@Z
int Gen_006C89D0::bfmeForward(void *a0, void *a1)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a0, a1);

	return 0;
}
// ?bfmeForward@Gen_006C8A60@@QAE_NPAX@Z
bool Gen_006C8A60::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a0);

	return false;
}
// ?bfmeForward@Gen_006C8A80@@QAE_NPAX@Z
bool Gen_006C8A80::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a0);

	return false;
}
// ?bfmeForward@Gen_006C8C00@@QAEXPAX@Z
void Gen_006C8C00::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_00730E00@@QAEXPAX@Z
void Gen_00730E00::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_00730E60@@QAEHPAX0@Z
int Gen_00730E60::bfmeForward(void *a0, void *a1)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a0, a1);

	return 0;
}
// ?bfmeForward@Gen_00730F10@@QAE_NPAX@Z
bool Gen_00730F10::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		return m_bfmeImpl->bfmeForward(a0);

	return false;
}
// ?bfmeForward@Gen_00730F50@@QAEXPAX@Z
void Gen_00730F50::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_0075BE40@@QAEXPAX@Z
void Gen_0075BE40::bfmeForward(void *a0)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward(a0);
}
// ?bfmeForward@Gen_0094BFA0@@QAEXXZ
void Gen_0094BFA0::bfmeForward(void)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward();
}
// ?bfmeForward@Gen_0094BFB0@@QAEXXZ
void Gen_0094BFB0::bfmeForward(void)
{
	if (m_bfmeImpl)
		m_bfmeImpl->bfmeForward();
}
// ?bfmeForward_009EBB40@@YAHXZ
int bfmeForward_009EBB40(void)
{
	if (TheBfmeTarget_009EBB40)
		return TheBfmeTarget_009EBB40->bfmeForward();

	return 100;
}
// ?bfmeForward_009EBB60@@YAHXZ
int bfmeForward_009EBB60(void)
{
	if (TheBfmeTarget_009EBB60)
		return TheBfmeTarget_009EBB60->bfmeForward();

	return 100;
}
