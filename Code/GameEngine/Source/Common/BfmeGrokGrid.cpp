// cl: /O2

class BfmeGridWM
{
public:
	void walk();
	void cell(int x, int y);

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
			cell(x, y);
}
