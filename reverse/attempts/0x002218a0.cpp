// ?Rva002218A0@Rva002218A0Subobject@@QBEDPBVRva002218A0Argument@@@Z
// partial score=0.93 date=2026-09-12
// Address-derived reconstruction of retail RVA 0x002218A0.
// The layout names below are offset-derived because no semantic method name
// or inherited subobject owner is proven by the secondary-vtable evidence.
// The secondary vtable at 0x010AB140 slot 0xA8 reaches this body through
// ILT 0x000087EC. ContestableContain constructors install that table, but
// the inherited subobject and original method name are not proven.
extern const float BfmeZeroRange;

class Rva002218A0Argument
{
public:
	unsigned char m_rva002218A0Head08[8];
	float m_rva002218A0Field08;
	unsigned char m_rva002218A0Pad0[0xc];
	float m_rva002218A0Field18;
	unsigned char m_rva002218A0Pad1[0xc];
	float m_rva002218A0Field28;
	unsigned char m_rva002218A0Pad2[0xc];
	float m_rva002218A0Field38;
	float m_rva002218A0Field3c;
	float m_rva002218A0Field40;
};

class Rva002218A0Info
{
public:
	unsigned char m_rva002218A0Head[0x138];
	float m_rva002218A0Field138;
};

class Rva002218A0Other
{
public:
	unsigned char m_rva002218A0Head[0x38];
	float m_rva002218A0Field38;
	float m_rva002218A0Field3c;
	float m_rva002218A0Field40;
};

class Rva002218A0OwnerLinks
{
public:
	Rva002218A0Info *m_rva002218A0Link0;
	Rva002218A0Other *m_rva002218A0Link4;
};

class Rva002218A0Subobject
{
public:
	char Rva002218A0(const Rva002218A0Argument *m) const;
};

// ?Rva002218A0@Rva002218A0Subobject@@QBEDPBVRva002218A0Argument@@@Z
char Rva002218A0Subobject::Rva002218A0(const Rva002218A0Argument *m) const
{
	const Rva002218A0Argument *p = m;
	volatile float v[3];

	if (p == 0)
		return 0;

	const Rva002218A0OwnerLinks *base =
		(const Rva002218A0OwnerLinks *)((const char *)this - 0x1c);
	Rva002218A0Info *info = base->m_rva002218A0Link0;

	if (info->m_rva002218A0Field138 < BfmeZeroRange)
		return 0;

	Rva002218A0Other *o = base->m_rva002218A0Link4;

	if (p->m_rva002218A0Field40 - o->m_rva002218A0Field40 >
		info->m_rva002218A0Field138)
		return 0;

	float a = p->m_rva002218A0Field08;
	float b = p->m_rva002218A0Field18;
	float c = p->m_rva002218A0Field28;
	float d = o->m_rva002218A0Field3c - p->m_rva002218A0Field3c;
	v[0] = o->m_rva002218A0Field38 - p->m_rva002218A0Field38;

	if (a * v[0] + b * d + c * BfmeZeroRange < BfmeZeroRange)
		return 0;

	return 1;
}
