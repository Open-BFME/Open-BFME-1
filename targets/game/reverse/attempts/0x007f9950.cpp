// ?rva007F9950Copy@Rva007F9950Struct@@QAEXPBV1@@Z
// partial score=0.85 date=2026-09-06
// ?rva007F9950Copy@Rva007F9950Struct@@QAEXPBV1@@Z
// Address-derived: field-wise copy of an 11-int-plus-byte struct from
// *other into *this, leaving offset 0 untouched (a preserved vtable or id
// field).
class Rva007F9950Struct
{
public:
	int m_0;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	unsigned char m_30;

	void rva007F9950Copy(const Rva007F9950Struct *other);
};

void Rva007F9950Struct::rva007F9950Copy(const Rva007F9950Struct *other)
{
	Rva007F9950Struct *self = this;
	self->m_4 = other->m_4;
	m_8 = other->m_8;
	m_c = other->m_c;
	m_10 = other->m_10;
	m_14 = other->m_14;
	m_18 = other->m_18;
	m_1c = other->m_1c;
	m_20 = other->m_20;
	m_24 = other->m_24;
	m_28 = other->m_28;
	m_2c = other->m_2c;
	m_30 = other->m_30;
}
