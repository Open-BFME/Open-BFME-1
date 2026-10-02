// cl: /Od

struct BfmePadVMN
{
	char m[48];
};

struct BfmePad44VMN
{
	char m[42];
	char n[2];
};

// Tag type of the retail callee at 0x008314E0, spelled as its defining name.
struct BfmeRangeTag;

class Rva008314E0String
{
public:
	Rva008314E0String &replaceRange(char *first, char *last, char *sourceFirst,
		char *sourceLast, const BfmeRangeTag &tag);
};

class BfmeStrVMN
{
public:
	void bfmeFwdVMN(int a, int b, int c, int d);
};

void BfmeStrVMN::bfmeFwdVMN(int a, int b, int c, int d)
{
	BfmePadVMN z0, z1;
	BfmePad44VMN z2;

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
		call Rva008314E0String::replaceRange
	}
}
