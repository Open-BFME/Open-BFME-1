// 17 seven-byte __thiscall members with one shape:
//
//     mov dword ptr [ecx],<offset vftable> / ret
//
// WHAT THE BYTES SHOW.  A vftable address is written over `this` and nothing
// else happens.  That is a DESTRUCTOR of a polymorphic class with an empty
// body, not a constructor: MSVC 7.1 returns `this` in eax from every
// constructor, so a constructor of this class would open `mov eax,ecx` and be
// nine bytes.  A destructor returns nothing, and re-seating the vptr to its own
// class before running the body is exactly what MSVC emits for one.  Each
// immediate resolves into .rdata, which is where vftables live.
//
// The destructor is spelled virtual because the class is polymorphic and
// nothing here distinguishes a virtual destructor from a non-virtual one --
// both emit these seven bytes -- while `virtual` is the shape that makes the
// vftable this body writes worth having.  The vftable slot itself is filled by
// the patcher from the target binary and the build checks that every reference
// to a given symbol resolves to one address, so the address is retail's.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_TRIVIAL_VIRTUAL_DTOR( NAME )                                     \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

BFME_TRIVIAL_VIRTUAL_DTOR( Rva000FBE10Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva001DDC90Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva00202E70Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva0020DE10Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva00410A60Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva005D47A0Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva005D4800Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva005D4810Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva005D4820Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva005D4F30Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva005D4F40Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva005EE330Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva005EE360Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva00618600Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva006235A0Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva0066B030Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva006709E0Poly )

// The carved retail boundary at 0x005D47E0 contains only ret.
void Rva005D47E0Noop(void)
{
}
