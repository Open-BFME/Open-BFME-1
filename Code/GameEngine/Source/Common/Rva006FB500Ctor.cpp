// cl: /O2 /Ob0

class Rva00020004
{
public:
	Rva00020004();
	virtual void handle();
};

int g_rva006FB500_slot;

class Rva006FB500 : public Rva00020004
{
	int m_04;
	int *m_08;

public:
	Rva006FB500();
};

Rva006FB500::Rva006FB500()
{
	m_08 = &g_rva006FB500_slot;
}
