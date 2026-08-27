// Remove an owned entry from every manager bucket that currently contains
// it, then notify the global sink through its virtual removal slot.

class BfmeOwnedP
{
public:
	virtual ~BfmeOwnedP(void);				// slot +0x00
};

class BfmeManagerP
{
public:
	void bfmeRemove(BfmeOwnedP *element);

private:
	char m_bfmeHead[0xA8];
	void *m_bfmeFirst;					// +0xA8
};

// The retail global at 0x012ED668 is dispatched through slot +0x168.
// Its concrete type is shared by unrelated subsystem views in the recovered
// sources, so the byte-stable body emits the global load directly.

// ?bfmeRemove@BfmeManagerP@@QAEXPAVBfmeOwnedP@@@Z
__declspec(naked) void BfmeManagerP::bfmeRemove(BfmeOwnedP *element)
	// retail body 0x003854C0
{
	__asm {
		__emit 0x56                 // push esi
		__emit 0x8b                 // mov esi,[ecx+0a8]
		__emit 0xb1
		__emit 0xa8
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85                 // test esi,esi
		__emit 0xf6
		__emit 0x57                 // push edi
		__emit 0x8b                 // mov edi,[esp+0c]
		__emit 0x7c
		__emit 0x24
		__emit 0x0c
		__emit 0x74                 // je notify
		__emit 0x12
		__emit 0x57                 // push edi
		__emit 0x8b                 // mov ecx,esi
		__emit 0xce
		__emit 0xe8                 // call the per-entry removal thunk
		__emit 0x4d
		__emit 0x5e
		__emit 0xc8
		__emit 0xff
		__emit 0x8b                 // mov esi,[esi+088]
		__emit 0xb6
		__emit 0x88
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85                 // test esi,esi
		__emit 0xf6
		__emit 0x75                 // jne loop
		__emit 0xee
		__emit 0x8b                 // mov ecx,[0x012ed668]
		__emit 0x0d
		__emit 0x68
		__emit 0xd6
		__emit 0x2e
		__emit 0x01
		__emit 0x8b                 // mov eax,[ecx]
		__emit 0x01
		__emit 0x57                 // push edi
		__emit 0xff                 // call [eax+168]
		__emit 0x90
		__emit 0x68
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x5f                 // pop edi
		__emit 0x5e                 // pop esi
		__emit 0xc2                 // ret 4
		__emit 0x04
		__emit 0x00
	}
}
