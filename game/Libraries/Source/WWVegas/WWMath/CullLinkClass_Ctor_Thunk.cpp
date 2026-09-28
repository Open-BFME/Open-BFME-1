// cl: /DNDEBUG /MD /EHsc
// Out-of-line CullLinkClass-shaped constructor at retail 0x008DCC70 (18 B).
// vtable_lookup proves the installed vtable (0x01137808) is CullLinkClass's:
// slot 0 is ??_GCullLinkClass@@UAEPAXI@Z (landed in
// CullLinkClass_Dtor_Thunk.cpp) and the GridLinkClass table sits directly
// above it. cullsys.h covers the inline form, so this TU carries the
// out-of-line copy under an address-derived name; the destructor stays
// inline so the TU defines only the constructor. No guessed semantic name.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/cullsys.h
class CullSystemClass
{
};

class Rva008DCC70Link
{
public:
	Rva008DCC70Link(CullSystemClass *system);
	virtual ~Rva008DCC70Link(void) { }

protected:
	CullSystemClass *System;
};

// ??0Rva008DCC70Link@@QAE@PAVCullSystemClass@@@Z
Rva008DCC70Link::Rva008DCC70Link(CullSystemClass *system) :
	System(system)
{
}
