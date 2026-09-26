// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: two compiler-generated bodies out of d_0005b6c0.asm.
//
// 0x0006B450 is a scalar deleting destructor and nothing else: `test [esp+4],1`
// on the hidden flags argument, the inlined destructor body (which for this
// class is only the vftable store at 0x01075BC0), operator delete on the set
// bit, and `this` returned. No source statement produces that test -- it is the
// ??_G thunk MSVC emits for a class with a virtual destructor -- so the source
// here is just the class with `virtual ~T();` defined out of line, and the
// thunk falls out.
//
// The destructor that emission also produces is the seven-byte body at
// 0x0006B430 (`mov dword ptr [ecx],0x01075BC0 / ret`), which the ledger already
// claims as ?m@Gen_0006b430@@QAEXXZ in game/gen_small/fun_000.cpp -- a gen-shim
// row, not a scaffold, so it cannot be taken over from here. It is annotated
// below rather than claimed twice.
//
// 0x0007B850 is the copy constructor of a class derived from the CRT's
// std::exception: the base copy is `ff 15 [__imp_??0exception@@QAE@ABV0@@Z]`
// with ecx holding this, and the derived vftable at 0x010766DC goes down after
// it, which is the fixed base-then-own-vptr order. The real vendored <exception>
// is used deliberately -- the dllimport spelling is what makes the base call six
// bytes indirect instead of a five-byte REL32.

#include <exception>

// ??1Rva0006B450Node@@UAE@XZ present-unmatched
//   (retail 0x0006B430; already claimed as ?m@Gen_0006b430@@QAEXXZ)
class Rva0006B450Node
{
public:
	Rva0006B450Node(void);
	virtual ~Rva0006B450Node();
};

// ??_GRva0006B450Node@@UAEPAXI@Z
Rva0006B450Node::~Rva0006B450Node()
{
}

// ---------------------------------------------------------------------------

// ??_GRva0007B850Exception@@UAEPAXI@Z present-unmatched
class Rva0007B850Exception : public std::exception
{
public:
	Rva0007B850Exception(const Rva0007B850Exception &other);
};

// ??0Rva0007B850Exception@@QAE@ABV0@@Z
Rva0007B850Exception::Rva0007B850Exception(const Rva0007B850Exception &other)
	: std::exception(other)
{
}
