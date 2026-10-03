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
};

// Retail 0x008316E0 calls through the incremental-link thunk at 0x00011522
// (E9 -> 0x000A4030). Its only definition in this link is the address-named
// ?j_00011522@@YAXXZ in game/gen_small/thunks_007.cpp, so the asm block names
// that; the caller's thiscall shape is unchanged and the bytes do not move.
void j_00011522();

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
		call j_00011522
	}
}
