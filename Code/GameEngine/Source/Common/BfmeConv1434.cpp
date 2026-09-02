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

class BfmeStrVMN
{
public:
	void bfmeFwdVMN(int a, int b, int c, int d);
	void bfmeImplVMN(int a, int b, int c, int d);
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
		call bfmeImplVMN
	}
}
