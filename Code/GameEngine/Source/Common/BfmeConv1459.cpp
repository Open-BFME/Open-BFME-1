// Open-BFME5 conversions.

char *bfmeFindVMQ(const char *a, const char *b);
int bfmeApplyVMQ(char *p, int n);

class BfmeThingVMQ
{
public:
	bool bfmeGoVMQ(const char *name, char flag);
	char m_bfmePad00[0x10];
	const char *m_bfme10;
};

bool BfmeThingVMQ::bfmeGoVMQ(const char *name, char flag)
{
	int n1 = (flag != 0);
	char *p = bfmeFindVMQ(m_bfme10, name);
	int n2;

	if (p == 0)
		n2 = n1;
	else
		n2 = bfmeApplyVMQ(p, n1);
	return n2 != 0;
}
