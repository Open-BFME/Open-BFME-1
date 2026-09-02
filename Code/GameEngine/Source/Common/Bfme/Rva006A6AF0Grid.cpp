// cl: /O2 /Ob1

struct BfmeCellAF0
{
	void bfmeFill(void);
	char m_bfmeBytes[0x28];
};

class Gen_006A6AF0
{
public:
	void bfmeGo(int a, int b, int c);
	void bfmePrep(int a, int c);

private:
	char m_bfmePad[0x9D4];
	BfmeCellAF0 m_bfmeCells[6];
	int m_bfmeMap[1];
};

void Gen_006A6AF0::bfmeGo(int a, int b, int c)
{
	if (m_bfmeMap[a] == b)
		bfmePrep(a, c);

	m_bfmeCells[b + 2 * a].bfmeFill();
}
