// cl: /O2 /Ob0

class Rva0040B2E0Global
{
public:
	char m_lead[0xDC8];
	float m_value;
};

class Rva0040B2E0
{
	char m_lead[0x14];
	float m_scale;

public:
	float scale() const;
};

Rva0040B2E0Global *g_rva0040b2e0;

float Rva0040B2E0::scale() const
{
	return g_rva0040b2e0->m_value * m_scale;
}
