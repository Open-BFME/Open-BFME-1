// cl: /DNDEBUG /MD /EHsc
// Open-BFME1: AABTreeLinkClass::AABTreeLinkClass(AABTreeCullSystemClass*), ported from
// Zero Hour's WWVegas/WWMath/aabtreecull.cpp. Retail zeroes a third pointer-sized field
// beyond {Node, NextObject} that the vendored Zero Hour class does not declare -- this
// build's AABTreeLinkClass carries one extra zero-initialized link member. Kept as an
// isolated translation unit (mirroring the other *_Thunk.cpp files in this directory) so
// the extra member doesn't touch the shared aabtreecull.h used by already-matched rows.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/cullsys.h
class CullSystemClass
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/cullsys.h
class CullLinkClass
{
public:
	CullLinkClass(CullSystemClass * system) { System = system; }
	virtual ~CullLinkClass(void) { }

protected:
	CullSystemClass * System;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/aabtreecull.h
class AABTreeCullSystemClass : public CullSystemClass
{
};

class AABTreeNodeClass;
class CullableClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/aabtreecull.h
class AABTreeLinkClass : public CullLinkClass
{
public:
	AABTreeLinkClass(AABTreeCullSystemClass * system);

	AABTreeNodeClass * Node;
	CullableClass * NextObject;
	CullableClass * PrevObject;
};

// ??0AABTreeLinkClass@@QAE@PAVAABTreeCullSystemClass@@@Z
AABTreeLinkClass::AABTreeLinkClass(AABTreeCullSystemClass * system) :
	CullLinkClass(system),
	Node(0),
	NextObject(0),
	PrevObject(0)
{
}
