// cl: /DNDEBUG /MD /EHsc

// DistLODClass's copy constructor, retail 0x005EC3A0.
//
// Everything it does is forward to the base and then re-stamp the vftables: one
// call, then +0x00, +0x14, +0x18 and +0x1C. Four pointers means the base itself
// is multiply derived - a primary at +0x00 with its data, and three interfaces
// at +0x14, +0x18 and +0x1C - and the leaf overwrites all four, the one-round
// shape.
//
// The vendored header has DistLODClass : public CompositeRenderObjClass, so the
// callee is that class's copy constructor; it is pinned on the thunk this call
// encodes rather than on the body, because that is what the call site names.

class CompositeRenderObjClassPrimary
{
public:
	virtual void renderObjAnchor();

private:
	unsigned char m_unmodelled_04[ 0x14 - 4 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	virtual void multiListObjectAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad/persist.h
class PersistClass
{
public:
	virtual void persistAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void refCountAnchor();
};

class CompositeRenderObjClass : public CompositeRenderObjClassPrimary,
	public MultiListObjectClass,
	public PersistClass,
	public RefCountClass
{
public:
	CompositeRenderObjClass( const CompositeRenderObjClass &that );
};

class BFMEDistLODClass : public CompositeRenderObjClass
{
public:
	BFMEDistLODClass( const BFMEDistLODClass &that );
};

// ??0DistLODClass@@QAE@ABV0@@Z
BFMEDistLODClass::BFMEDistLODClass( const BFMEDistLODClass &that )
	: CompositeRenderObjClass( that )
{
}
