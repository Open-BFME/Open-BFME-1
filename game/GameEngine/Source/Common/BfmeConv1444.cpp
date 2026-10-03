// cl: /Od

struct BfmePadVMW
{
	char m[48];
};

struct BfmePad12VMW
{
	char m[11];
	char n;
};

struct BfmeObjVMW
{
	int a;
	int b;
};

class BfmeStrVMW
{
public:
	void bfmeFwdVMW(BfmeObjVMW *p);
};

// Retail 0x00831740 calls through the incremental-link thunk at 0x00021A58
// (E9 -> 0x000A5780). Its only definition in this link is the address-named
// ?j_00021a58@@YAXXZ in game/gen_small/thunks_015.cpp, so the asm block names
// that; the caller's thiscall shape is unchanged and the bytes do not move.
void j_00021a58();

void BfmeStrVMW::bfmeFwdVMW(BfmeObjVMW *p)
{
	BfmePadVMW z0, z1;
	BfmePad12VMW z2;

	__asm
	{
		mov eax, dword ptr p
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-0x68], ecx
		mov edx, dword ptr p
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x6C], eax
		xor ecx, ecx
		mov byte ptr z2.n, cl
		lea edx, z2.n
		push edx
		mov eax, dword ptr [ebp-0x68]
		push eax
		mov ecx, dword ptr [ebp-0x6C]
		push ecx
		mov ecx, this
		call j_00021a58
	}
}
