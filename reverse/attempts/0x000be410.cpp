// ?bfmeMakeZA@@YGXPAX@Z (identity unknown)
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
class BfmeVecZA
{
public:
	BfmeVecZA() { m_bfmeXZA = 0; m_bfmeYZA = 0; m_bfmeZZA = 0; }
	BfmeVecZA(const BfmeVecZA &other) throw()
	{
		m_bfmeXZA = other.m_bfmeXZA;
		m_bfmeYZA = other.m_bfmeYZA;
		m_bfmeZZA = other.m_bfmeZZA;
	}
	~BfmeVecZA();

	int m_bfmeXZA;
	int m_bfmeYZA;
	int m_bfmeZZA;
};

void __stdcall bfmeSendZA(void *owner, BfmeVecZA value);	// pin at thunk 0x0004835B

void __stdcall bfmeMakeZA(void *owner)
{
	bfmeSendZA(owner, BfmeVecZA());
}
