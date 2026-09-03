// cl: /DNDEBUG /MD /EHsc

// DX8Wrapper::Clamp_Color, retail 0x0090F3FA. Out-of-line copy of the
// Zero Hour inline in dx8wrapper.h, minus the runtime CMOV detect: BFME's
// body is the Pentium-Pro integer clamp and nothing else. cmovnb is a
// compiler-machinery instruction; the upstream already emits it from this
// asm, which is why a C++ ternary does not.

class Vector4;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Clamp_Color(Vector4 &color);
};

// ?Clamp_Color@DX8Wrapper@@SAXAAVVector4@@@Z
void DX8Wrapper::Clamp_Color(Vector4 &color)
{
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
