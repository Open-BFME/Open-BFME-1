// cl: /O2 /Ob0

struct Rva001F7270Inner
{
	char m_lead[0x44];
	float m_44;
};

class Rva001F7270
{
public:
	float get() const;
};

float Rva001F7270::get() const
{
	Rva001F7270Inner *p = *(Rva001F7270Inner **)((const char *)this - 0x48);
	if (!p)
		return 0.0f;
	return p->m_44;
}
