// cl: /O2 /Ob0

struct Rva005A4620Out
{
	float a;
	float b;
	float c;
	float d;
};

class Rva005A4620
{
	char pad[0x4D88];
	int m_4D88;
	int m_4D8C;
	int m_4D90;
	int m_4D94;

public:
	void get(Rva005A4620Out *o);
};

void Rva005A4620::get(Rva005A4620Out *o)
{
	if (o)
	{
		o->a = (float)m_4D88;
		o->c = (float)m_4D8C;
		o->b = (float)m_4D90;
		o->d = (float)m_4D94;
	}
}
