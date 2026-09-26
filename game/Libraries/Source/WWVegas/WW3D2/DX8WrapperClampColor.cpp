// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug

// Complete retail entry 0x0090F310, 328 bytes, separated by int3 padding.
// The former 94-byte claim at 0x0090F3FA was the internal CMOV branch:
// the conditional jump at entry+7 reaches it when HasCMOVSupport is true.
// The missing x87 path clamps all four components before returning.
// Donor: DX8Wrapper::Clamp_Color in Zero Hour dx8wrapper.h. Its name is the
// existing donor mapping; no direct retail caller was found. The feature flag
// at VA 0x0134EDE8 is independently written by Init_Processor_Features from
// the CMOV feature bit. Keep the donor's existing cmovnb assembly; VC7.1
// emits conditional branches for its equivalent C++ expression.

#include "cpudetect.h"
#include "vector4.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Clamp_Color(Vector4 &color);
};

// ?Clamp_Color@DX8Wrapper@@SAXAAVVector4@@@Z
void DX8Wrapper::Clamp_Color(Vector4 &color)
{
	if (!CPUDetectClass::Has_CMOV_Instruction())
	{
		for (int i = 0; i < 4; ++i)
			color[i] = color[i] <= 0.0f ? 0.0f :
				(color[i] > 1.0f ? 1.0f : color[i]);
		return;
	}

	__asm
	{
		mov	esi,dword ptr color

		mov edx,0x3f800000

		mov edi,dword ptr[esi]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi],edi

		mov edi,dword ptr[esi+4]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi+4],edi

		mov edi,dword ptr[esi+8]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi+8],edi

		mov edi,dword ptr[esi+12]
		mov ebx,edi
		sar edi,31
		not edi
		and edi,ebx
		cmp edi,edx
		cmovnb edi,edx
		mov dword ptr[esi+12],edi
	}
}
