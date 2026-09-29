// ?bfmeCallDUL@@YG?AVRva0058C2B0RefPtr@@PBD@Z
// 0x0058C2B0, 170 bytes, byte-exact (`tools/probe.py` reports EXACT modulo
// relocation slots).
// cl: /DNDEBUG /MD /EHsc
//
// ---------------------------------------------------------------------------
// PROVED SIGNATURE: the function returns a CLASS BY VALUE
// ---------------------------------------------------------------------------
// The first stack slot is the object's address, not a value:
//   +006a  mov esi, [X+4]      ; esi = the hidden RETURN pointer
//   +006e  mov [esi], eax      ; returnObject.m_ptr = p
//   +0072  inc dword [eax+4]   ; if (p) ++p->ref
//   +0099  mov eax, esi        ; small class return: eax = the object address
//   +00a7  ret 8               ; [sret][const char *]
// The unwind map proves it independently: FuncInfo 0x00E267B8 has a state-0
// funclet at 0x00C37334 whose cleanup is
//   mov eax,[ebp-0x18] ; and eax,2 ; je ret
//   and dword [ebp-0x18],-3
//   mov ecx,[ebp+4]                       <- destroys the object AT [X+4]
//   jmp 0x0018336 -> 0x00107550 (the matched release body, `mov ecx,[ecx]`)
// whose first instruction is `mov ecx,[ecx]`, i.e. `this` is the returned
// object and it releases `this->m_ptr`.  The five matched callers at
// 0x006C1C10..0x006C1CD0 push the string and then the pointer they received and
// return that pointer, which is exactly an sret destination under MSVC's
// left-to-right push order.  Only MSVC's sret pointer and a by-value class
// parameter can put an object in the first stack slot, and the by-value
// spelling emits a normal-path destructor call retail does not have.
//
// `symbols.csv` pins this name at the ILT thunk 0x0001D467 with
// `route=0x0058C2B0`, which is what the five matched callers in
// BfmeConv785.cpp encode.  Those callers reach it through a
// function-pointer cast typed `void (void*, const char*)`, which emits retail's
// exact `push esi; push <string>` pair and no return-object temporary.  One
// name, one body, one routing pin.  See
// targets/game/reverse/identity_evidence/0058c2b0-eh-structure.md and
// targets/game/reverse/identity_evidence/0058c2b0-caller-abi-paradox.md.
//
// The destructor of the returned class MUST be user-declared and must NOT be
// throw().  VC7.1 treats an implicit destructor as throw() and registers no
// unwind action for it at all: with a bare `void release();` member the body
// has only two funclets and no `or ebx,2`.
//
// Frame (proved from the unwind map; EBP = entry ESP X):
//   X-0x18  EH flags word: bit0 = string temp alive, bit1 = return object alive
//   X-0x14  BFMERetailAsciiString object
//   X-0x10  raw operator new result
//   X-0x0c  saved fs:[0] chain, X-0x08 handler, X-0x04 EH state variable
//   X+0x04  the sret pointer,  X+0x08 the "PingAttack" string
//
// Retail order: operator new(0x18) -> BFMERetailAsciiString(what) ->
// Owner((int)&arg) -> returnObject.m_ptr = p (store first, then AddRef) ->
// string destructor -> return the object address.  The string object lives
// until the end of the whole full expression, which is why it is written as a
// temporary inside the new-expression and not as a local.
//
// WHY THE ARGUMENT IS A MEMBER ADDRESS (the last 4 bytes, the residue four
// earlier verdicts could not remove): retail materialises the Owner
// constructor's argument with `lea ecx,[X-0x14]` / `push ecx` and only then
// writes the string flag `mov ebx,1`.  VC7.1 folds `&class-prvalue` to the
// constructor's own `this` return in EAX, which emits `push eax` and moves the
// flag store ahead of the push (166 bytes, four short).  Taking the address of
// a MEMBER of the temporary is a different expression tree: the member address
// is an indirection on the object, so C1 re-materialises the frame address
// instead of reusing the constructor's return value.  `ArgBox` holds nothing
// else, so `&arg.m_s` is the object's own address and the dtor tail-call is the
// `releaseBuffer` at [X-0x14] retail has.  170 bytes, exact.

void *operator new(unsigned int n);

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
private:
	void releaseBuffer();
	char *m_data;
};

// The one-word argument object: its only member is the string, so the Owner
// constructor receives the object's address and its destructor is the string
// destructor retail calls.
class ArgBox
{
public:
	ArgBox(const char *text) : m_s(text) {}
	~ArgBox() {}
	BFMERetailAsciiString m_s;
};

class Rva0058BF70Base
{
public:
	Rva0058BF70Base() : m_value(0) {}
	virtual ~Rva0058BF70Base() {}
	virtual void slot1();
	int m_value;
};

class Rva0058BF70Owner : public Rva0058BF70Base
{
public:
	Rva0058BF70Owner(int value);
	virtual ~Rva0058BF70Owner();
private:
	char m_pad[16];
};

// The returned smart pointer: one pointer, so MSVC passes a hidden return
// pointer in the first stack slot.  The user-declared destructor is what makes
// VC7.1 register the state-0 unwind action above; it tail-calls release().
// m_value is the shared reference count at [object+4] (the matched
// Rva0058BF70Owner constructor stores 0 there and the release body at
// 0x00107550 decrements it and calls vtable slot 0 with 1 at zero).
class Rva0058C2B0RefPtr
{
public:
	Rva0058C2B0RefPtr(Rva0058BF70Base *p) { m_ptr = p; if (p) ++p->m_value; }
	void release();
	~Rva0058C2B0RefPtr() { release(); }
private:
	Rva0058BF70Base *m_ptr;
};

Rva0058C2B0RefPtr __stdcall bfmeCallDUL(const char *what)
{
	return Rva0058C2B0RefPtr(new Rva0058BF70Owner((int)&ArgBox(what).m_s));
}
