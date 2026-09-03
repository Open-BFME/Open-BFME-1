// cl: /DNDEBUG /MD
// Constructor that writes 1.0f into six rows of thirty-two floats. Retail
// keeps this in eax (constructor return), the biased pointer in edx, the
// countdown in edi and the 0x3F800000 bits in esi.

class Rva00083150
{
public:
	Rva00083150();

private:
	unsigned int m_grid[6][32];
};

Rva00083150::Rva00083150()
{
	unsigned int one = 0x3F800000u;
	for (int i = 0; i < 32; ++i)
	{
		m_grid[0][i] = one;
		m_grid[1][i] = one;
		m_grid[2][i] = one;
		m_grid[3][i] = one;
		m_grid[4][i] = one;
		m_grid[5][i] = one;
	}
}
