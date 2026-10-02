// cl: /Od

struct BfmePad56VMO
{
	char m[56];
};

struct BfmePadVMO
{
	char m[48];
};

struct BfmePad44VMO
{
	char m[42];
	char n[2];
};

struct Rva008312E0Tag;

class Rva008312E0String
{
public:
	Rva008312E0String &bfmeReplaceAliasedRange(char *first, char *last,
		char *sourceFirst, char *sourceLast, const Rva008312E0Tag &tag);
};

class BfmeStrVMO
{
public:
	void bfmeFwdVMO(int a, int b, int c, int d);
};

void BfmeStrVMO::bfmeFwdVMO(int a, int b, int c, int d)
{
	BfmePad56VMO z0;
	BfmePadVMO z1;
	BfmePad44VMO z2;

	__asm
	{
		xor eax, eax
		mov byte ptr z2.n[1], al
		lea ecx, z2.n
		push ecx
		mov edx, dword ptr d
		push edx
		mov eax, dword ptr c
		push eax
		mov ecx, dword ptr b
		push ecx
		mov edx, dword ptr a
		push edx
		mov ecx, this
		call Rva008312E0String::bfmeReplaceAliasedRange
	}
}
