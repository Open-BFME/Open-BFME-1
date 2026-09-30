// Retail 0x009A2F40:30B and 0x009A2F60:12B; separate entries with INT3 padding.
// The former generated 44B extent fused these two bodies and two padding bytes.
class Rva009A2F40
{
public:
 unsigned int m_00, m_04;
 int m_a, m_b; // Existing banked names; retail offsets +0x08 and +0x0C.
 unsigned char method(const Rva009A2F40 *other);
 unsigned int method_009A2F60() const;
};
unsigned char Rva009A2F40::method(const Rva009A2F40 *other)
{
 if (m_a == other->m_a && m_b == other->m_b) return 1;
 return 0;
}
unsigned int Rva009A2F40::method_009A2F60() const
{
 return ((unsigned int)m_a << 16) + (unsigned int)m_b;
}

// Retail 0x009A2F70:30B and 0x009A2F90:12B; separate entries with INT3 padding.
// The former generated 44B extent fused these two bodies and two padding bytes.
class Rva009A2F70
{
public:
 unsigned int m_00, m_04;
 int m_a, m_b; // Existing banked names; retail offsets +0x08 and +0x0C.
 unsigned char method(const Rva009A2F70 *other);
 unsigned int method_009A2F90() const;
};
unsigned char Rva009A2F70::method(const Rva009A2F70 *other)
{
 if (m_a == other->m_a && m_b == other->m_b) return 1;
 return 0;
}
unsigned int Rva009A2F70::method_009A2F90() const
{
 return ((unsigned int)m_a << 16) + (unsigned int)m_b;
}
