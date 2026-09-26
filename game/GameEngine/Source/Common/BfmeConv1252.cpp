// Open-BFME5 conversions.

struct BfmeVec1252
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeV1252
{
public:
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
	int m_bfme0c;
};

extern "C" void bfmeGet1252(void *a, void *b, BfmeVec1252 *t);
extern "C" int bfmeCheck1252(void *a, BfmeVec1252 *t);

int bfmeTest1252(void *a, BfmeV1252 *b)
{
	BfmeVec1252 t;

	bfmeGet1252(a, &b->m_bfme0c, &t);
	t.m_bfme00 = b->m_bfme00 - t.m_bfme00;
	t.m_bfme04 = b->m_bfme04 - t.m_bfme04;
	t.m_bfme08 = b->m_bfme08 - t.m_bfme08;
	return bfmeCheck1252(a, &t) == 1;
}
