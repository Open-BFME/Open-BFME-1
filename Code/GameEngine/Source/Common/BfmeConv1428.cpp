// cl: /Od

struct BfmePadVMF
{
	int m[10];
};

class BfmeStrVMF
{
public:
	void bfmeFwdVMF(int a, int b, int c, int d);
	void bfmeImplVMF(int a, int b, int c, char *p);
};

void BfmeStrVMF::bfmeFwdVMF(int a, int b, int c, int d)
{
	char n;
	BfmePadVMF z0, z1, z2;

	bfmeImplVMF(a, b, c, &n);
}
