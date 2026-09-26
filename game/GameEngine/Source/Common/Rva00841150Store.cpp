// cl: /O2 /Ob0

class HoldRva00841150
{
public:
	char m_lead[4];
	int m_off;
};

class Rva00841150
{
public:
	void apply();
};

void Rva00841150::apply()
{
	HoldRva00841150 *hold = *(HoldRva00841150 **)((char *)this - 4);
	*(unsigned *)((char *)this - 4 + hold->m_off) = 0x0112F30Cu;
}
