// cl: /Od

struct BfmePadVML
{
	char m[48];
};

struct BfmePad44VML
{
	char m[44];
};

class BfmeStrVML
{
public:
	void bfmeFwdVML(int a, int b, int c, int d, int e);
	void bfmeImplVML(int a, int b, int c, int d, char *p);
};

void BfmeStrVML::bfmeFwdVML(int a, int b, int c, int d, int e)
{
	BfmePadVML z0, z1;
	BfmePad44VML z2;

	bfmeImplVML(a, b, c, d, &z2.m[43]);
}
