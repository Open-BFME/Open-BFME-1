// cl: /O2 /Ob0

class BfmeElemVMZ
{
public:
	void bfmeTailVMZ(void *self, int a0, int a2, int a3, int a4, int a5, int k);
	char m_pad[0x18];
};

class BfmeThingVMZ
{
public:
	void bfmeGo1VMZ(int a0, int i, int a2, int a3, int a4, int a5);
	void bfmeGo2VMZ(int a0, int i, int a2, int a3, int a4, int a5);
	char m_pad[0x64];
	BfmeElemVMZ m_arr[3];
};

void BfmeThingVMZ::bfmeGo1VMZ(int a0, int i, int a2, int a3, int a4, int a5)
{
	if (i < 3)
		m_arr[i].bfmeTailVMZ(this, a0, a2, a3, a4, a5, 1);
}

void BfmeThingVMZ::bfmeGo2VMZ(int a0, int i, int a2, int a3, int a4, int a5)
{
	if (i < 3)
		m_arr[i].bfmeTailVMZ(this, a0, a2, a3, a4, a5, 2);
}
