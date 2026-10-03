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
};

// The ILT thunk at 0x00036DE0 is the retail body at this call site
// (targets/game/reverse/functions.csv ?j_00036de0@@YAXXZ, 5 bytes, tail jmp
// to 0x004A4F80).  It is called with ECX = this and two stack ints, so the
// defined thunk symbol replaces the TU-local placeholder method.
extern void j_00036de0();

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
		call j_00036de0
	}
}
