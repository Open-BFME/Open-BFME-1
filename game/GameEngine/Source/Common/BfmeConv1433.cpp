// cl: /Od

struct BfmePadVML
{
	char m[48];
};

struct BfmePad44VML
{
	char m[44];
};

// Tag type of the retail callee at 0x008314E0, spelled as its defining name.
struct BfmeRangeTag;

class Rva008314E0String
{
public:
	Rva008314E0String &replaceRange(char *first, char *last, char *sourceFirst,
		char *sourceLast, const BfmeRangeTag &tag);
};

class BfmeStrVML
{
public:
	void bfmeFwdVML(int a, int b, int c, int d, int e);
};

void BfmeStrVML::bfmeFwdVML(int a, int b, int c, int d, int e)
{
	BfmePadVML z0, z1;
	BfmePad44VML z2;

	((Rva008314E0String *)this)->replaceRange((char *)a, (char *)b, (char *)c,
		(char *)d, *(const BfmeRangeTag *)&z2.m[43]);
}