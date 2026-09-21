// ?Rva000BE410@@YGXPAX@Z (identity unknown)
// partial score=0.91 date=2026-09-06
// 31/34 at exact size. The recipe that gets the frame and the esp marker
// right (and landed 0x00522DD0 exactly) is: a class with a real default
// constructor, an INLINE copy constructor, and a destructor DECLARED BUT NOT
// DEFINED. That combination is what makes MSVC construct the temporary
// directly in the outgoing argument area instead of building a local and
// rep-movs-ing it, and what makes it emit `mov [esp+N],esp`.
//   - ctor + inline dtor       -> no marker, push esi, three separate zero regs
//   - ctor + out-of-line dtor with no inline copy ctor -> full SEH frame, 105B
//   - POD + value-init         -> 30B, no frame slot
// The only residue here is the zero register: retail `xor edx,edx`, MSVC
// `xor ecx,ecx` (3 modrm bytes). Tried throw()/non-throw ctor, member-init
// list, a zero local, reversed store order, void* members, a one-argument
// ctor, a three-argument ctor, and making the caller a thiscall member.
// That is the known zero-register-propagation class.
class Rva000BE410Value
{
public:
	Rva000BE410Value() { m_x = 0; m_y = 0; m_z = 0; }
	Rva000BE410Value(const Rva000BE410Value &other) throw()
	{
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;
	}
	~Rva000BE410Value();

	int m_x;
	int m_y;
	int m_z;
};

// tools/callees.py resolves the retail REL32 to this address-derived ILT
// thunk.  Its body jumps to the still-anonymous 0x000BE300 body.  Keep the
// ledger spelling and cast only the ABI; do not invent a semantic pin.
extern void j_0004835b();
typedef void (__stdcall *Rva0004835BCall)(void *, Rva000BE410Value);

void __stdcall Rva000BE410(void *owner)
{
	union
	{
		void (*raw)();
		Rva0004835BCall typed;
	} call;
	call.raw = ::j_0004835b;
	call.typed(owner, Rva000BE410Value());
}
