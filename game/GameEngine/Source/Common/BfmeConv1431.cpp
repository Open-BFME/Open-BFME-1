// cl: /Od

struct BfmePadVMI
{
	int m[12];
};

struct Rva008312E0Tag
{
};

class Rva008312E0String
{
public:
	Rva008312E0String &bfmeReplaceAliasedRange(char *first, char *last,
		char *sourceFirst, char *sourceLast, const Rva008312E0Tag &tag);
};

class BfmeStrVMI
{
public:
	void bfmeFwdVMI(int a, int b, int c, int d, int e);
};

void BfmeStrVMI::bfmeFwdVMI(int a, int b, int c, int d, int e)
{
	Rva008312E0Tag n;
	BfmePadVMI z0, z1, z2;

	reinterpret_cast<Rva008312E0String *>(this)->bfmeReplaceAliasedRange(
		reinterpret_cast<char *>(a), reinterpret_cast<char *>(b),
		reinterpret_cast<char *>(c), reinterpret_cast<char *>(d), n);
}
