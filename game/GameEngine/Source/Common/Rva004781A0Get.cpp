// cl: /O2 /Ob0

class Rva004781A0
{
	char pad[0x24];
	int m_24;
	int m_28;

public:
	int get(int *a, int *b);
};

int Rva004781A0::get(int *a, int *b)
{
	if (a)
		*a = m_24;
	if (b)
		*b = m_28;
	return 0;
}
