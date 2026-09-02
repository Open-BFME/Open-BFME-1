// cl: /Od

struct BfmePadVMT
{
	char m[48];
};

struct BfmePad20VMT
{
	char m[18];
	char n[2];
};

class BfmeStrVMT
{
public:
	void bfmeFwdVMT(int a, int b);
	void bfmeImplVMT(int a, int b);
};

void BfmeStrVMT::bfmeFwdVMT(int a, int b)
{
	BfmePadVMT z0;
	BfmePad20VMT z2;

	__asm
	{
		xor eax, eax
		mov byte ptr z2.n[1], al
		lea ecx, z2.n
		push ecx
		mov edx, dword ptr a
		add edx, dword ptr b
		push edx
		mov eax, dword ptr a
		push eax
		mov ecx, this
		call bfmeImplVMT
	}
}
