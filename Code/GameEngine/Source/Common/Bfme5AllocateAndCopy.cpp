// Six allocate-and-delegate copies.
//
// Each sizes a block for the count, allocates it through the size-dispatch
// helper with the usual zero arm, and hands the range plus the block plus the
// address of its own count parameter to a copier. The block lives in a
// callee-saved register across that call and comes back as the result.
//
// The fourth argument is the address of the first parameter slot, not a value:
// a lea of the incoming count. The element widths are 0x0C, 0x10, 0x18 and
// 0xEC -- all but the last fold into a scaled address, and the three bytes
// that saves are the whole difference between a seventy-six byte body and a
// seventy-nine byte one.

void *bfmeNewAlloc(unsigned int bytes);				// retail 0x00881F30
void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void *bfmeAllocate(unsigned int bytes)
{
	if (bytes > 0x80)
		return bfmeNewAlloc(bytes);

	return bfmeAllocNode(bytes);
}

struct BfmeCopyElem_00134BB0 { char m_bfmeBytes[0xEC]; };

__declspec(naked) void __cdecl bfmeCopyInto_00134BB0(const BfmeCopyElem_00134BB0 *first, const BfmeCopyElem_00134BB0 *last,
	BfmeCopyElem_00134BB0 *result, unsigned int *counter)
{
	__asm {
		mov edx, dword ptr [esp+4h]
		mov eax, dword ptr [esp+0Ch]
		push ebx
		mov ebx, dword ptr [esp+0Ch]
		cmp edx, ebx
		je bfmeCopyInto_00134BB0_done
		push esi
		push edi
	bfmeCopyInto_00134BB0_loop:
		test eax, eax
		je bfmeCopyInto_00134BB0_copied
		mov ecx, 3Bh
		mov esi, edx
		mov edi, eax
		rep movsd
	bfmeCopyInto_00134BB0_copied:
		add edx, 0ECh
		add eax, 0ECh
		cmp edx, ebx
		jne bfmeCopyInto_00134BB0_loop
		pop edi
		pop esi
	bfmeCopyInto_00134BB0_done:
		pop ebx
		ret
	}
}

struct BfmeCopyElem_00134C20 { char m_bfmeBytes[0xC]; };

void __cdecl bfmeCopyInto_00134C20(const BfmeCopyElem_00134C20 *first, const BfmeCopyElem_00134C20 *last,
	BfmeCopyElem_00134C20 *result, unsigned int *counter);	// retail 0x00031E4E

struct BfmeCopyElem_0020E8D0 { char m_bfmeBytes[0xC]; };

void __cdecl bfmeCopyInto_0020E8D0(const BfmeCopyElem_0020E8D0 *first, const BfmeCopyElem_0020E8D0 *last,
	BfmeCopyElem_0020E8D0 *result, unsigned int *counter);	// retail 0x00024528

struct BfmeCopyElem_00230120 { char m_bfmeBytes[0x18]; };

void __cdecl bfmeCopyInto_00230120(const BfmeCopyElem_00230120 *first, const BfmeCopyElem_00230120 *last,
	BfmeCopyElem_00230120 *result, unsigned int *counter);	// retail 0x0002894D

// ?bfmeMakeCopy_00134BB0@@YGPAUBfmeCopyElem_00134BB0@@IPBU1@0@Z
BfmeCopyElem_00134BB0 * __stdcall bfmeMakeCopy_00134BB0(unsigned int count,
	const BfmeCopyElem_00134BB0 *first, const BfmeCopyElem_00134BB0 *last)
{
	BfmeCopyElem_00134BB0 *block;

	if (count)
		block = (BfmeCopyElem_00134BB0 *)bfmeAllocate(count * sizeof(BfmeCopyElem_00134BB0));
	else
		block = 0;

	bfmeCopyInto_00134BB0(first, last, block, &count);

	return block;
}

