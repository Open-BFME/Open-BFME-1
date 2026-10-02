// cl: /O2 /DNDEBUG /MD /EHsc

// Retail reads the constant 0.0 out of the compiler's own literal pool at image
// VA 0x01085F58, whose dir32 name is __real@0000000000000000 and which every
// object using a zero double emits as a folded COMDAT.  It is a code literal,
// not a game datum, so it is defined here rather than left unresolved.
static const double bfmeZeroDouble = 0.0;

extern "C" void __fastcall Rva00385FB0Initialize(void *self)
{
	__asm {
		mov eax, ecx
		fld qword ptr [bfmeZeroDouble]
		xor ecx, ecx
		mov byte ptr [eax], cl
		mov dword ptr [eax+4h], ecx
		mov dword ptr [eax+8h], ecx
		fstp qword ptr [eax+50h]
		fld qword ptr [bfmeZeroDouble]
		mov byte ptr [eax+0Ch], cl
		fstp qword ptr [eax+58h]
		mov dword ptr [eax+10h], ecx
		fld qword ptr [bfmeZeroDouble]
		mov byte ptr [eax+14h], cl
		fstp qword ptr [eax+60h]
		mov dword ptr [eax+18h], ecx
		fld qword ptr [bfmeZeroDouble]
		mov dword ptr [eax+1Ch], ecx
		fstp qword ptr [eax+68h]
		mov dword ptr [eax+20h], ecx
		fld qword ptr [bfmeZeroDouble]
		mov dword ptr [eax+24h], ecx
		fstp qword ptr [eax+70h]
		mov byte ptr [eax+28h], cl
		fld qword ptr [bfmeZeroDouble]
		mov dword ptr [eax+30h], ecx
		fstp qword ptr [eax+78h]
		mov dword ptr [eax+34h], ecx
		fld qword ptr [bfmeZeroDouble]
		mov dword ptr [eax+38h], ecx
		fstp qword ptr [eax+80h]
		mov dword ptr [eax+3Ch], ecx
		mov dword ptr [eax+40h], ecx
		mov dword ptr [eax+44h], ecx
		mov dword ptr [eax+48h], ecx
		mov dword ptr [eax+4Ch], ecx
		mov dword ptr [eax+88h], ecx
		mov dword ptr [eax+8Ch], ecx
		mov dword ptr [eax+90h], ecx
		mov dword ptr [eax+94h], ecx
	}
}
