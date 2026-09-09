// ?allow@Rva0014C9E0@@QBE_NPAVRva0014C9E0Node@@@Z
// partial score=0.45 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
//
// thiscall @ 0x0014C9E0, 94 bytes. Filter-like predicate: rejects the
// argument object if its +0x344 status byte has bit 0 or bit 3 set, if
// a BfmeCheckerNW at +0x208 (when present) reports busy, if either
// isKindOf(0x35) or isKindOf(0x6c) hold, or if this+0x8's relationship to
// the object is nonzero. Owning class unidentified; callees resolve through
// already-pinned thunks (isKindOf@Thing, getRelationship@Object,
// bfmeBusyNW@BfmeCheckerNW).

enum KindOfType
{
	KindOfType_Thunk
};

class Thing
{
public:
	bool isKindOf(KindOfType) const;
};

enum Relationship
{
	Relationship_Thunk
};

class Object
{
public:
	Relationship getRelationship(const Object *) const;
};

class BfmeCheckerNW
{
public:
	char bfmeBusyNW();
};

class Rva0014C9E0Node
{
public:
	char m_pad00[0x208];
	BfmeCheckerNW *m_checkerNW;
	char m_pad20C[0x344 - 0x20C];
	unsigned char m_status;
};

class Rva0014C9E0
{
public:
	bool allow(Rva0014C9E0Node *obj) const;

private:
	char m_pad00[8];
	Object *m_owner;
};

bool Rva0014C9E0::allow(Rva0014C9E0Node *obj) const
{
	unsigned char status = obj->m_status;
	if (status & 1)
		return false;
	if (status & 8)
		return false;

	BfmeCheckerNW *checker = obj->m_checkerNW;
	if (checker != 0 && checker->bfmeBusyNW())
		return false;

	if (((Thing *)obj)->isKindOf((KindOfType)0x35))
		return false;
	if (((Thing *)obj)->isKindOf((KindOfType)0x6c))
		return false;

	return m_owner->getRelationship((const Object *)obj) == 0;
}
