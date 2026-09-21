// ?rva009c74f0@@YAXHHHHHHH@Z
// partial score=0.95 date=2026-09-21
// cl: /DNDEBUG /MD /O2
//
// Retail 0x009C74F0, 465 bytes. Bink CPU-dispatch wrapper in the SSE2
// decoder family: chooses among the already-landed rva009C6F20/6FC0/7490
// four-tap filters (when p7 != 0) or the rva009C72C0/7320/7200 two-tap
// filters (when p7 == 0), based on how |p1-p2| relates to p4 or to p4+/-1.
// The four-tap side additionally unpacks its byte-filtered 256-byte scratch
// buffer to 16-bit output through the same inlined loop as
// bfmeUnpack8to16Sse.cpp (retail duplicates that loop here rather than
// calling it, reusing the p1/p2 incoming stack slots as scratch).
//
// Written as one inline-asm body, transcribed instruction-for-instruction
// from the disassembly (labels named after the retail hex offset), because
// a plain-C++ version of the dispatch logic compiled to the right control
// flow but not the same register/stack-slot choices once the mandatory
// SSE2 unpack loop (MSVC 7.1 does not form it from C++ or intrinsics,
// matching every BinkSse sibling's own note) forced the whole function out
// of full enregistration. p1..p7 are unidentified beyond their arithmetic
// role; getting the seven-way branch topology and exact cdecl push order
// right matters far more than a guess at what each one models.

extern void __cdecl rva009C6F20BinkSse(const void *, void *, int, int,
	int, int, const void *);
extern void __cdecl rva009C6FC0BinkSse(const void *, void *, int, int,
	int, int, const void *);
extern void __cdecl rva009C7490BinkSse(const unsigned char *,
	unsigned char *, int, const void *, const void *);
extern void __cdecl rva009C72C0BinkSse(const void *, void *, int, int,
	int, int, const void *);
extern void __cdecl rva009C7320BinkSse(const void *, void *, int, int,
	int, int, const void *);
extern void __cdecl rva009C7200BinkSse(const void *, void *, int,
	const void *, const void *);

// ?rva009c74f0@@YAXHHHHHHH@Z (address-derived; not landed)
__declspec(naked) void __cdecl rva009c74f0(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
	__asm
	{
		push ebp
		mov ebp, esp
		sub esp, 100h
		mov edx, p2
		mov ecx, p1
		mov eax, edx
		sub eax, ecx
		jns L1b
		mov eax, ecx
		mov ecx, edx
		sub eax, edx
	L1b:
		test eax, eax
		je L1cd
		mov edx, p7
		test edx, edx
		push esi
		je L114

		cmp eax, 1
		mov edx, p4
		jne L5c

		mov eax, p5
		shl eax, 6
		add eax, 12d8d10h
		push eax
		push 8
		push 8
		push 1
		push edx
		lea eax, [ebp-100h]
		push eax
		push ecx
		call rva009C6F20BinkSse
		add esp, 1ch
		jmp Ld5

	L5c:
		cmp eax, edx
		jne L84
		mov eax, p6
		shl eax, 6
		add eax, 12d8d10h
		push eax
		push 8
		push 8
		push edx
		push edx
		lea edx, [ebp-100h]
		push edx
		push ecx
		call rva009C6FC0BinkSse
		add esp, 1ch
		jmp Ld5

	L84:
		lea esi, [edx - 1]
		cmp eax, esi
		jne La5
		mov eax, p6
		shl eax, 6
		add eax, 12d8d10h
		push eax
		mov eax, p5
		shl eax, 6
		add eax, 12d8d10h
		dec ecx
		jmp Lc3

	La5:
		lea esi, [edx + 1]
		cmp eax, esi
		jne Ld5
		mov eax, p6
		shl eax, 6
		add eax, 12d8d10h
		push eax
		mov eax, p5
		shl eax, 6
		add eax, 12d8d10h
	Lc3:
		push eax
		push edx
		lea edx, [ebp-100h]
		push edx
		push ecx
		call rva009C7490BinkSse
		add esp, 14h

	Ld5:
		lea eax, [ebp-100h]
		push edi
		mov p2, 8
		mov p1, eax
		mov edi, p3
		mov esi, p1
		mov ecx, 8
		mov eax, 10h
		pxor xmm0, xmm0
	LunpackLoop:
		movdqu xmm3, [esi]
		punpcklbw xmm3, xmm0
		movdqu [edi], xmm3
		add esi, p2
		add edi, eax
		dec ecx
		jne LunpackLoop
		pop edi
		pop esi
		mov esp, ebp
		pop ebp
		ret

	L114:
		cmp eax, 1
		jne L141
		mov edx, p5
		shl edx, 5
		add edx, 12d8c10h
		push edx
		mov edx, p3
		push 10h
		push 8
		push eax
		mov eax, p4
		push eax
		push edx
		push ecx
		call rva009C72C0BinkSse
		add esp, 1ch
		pop esi
		mov esp, ebp
		pop ebp
		ret

	L141:
		mov edx, p4
		cmp eax, edx
		jne L16c
		mov eax, p6
		shl eax, 5
		add eax, 12d8c10h
		push eax
		push 10h
		push 8
		push edx
		push edx
		mov edx, p3
		push edx
		push ecx
		call rva009C7320BinkSse
		add esp, 1ch
		pop esi
		mov esp, ebp
		pop ebp
		ret

	L16c:
		lea esi, [edx - 1]
		cmp eax, esi
		jne L19f
		mov eax, p6
		shl eax, 5
		add eax, 12d8c10h
		push eax
		mov eax, p5
		shl eax, 5
		add eax, 12d8c10h
		push eax
		push edx
		mov edx, p3
		dec ecx
		push edx
		push ecx
		call rva009C7200BinkSse
		add esp, 14h
		pop esi
		mov esp, ebp
		pop ebp
		ret

	L19f:
		lea esi, [edx + 1]
		cmp eax, esi
		jne L1cc
		mov eax, p6
		shl eax, 5
		add eax, 12d8c10h
		push eax
		mov eax, p5
		shl eax, 5
		add eax, 12d8c10h
		push eax
		push edx
		mov edx, p3
		push edx
		push ecx
		call rva009C7200BinkSse
		add esp, 14h

	L1cc:
		pop esi
	L1cd:
	Lend:
		mov esp, ebp
		pop ebp
		ret
	}
}