// ?bfmeMakeCopy_00134C20@@YGPAUBfmeCopyElem_00134C20@@IPBU1@0@Z
BfmeCopyElem_00134C20 * __stdcall bfmeMakeCopy_00134C20(unsigned int count,
	const BfmeCopyElem_00134C20 *first, const BfmeCopyElem_00134C20 *last)
{
	BfmeCopyElem_00134C20 *block;

	if (count)
		block = (BfmeCopyElem_00134C20 *)bfmeAllocate(count * sizeof(BfmeCopyElem_00134C20));
	else
		block = 0;

	bfmeCopyInto_00134C20(first, last, block, &count);

	return block;
}

// ?bfmeMakeCopy_0020E8D0@@YGPAUBfmeCopyElem_0020E8D0@@IPBU1@0@Z
BfmeCopyElem_0020E8D0 * __stdcall bfmeMakeCopy_0020E8D0(unsigned int count,
	const BfmeCopyElem_0020E8D0 *first, const BfmeCopyElem_0020E8D0 *last)
{
	BfmeCopyElem_0020E8D0 *block;

	if (count)
		block = (BfmeCopyElem_0020E8D0 *)bfmeAllocate(count * sizeof(BfmeCopyElem_0020E8D0));
	else
		block = 0;

	bfmeCopyInto_0020E8D0(first, last, block, &count);

	return block;
}

// ?bfmeMakeCopy_00230120@@YGPAUBfmeCopyElem_00230120@@IPBU1@0@Z
BfmeCopyElem_00230120 * __stdcall bfmeMakeCopy_00230120(unsigned int count,
	const BfmeCopyElem_00230120 *first, const BfmeCopyElem_00230120 *last)
{
	BfmeCopyElem_00230120 *block;

	if (count)
		block = (BfmeCopyElem_00230120 *)bfmeAllocate(count * sizeof(BfmeCopyElem_00230120));
	else
		block = 0;

	bfmeCopyInto_00230120(first, last, block, &count);

	return block;
}

struct BfmeCopyElem_003B3E00 { char m_bfmeBytes[0x10]; };

void __cdecl bfmeCopyInto_003B3E00(const BfmeCopyElem_003B3E00 *first, const BfmeCopyElem_003B3E00 *last,
	BfmeCopyElem_003B3E00 *result, unsigned int *counter);	// retail 0x0002846B

// ?bfmeMakeCopy_003B3E00@@YGPAUBfmeCopyElem_003B3E00@@IPBU1@0@Z
BfmeCopyElem_003B3E00 * __stdcall bfmeMakeCopy_003B3E00(unsigned int count,
	const BfmeCopyElem_003B3E00 *first, const BfmeCopyElem_003B3E00 *last)
{
	BfmeCopyElem_003B3E00 *block;

	if (count)
		block = (BfmeCopyElem_003B3E00 *)bfmeAllocate(count * sizeof(BfmeCopyElem_003B3E00));
	else
		block = 0;

	bfmeCopyInto_003B3E00(first, last, block, &count);

	return block;
}

struct BfmeCopyElem_005716D0 { char m_bfmeBytes[0x10]; };

void __cdecl bfmeCopyInto_005716D0(const BfmeCopyElem_005716D0 *first, const BfmeCopyElem_005716D0 *last,
	BfmeCopyElem_005716D0 *result, unsigned int *counter);	// retail 0x00027782

// ?bfmeMakeCopy_005716D0@@YGPAUBfmeCopyElem_005716D0@@IPBU1@0@Z
BfmeCopyElem_005716D0 * __stdcall bfmeMakeCopy_005716D0(unsigned int count,
	const BfmeCopyElem_005716D0 *first, const BfmeCopyElem_005716D0 *last)
{
	BfmeCopyElem_005716D0 *block;

	if (count)
		block = (BfmeCopyElem_005716D0 *)bfmeAllocate(count * sizeof(BfmeCopyElem_005716D0));
	else
		block = 0;

	bfmeCopyInto_005716D0(first, last, block, &count);

	return block;
}
