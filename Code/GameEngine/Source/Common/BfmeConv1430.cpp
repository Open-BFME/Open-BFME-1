// cl: /Od

struct BfmePadVMI
{
	int m[12];
};

class BfmeStrVMI
{
public:
	void bfmeFwdVMI(int a, int b, int c, int d, int e);
	void bfmeImplVMI(int a, int b, int c, int d, char *p);
};

void BfmeStrVMI::bfmeFwdVMI(int a, int b, int c, int d, int e)
{
	char n;
	BfmePadVMI z0, z1, z2;

	bfmeImplVMI(a, b, c, d, &n);
}
