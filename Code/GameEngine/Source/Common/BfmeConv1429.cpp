// cl: /Od

struct BfmePadVMG
{
	int m[12];
};

class BfmeStrVMG
{
public:
	void bfmeFwdVMG(int a, int b, int c, int d);
	void bfmeImplVMG(int a, int b, int c, char *p);
};

void BfmeStrVMG::bfmeFwdVMG(int a, int b, int c, int d)
{
	char n;
	BfmePadVMG z0, z1, z2;

	bfmeImplVMG(a, b, c, &n);
}
