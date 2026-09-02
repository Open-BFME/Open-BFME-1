// cl: /Od

struct BfmePadVMX
{
	char m[48];
};

struct BfmePad40VMX
{
	char m[38];
	char n[2];
};

struct BfmeObjVMX
{
	int a;
	int b;
};

class BfmeStrVMX
{
public:
	void bfmeFwdVMX(BfmeObjVMX *p);
	void bfmeImplVMX(int a, int b, char *q);
};

void BfmeStrVMX::bfmeFwdVMX(BfmeObjVMX *p)
{
	BfmePadVMX z0;
	BfmePad40VMX z2;

	__asm
	{
		mov eax, dword ptr p
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-0x54], ecx
		mov edx, dword ptr p
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x58], eax
		xor ecx, ecx
		mov byte ptr z2.n[1], cl
		lea edx, z2.n
		push edx
		mov eax, dword ptr [ebp-0x54]
		push eax
		mov ecx, dword ptr [ebp-0x58]
		push ecx
		mov ecx, this
		call bfmeImplVMX
	}
}
