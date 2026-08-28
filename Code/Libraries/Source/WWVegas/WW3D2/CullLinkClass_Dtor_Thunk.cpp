// cl: /DNDEBUG /MD /EHsc

// The scalar deleting destructor of the cull-link base.
//
// vtable_gaps offered this as slot 10 of a twelve-slot run whose other names are
// all GridCullSystemClass. It is not: the body stores 0x01137808 into its own
// object, and 0x01137808 is the address of slot 10 itself. A body that installs
// a vptr pointing at its own slot is slot 0 of a new table, so the run holds
// three vtables and the GridCullSystemClass names next door say nothing about
// this one.
//
// What does say something is the one slot below. 0x0113780C is installed by
// ??0GridLinkClass@@QAE@PAVGridCullSystemClass@@@Z, so that table is
// GridLinkClass, and its destructor delegates to the destructor that installs
// 0x01137808 -- this class is GridLinkClass's base. cullsys.h has exactly one
// candidate: GridLinkClass derives from CullLinkClass, whose only virtual is its
// destructor, which is why each of these tables holds a single slot.
//
// The destructor body is empty; everything before the delete is the vptr store
// the compiler inserts, which is why it inlined into the deleting stub.
class CullSystemClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/cullsys.h
class CullLinkClass
{
public:
	CullLinkClass(CullSystemClass *system);
	virtual ~CullLinkClass(void);

	CullSystemClass *System;
};

// ??_GCullLinkClass@@UAEPAXI@Z
CullLinkClass::~CullLinkClass(void)
{
}
