// ?ready@Rva007E3160@@QAEHXZ
// partial score=0.85 date=2026-09-02
// cl: /O2
// 0x007E3160: true when the +4 pointer is live and the +8 tag is 6 or 7.

class Rva007E3160
{
public:
	virtual void v0();
	int ready();

private:
	void *m_04;
	int m_08;
};

int Rva007E3160::ready()
{
	if (!m_04)
		return 0;
	if (m_08 != 6 && m_08 != 7)
		return 0;
	return 1;
}
