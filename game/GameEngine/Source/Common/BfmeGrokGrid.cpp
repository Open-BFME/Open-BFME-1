// cl: /O2

extern void j_00023b14(void);

class BfmeGridWM
{
public:
	void walk();

private:
	int m_pad0;
	int m_pad1;
	int m_w;
	int m_h;
};

void BfmeGridWM::walk()
{
	for (int x = 0; x < m_w - 1; ++x)
		for (int y = 0; y < m_h - 1; ++y)
		{
			typedef void (BfmeGridWM::*BfmeGridWMCellCall)(int, int);
			union
			{
				void (*function)(void);
				BfmeGridWMCellCall method;
			} cell = { j_00023b14 };
			(this->*cell.method)(x, y);
		}
}
