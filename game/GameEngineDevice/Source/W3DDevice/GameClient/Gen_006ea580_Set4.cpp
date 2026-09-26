// cl: /DNDEBUG /MD /EHsc

// Retail 0x006EA580. Copy a 16-byte struct to +0x168 and set +0x178 = 1.

struct Gen_006ea580_Quad
{
	int a;
	int b;
	int c;
	int d;
};

class Gen_006ea580
{
public:
	void set(const Gen_006ea580_Quad *v);

private:
	unsigned char m_pad[0x168];
	Gen_006ea580_Quad m_q;
	unsigned char m_178;
};

// ?set@Gen_006ea580@@QAEXPBUGen_006ea580_Quad@@@Z
void Gen_006ea580::set(const Gen_006ea580_Quad *v)
{
	m_q = *v;
	m_178 = 1;
}
