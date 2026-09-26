// ?d_00918e80@@YAXXZ
// partial score=0.88 date=2026-09-26
// cl: /O2 /Ob0

class Rva00918E80
{
	unsigned char m_prefix[0x11c];
	void *m_first;
	unsigned char m_between[0x4c];
	void *m_second;

public:
	void setBoth(void *value);
};

void Rva00918E80::setBoth(void *value)
{
	m_first = value;
	m_second = value;
}
