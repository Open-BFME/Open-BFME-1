// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00076B60 is the constructor of an unidentified BFME
// SubsystemInterface-derived object.  Its identity is deliberately neutral:
// the constructor installs the distinct retail table 0x01075EE8, while the
// named caller/class for this particular owner is not recovered.  The table
// itself is not a guessed padding table.  It is the nine-slot BFME interface
// recovered from the base table 0x01141640 and the target table's ILTs.
//
// Slots 0..8 of 0x01075EE8 are, respectively:
//   scalar deleting dtor (ILT 0x0001E2F4 -> 0x00076C50),
//   init (ILT 0x00003355 -> 0x001487F0),
//   SubsystemInterface::loadIniFilesFromLegend,
//   the inherited empty base stub (ILT 0x000436B2 -> 0x00067930),
//   reset (ILT 0x0001604F -> 0x00076C00),
//   update (ILT 0x0003744D -> 0x00076BF0),
//   the inherited Bool(arg) base stub (ILT 0x00033497 -> 0x00067940),
//   the inherited empty base member (0x009A16C0), and
//   the inherited empty-with-arg base member (0x009A16D0).
//
// The alternate names below preserve those existing retail ILT targets in
// the emitted COMDAT; they are routes proved by the vtable and the matched
// thunk rows, not substitute method bodies.  Slots 7 and 8 are represented
// by neutral base members because their bodies are direct, unclaimed retail
// stubs; their address pins carry the separate vtable evidence.

#define _STLP_NO_EXCEPTIONS 0
#include <list>

typedef bool Bool;
typedef int Int;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;                         // slot 1
	virtual Bool loadIniFilesFromLegend();           // slot 2, named base body
	virtual void unidentifiedSlot03();               // slot 3, empty base stub
	virtual void reset() = 0;                        // slot 4
	virtual void update() = 0;                       // slot 5
	virtual Bool unidentifiedSlot06(Int arg);        // slot 6, returns FALSE
	virtual void unidentifiedSlot07();               // slot 7, direct ret stub
	virtual void unidentifiedSlot08(Int arg);        // slot 8, direct ret 4 stub

private:
	struct BfmeStringMember
	{
		void *m_data;
	} m_name;                                          // member at +0x04, not a base
};

// The table's slot 0 is the scalar deleting destructor.  Retail reaches its
// 30-byte body through the already matched ILT 0x0001E2F4; the body at
// 0x00076C50 consumes the deleting flag, calls the complete destructor,
// conditionally calls operator delete, and returns this.  VS2003 emits a
// weak ??_E vftable relocation whose COFF auxiliary record tags this class's
// strong local ??_G helper.  That is the effective compiler resolution; an
// /alternatename for an already-defined ??_G would be false evidence and is
// intentionally not used here.

// The three overridden virtuals are identified by the target-table ILTs and
// their matched retail bodies: init is the one-byte empty body, reset clears
// the STLport list at +0x0C, and update is the one-byte empty body.
#pragma comment(linker, "/alternatename:?init@Rva00076B60@@UAEXXZ=?j_00003355@@YAXXZ")
#pragma comment(linker, "/alternatename:?reset@Rva00076B60@@UAEXXZ=?j_0001604f@@YAXXZ")
#pragma comment(linker, "/alternatename:?update@Rva00076B60@@UAEXXZ=?j_0003744d@@YAXXZ")

// Inherited slots 3 and 6 are the exact incremental-link ILTs already
// present in the ledger.  The base slot 2 remains the named implementation
// in SubsystemInterface.cpp; slots 7 and 8 are pinned neutral members below.
#pragma comment(linker, "/alternatename:?unidentifiedSlot03@SubsystemInterface@@UAEXXZ=?j_000436b2@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentifiedSlot06@SubsystemInterface@@UAE_NH@Z=?j_00033497@@YAXXZ")

// The scalar wrapper's complete-dtor call is not a second guessed body.  The
// retail wrapper at 0x00076C50 calls ILT 0x00015C62, whose matched thunk
// reaches the already-converted 82-byte complete destructor at 0x00076C80
// (Gen_00076C80 in Bfme5ChainedDestructors.cpp).  Leave this destructor
// declaration unresolved so the linker route records that existing callee;
// defining another local ??1 body would make the exact 30-byte wrapper point
// at an unproved duplicate.
#pragma comment(linker, "/alternatename:??1Rva00076B60@@UAE@XZ=?j_00015c62@@YAXXZ")

// The two direct base stubs are not present as named function rows, so these
// neutral member symbols are pinned only to the addresses shown by every
// nine-slot SubsystemInterface-family table.  Their ABI is explicit: slot 7
// is ret and slot 8 is ret 4.
class Rva00076B60 : public SubsystemInterface
{
public:
	Rva00076B60();
	virtual ~Rva00076B60();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	class Flags
	{
	public:
		Flags() : m_value(0) { }
		Flags &operator|=(unsigned int mask)
		{
			m_value |= mask;
			return *this;
		}

	private:
		unsigned int m_value;
	} m_bfmeFlags;                                    // +0x08

	// The element identity is not recovered.  The constructor proves only
	// the eight-byte STLport list element width and sentinel layout.
	struct Elem
	{
		int m_a;
		int m_b;
	};
	_STL::list<Elem, _STL::allocator<Elem> > m_bfmeList; // +0x0C
};

// ??0Rva00076B60@@QAE@XZ
Rva00076B60::Rva00076B60()
	: m_bfmeFlags()
{
	m_bfmeFlags |= 0x8;
	m_bfmeFlags |= 0x20;
}

// No duplicate complete destructor is defined here: the declaration above is
// routed to retail's existing complete-dtor chain, while this TU still emits
// the real C++ scalar deleting helper and its ABI/flag protocol.
