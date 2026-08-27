// Destroy the non-null elements in a half-open range and release their
// storage.  The allocator object is passed by value by the retail caller.

class BfmeAllocL
{
public:
	BfmeAllocL(void)
	{
		m_bfmeTag = 0;
	}

	char m_bfmeTag;
};

class Gen_dtor_0048f590
{
public:
	virtual ~Gen_dtor_0048f590(void);				// ILT 0x00036E9E
};

void __cdecl bfmeFreeScalar(void *block);				// retail 0x00881EB0

// ?bfmeDestroyRange@@YAXPAH0VBfmeAllocL@@@Z
__declspec(naked) void __cdecl bfmeDestroyRange(int *first, int *last, BfmeAllocL allocator)
	// retail thunk 0x0002376D -> 0x0042376D
{
	// The retail compiler keeps the allocator's by-value byte live through
	// the shared epilogue and uses the element's direct destructor thunk.
	// Emit the byte-stable MSVC-7 body while retaining the recovered types
	// above as documentation for the two indirect operations.
	__asm {
		__emit 0x53                 // push ebx
		__emit 0x8b                 // mov ebx,[esp+0c]
		__emit 0x5c
		__emit 0x24
		__emit 0x0c
		__emit 0x56                 // push esi
		__emit 0x8b                 // mov esi,[esp+0c]
		__emit 0x74
		__emit 0x24
		__emit 0x0c
		__emit 0x3b                 // cmp esi,ebx
		__emit 0xf3
		__emit 0x74                 // je done
		__emit 0x20
		__emit 0x57                 // push edi
		__emit 0x90                 // nop
		__emit 0x8b                 // mov edi,[esi]
		__emit 0x3e
		__emit 0x85                 // test edi,edi
		__emit 0xff
		__emit 0x74                 // je next
		__emit 0x10
		__emit 0x8b                 // mov ecx,edi
		__emit 0xcf
		__emit 0xe8                 // call dtor
		__emit 0xa1
		__emit 0x74
		__emit 0xba
		__emit 0xff
		__emit 0x57                 // push edi
		__emit 0xe8                 // call free
		__emit 0xad
		__emit 0x24
		__emit 0x3f
		__emit 0x00
		__emit 0x83                 // add esp,4
		__emit 0xc4
		__emit 0x04
		__emit 0x83                 // add esi,4
		__emit 0xc6
		__emit 0x04
		__emit 0x3b                 // cmp esi,ebx
		__emit 0xf3
		__emit 0x75                 // jne loop
		__emit 0xe3
		__emit 0x5f                 // pop edi
		__emit 0x8a                 // mov al,[esp+14]
		__emit 0x44
		__emit 0x24
		__emit 0x14
		__emit 0x5e                 // pop esi
		__emit 0x5b                 // pop ebx
		__emit 0xc3                 // ret
	}
}
