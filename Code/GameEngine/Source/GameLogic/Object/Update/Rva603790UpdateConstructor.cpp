// cl: /DNDEBUG /MD /EHsc

// The client-update-module constructor at retail 0x00603790, 95 bytes.
//
// IDENTITY, and why the row does not assert it. The incremental-link thunk at
// 0x00006780 is `jmp 0x00603790` and reverse/symbols.csv pins that thunk as
// ??0LaserUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, so this is LaserUpdate's
// constructor. The ledger already spends that mangled name on a DIFFERENT
// 5-byte thunk, 0x00035D91, whose jump lands on 0x002B1060 -- an SEH-framed
// constructor that writes four vftables (0x0109C9D0, 0x0109CBA0, 0x010A1DE4,
// 0x010C5124) and cannot be the same body. One of the two claims is wrong and
// the ledger allows a name only one address, so this row takes an
// address-derived placeholder rather than contest the older one. Promoting it
// to the real name is a one-line repoint once 0x00035D91 is re-identified.
//
// SHAPE. The base is ClientUpdateModule(Thing *, const ModuleData *), already
// pinned at the 0x00002874 thunk. Its subobject ends at +0x0C; everything from
// +0x0C to +0x50 is this class's own, all zeroed except 1.0f at +0x3C.
//
// WHY THIS ROW KEEPS THE CONTRIVED SPELLING WHEN ITS SIBLINGS NO LONGER DO.
// Taint (0x0026B870), CloudBreak (0x002592A0) and Keyboard (0x005A3AC0) were
// landed with the same __declspec(novtable) plus hand-written vftable plus
// volatile-lvalue construct and have since been rewritten as ordinary C++,
// because MSVC 7.1's real rule is that it SINKS a constructor's vptr store
// forward until a barrier stops it, and a member sub-object's construction is
// such a barrier -- emitted after the vptr store and before the constructor
// body. This body is the one of the four that cannot be reached that way, and
// the reason is a layout contradiction, not a missing spelling.
//
// Retail writes the byte at +0x24 BEFORE the vftable pointer and the dword at
// +0x18 immediately AFTER it. Only two things put a store ahead of the vptr
// store: a base-class constructor (bases are constructed first) or a store the
// compiler cannot prove stays inside the object. Only those same two things,
// plus a member sub-object's construction, stop the sink. A base holding +0x24
// must extend to at least +0x28, which forces every member sub-object to +0x28
// or beyond -- so the barrier can never be the +0x18 store. Probed directly:
// an intermediate base setting +0x24 with a sub-object at +0x28 emits
// `88 46 24 / c7 06 vtbl / 89 46 28 / 89 46 18`, the barrier's own field
// wedged between the vftable and +0x18. And +0x18 cannot be made a barrier by
// itself: declaring it volatile, or writing it through a volatile lvalue,
// leaves the vptr store sinking to the head of the immediate-store group,
// because volatile orders only the volatile accesses among themselves and the
// compiler's own vptr store is not one of them. That last point is why
// novtable is load-bearing here rather than decorative -- it removes the
// compiler's vptr store from the problem so a hand-written one can hold a
// position. The hand-written store must be volatile ALONG WITH the members:
// probed plain, and probed volatile with plain members, it sinks to the head
// of the immediate group in both cases. Retail also puts +0x31 between +0x38
// and +0x40, which the written order reproduces for free.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ClientUpdateModule.h
class ClientUpdateModule
{
public:
	ClientUpdateModule( Thing *thing, const ModuleData *moduleData );

	virtual void clientUpdateModuleAnchor();

private:
	unsigned char m_unmodelled_04[ 0x0C - 4 ];
};

extern "C" char Rva603790_vtbl;

class __declspec(novtable) Rva603790Ctor : public ClientUpdateModule
{
public:
	Rva603790Ctor( Thing *thing, const ModuleData *moduleData );

private:
	unsigned int m_unmodelled_0C;
	unsigned int m_unmodelled_10;
	unsigned int m_unmodelled_14;
	unsigned int m_unmodelled_18;
	unsigned int m_unmodelled_1C;
	unsigned int m_unmodelled_20;
	unsigned char m_unmodelled_24;
	unsigned char m_pad_25[ 3 ];
	unsigned int m_unmodelled_28;
	unsigned int m_unmodelled_2C;
	unsigned char m_unmodelled_30;
	unsigned char m_unmodelled_31;
	unsigned char m_pad_32[ 2 ];
	unsigned int m_unmodelled_34;
	unsigned int m_unmodelled_38;
	float m_unmodelled_3C;
	unsigned int m_unmodelled_40;
	unsigned int m_unmodelled_44;
	unsigned int m_unmodelled_48;
	unsigned int m_unmodelled_4C;
	unsigned int m_unmodelled_50;
};

// ??0Rva603790Ctor@@QAE@PAVThing@@PBVModuleData@@@Z
Rva603790Ctor::Rva603790Ctor( Thing *thing, const ModuleData *moduleData )
	: ClientUpdateModule( thing, moduleData )
{
	*reinterpret_cast<unsigned char volatile *>(&m_unmodelled_24) = 0;
	*reinterpret_cast<char *volatile *>(this) = &Rva603790_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_18) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_1C) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_20) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_0C) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_10) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_14) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_28) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_2C) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_unmodelled_30) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_34) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_38) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_unmodelled_31) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_40) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_44) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_48) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_4C) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_50) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_unmodelled_3C) = 0x3F800000u;	// 1.0f
}
