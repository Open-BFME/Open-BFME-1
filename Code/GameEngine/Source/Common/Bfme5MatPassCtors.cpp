// Open-BFME5 conversions: two constructors over library base types.

class MaterialPassClass
{
public:
	MaterialPassClass(void);
	virtual ~MaterialPassClass();

	char m_bfmePad[0x34];
};

extern int g_bfme5MatPassCount;

class Bfme5MaterialPass : public MaterialPassClass
{
public:
	Bfme5MaterialPass(int a, int b);
	virtual ~Bfme5MaterialPass();

	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
	int m_bfme44;
};

Bfme5MaterialPass::Bfme5MaterialPass(int a, int b)
{
	m_bfme38 = a;
	m_bfme3c = b;
	m_bfme40 = 0;
	m_bfme44 = 0;
	++g_bfme5MatPassCount;
}

class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition(const MultiplayerColorDefinition &o);

	int m_bfmeColor;
};

class Bfme5ColorRecord
{
public:
	Bfme5ColorRecord(const Bfme5ColorRecord &o);
	virtual ~Bfme5ColorRecord();

	int m_bfme04;
	int m_bfme08;
	MultiplayerColorDefinition m_bfme0c;
	char m_bfme10;
};

Bfme5ColorRecord::Bfme5ColorRecord(const Bfme5ColorRecord &o)
	: m_bfme04(o.m_bfme04), m_bfme08(o.m_bfme08), m_bfme0c(o.m_bfme0c), m_bfme10(o.m_bfme10)
{
}

struct Bfme5ColorTriple
{
	MultiplayerColorDefinition m_bfmeColour;
	int m_bfme04;
	int m_bfme08;
};

class Bfme5TripleRecord
{
public:
	Bfme5TripleRecord(const int *p, const Bfme5ColorTriple &t);

	int m_bfme00;
	Bfme5ColorTriple m_bfme04;
};

Bfme5TripleRecord::Bfme5TripleRecord(const int *p, const Bfme5ColorTriple &t)
	: m_bfme00(*p), m_bfme04(t)
{
}
