// cl: /DNDEBUG /MD /EHsc
// Retail 0x0014C9E0, 94 bytes. The status, checker, kind, and relationship
// tests match the retail body. The address-derived owner name records the
// missing source declaration for this filter.

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
	{
		return false;
	}
	else
	{
		if (status & 8)
			return false;

		BfmeCheckerNW *checker = obj->m_checkerNW;
		if (checker != 0 && checker->bfmeBusyNW())
			return false;

		if (((Thing *)obj)->isKindOf((KindOfType)0x35))
			return false;
		if (((Thing *)obj)->isKindOf((KindOfType)0x6c))
			return false;

		return static_cast<unsigned char>(
			m_owner->getRelationship((const Object *)obj) == 0);
	}
}
