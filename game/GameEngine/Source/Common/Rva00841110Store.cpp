// cl: /O2 /Ob0

class HoldRva00841110
{
public:
	char m_lead[4];
	int m_off;
};

class Rva00841110
{
public:
	void apply();
};

void Rva00841110::apply()
{
	HoldRva00841110 *hold = *(HoldRva00841110 **)((char *)this - 8);
	*(unsigned *)((char *)this - 8 + hold->m_off) = 0x0112F2FCu;
}
