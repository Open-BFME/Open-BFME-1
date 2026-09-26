// cl: /Od

struct BfmePadVMR
{
	char m[48];
};

struct BfmePad28VMR
{
	char m[26];
	char n[2];
};

class BfmeStrVMR
{
public:
	void bfmeFwdVMR(int a, int b, int c);
	void bfmeImplVMR(int a, int b, int c);
};

void BfmeStrVMR::bfmeFwdVMR(int a, int b, int c)
{
	BfmePadVMR z0, z1;
	BfmePad28VMR z2;

	__asm
	{
		xor eax, eax
		mov byte ptr z2.n[1], al
		lea ecx, z2.n
		push ecx
		mov edx, dword ptr c
		push edx
		mov eax, dword ptr b
		push eax
		mov ecx, dword ptr a
		push ecx
		mov ecx, this
		call bfmeImplVMR
	}
}
