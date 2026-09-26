// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Open-BFME5: the 125-byte guard/overlay callback at retail 0x004CAF70.
//
// The control-flow and object fast path are ordinary C++.  Retail's +0xC0
// entries are cdecl vtable calls that retain the object in ECX; MSVC 7.1 has
// no C++ spelling for that mixed ABI, so the two dispatch sequences are kept
// as the narrow, proven code-generation exception here.

struct Rva004CAF70Obj
{
	char m_pad[0x26c];
	char m_flag;
};

extern char g_rva004CAF70_gate;
extern Rva004CAF70Obj *g_rva004CAF70_obj;
extern void *g_rva004CAF70_value;
extern void *g_rva004CAF70_g;
extern char g_rva004CAF70_a[];
extern char g_rva004CAF70_b[];
extern char g_rva004CAF70_c[];
extern char g_rva004CAF70_d[];
extern char g_rva004CAF70_e[];
extern char g_rva004CAF70_f[];

extern void j_000056c8(void);
extern void j_0001e4bb(void);
extern void j_00022ab6(void);

typedef char (*Rva004CAF70Gate)(void);

void rva004CAF70(void)
{
	if (((Rva004CAF70Gate)j_000056c8)() == 0)
		return;
	if (g_rva004CAF70_gate != 0)
		return;
	Rva004CAF70Obj *p = g_rva004CAF70_obj;
	if (p != 0)
	{
		p->m_flag = 1;
		return;
	}

	__asm {
		mov eax, dword ptr [g_rva004CAF70_value]
		mov ecx, dword ptr [g_rva004CAF70_g]
		mov edx, dword ptr [ecx]
		push offset g_rva004CAF70_f
		push eax
		push offset g_rva004CAF70_e
		push offset g_rva004CAF70_d
		push offset g_rva004CAF70_c
		push offset g_rva004CAF70_b
		push offset g_rva004CAF70_a
		call dword ptr [edx+0c0h]
		push eax
		call j_0001e4bb
		mov ecx, dword ptr [g_rva004CAF70_g]
		mov eax, dword ptr [ecx]
		add esp, 20h
		push 0
		push offset g_rva004CAF70_f
		call dword ptr [eax+0c0h]
		push eax
		call j_00022ab6
		add esp, 0ch
	}
}
