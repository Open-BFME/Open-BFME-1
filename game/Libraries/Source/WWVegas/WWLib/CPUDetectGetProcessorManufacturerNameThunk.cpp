// cl: /DNDEBUG /MD /EHsc /Os

extern "C" unsigned int bfme_CPUDetectGetProcessorManufacturerName_A5EAED()
{
	unsigned int features;
	unsigned int signature;
	char vendor_id[13] = "UnknownVendr";
	char amd_id[13] = "AuthenticAMD";

	__asm {
		xor		eax, eax
		xor		ebx, ebx
		xor		ecx, ecx
		xor		edx, edx
		cpuid
		mov		features, 1
		xor		eax, eax
		cpuid
		mov		dword ptr vendor_id[0], ebx
		mov		dword ptr vendor_id[4], edx
		mov		dword ptr vendor_id[8], ecx
		test	eax, eax
		jz		Done
		or		features, 2
		mov		eax, 1
		cpuid
		mov		signature, eax
		mov		ecx, 000800000h
		and		ecx, edx
		neg		ecx
		sbb		ecx, ecx
		and		ecx, 000000020h
		or		features, ecx
		mov		ecx, 002000000h
		and		ecx, edx
		neg		ecx
		sbb		ecx, ecx
		and		ecx, 000000040h
		or		features, ecx
		mov		eax, 080000000h
		cpuid
		cmp		eax, 080000000h
		jbe		Done
		or		features, 4
		mov		eax, 080000001h
		cpuid
		mov		ecx, 080000000h
		and		ecx, edx
		neg		ecx
		sbb		ecx, ecx
		and		ecx, 000000080h
		or		features, ecx
		lea		esi, amd_id
		lea		edi, vendor_id
		mov		ecx, 12
		cld
		repe	cmpsb
		mov		ecx, 040000000h
		and		ecx, edx
		neg		ecx
		sbb		ecx, ecx
		and		ecx, 000000100h
		or		features, ecx
		mov		ecx, 000400000h
		and		ecx, edx
		neg		ecx
		sbb		ecx, ecx
		and		ecx, 000000200h
		or		features, ecx
		jmp		Done
Done:
	}

	return features;
}
