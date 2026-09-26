// cl: /DNDEBUG /MD /EHsc

typedef void (*Rva00906340CellFn)(void *);

void __stdcall rva00906340VecCtor(void *ptr, unsigned size, int count, Rva00906340CellFn ctor, Rva00906340CellFn dtor);
void rva00906340CellCtor(void *self);
void rva00906340CellDtor(void *self);

class Rva00906340
{
public:
	Rva00906340 *init();

	int m_tag;
	int m_zero;
	unsigned char m_cells[32];
	unsigned char m_pad[0x238];
	int m_260;
	int m_264;
	int m_268;
};

Rva00906340 *Rva00906340::init()
{
	m_tag = 0x0010441B;
	m_zero = 0;
	rva00906340VecCtor(m_cells, 4, 8, rva00906340CellCtor, rva00906340CellDtor);
	m_268 = 0;
	m_260 = 0;
	m_264 = 0;
	return this;
}
