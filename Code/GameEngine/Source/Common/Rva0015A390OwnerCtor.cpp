// cl: /O2
// ??0Rva0015A390Owner@@QAE@XZ
// Open-BFME: clean reconstruction of retail 0x0015A390 (322 B), a leaf
// constructor for a 0x1BC-byte object. The only caller, 0x0015AB50, builds
// twelve of these in a local array (stride 0x1BC, through ILT thunk
// 0x00044DFA) and then clamps +0x4 into [2,6] the way
// Rva0015A530::set does. No vtable, string or Zero Hour twin names the
// class or its fields, so the names keep the address token and field
// offsets. +0x4 starts as twice a count read from TheAI (0x012EF214)
// through the unwitnessed pointer at +0x14 and its field +0xB0.

#include <string.h>

class AI;
extern AI *TheAI;

class Rva0015A390Inner
{
public:
	Rva0015A390Inner() { memset(this, 0, sizeof(*this)); }

	int dword_0;
	int dword_4;
	int dword_8;
	int dword_c;
	int dword_10;
	int dword_14;
};

class Rva0015A390Bucket
{
public:
	Rva0015A390Bucket() : dword_0(0) {}

	int dword_0;
	Rva0015A390Inner inner_4;
};

class Rva0015A390Owner
{
public:
	Rva0015A390Owner();

private:
	int dword_0;
	int dword_4;
	Rva0015A390Bucket bucket_8[10];
	int dword_120;
	int dword_124[36];
	int dword_1b4;
	bool byte_1b8;
};

Rva0015A390Owner::Rva0015A390Owner()
	: dword_0(0),
	  dword_4(*(int *)(*(char **)((char *)TheAI + 0x14) + 0xb0) * 2),
	  dword_120(0),
	  dword_1b4(0),
	  byte_1b8(false)
{
	for (int i = 0; i < 36; ++i)
		dword_124[i] = 0;
}
