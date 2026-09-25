// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// ?rva0090FBA0ConvertColors@@YAXPAIHPBURva0090FBA0Vector4@@H@Z, retail 0x0090FBA0.
// Strided array form of the Zero Hour inline DX8Wrapper::Convert_Color_Clamp
// (dx8wrapper.h): copy each 16-byte color, Clamp_Color it (x87 loop unless
// CPUDetectClass::HasCMOVSupport, then the upstream cmovnb asm), pack it with
// the upstream Convert_Color fistp asm, store at a byte stride. The flag is
// HasCMOVSupport: Init_Processor_Features (0x009DF1C0 +0x45) stores
// (FeatureBits>>15)&1 to 0x0134EDE8. Owner and name unproven: address token.

#include "cpudetect.h"

struct Rva0090FBA0Vector3
{
	float x;
	float y;
	float z;
};

struct Rva0090FBA0Vector4
{
	float x;
	float y;
	float z;
	float w;

	const float &operator[](int index) const { return (&x)[index]; }
	float &operator[](int index) { return (&x)[index]; }
};

static __forceinline void rva0090FBA0Clamp(Rva0090FBA0Vector4 &color)
{
	if (!CPUDetectClass::Has_CMOV_Instruction())
	{
		for (int i = 0; i < 4; ++i)
		{
			color[i] = (color[i] <= 0.0f)
				? 0.0f
				: ((color[i] > 1.0f)
					? 1.0f : color[i]);
		}
		return;
	}

	__asm
	{
		mov esi,dword ptr color
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

static __forceinline unsigned int rva0090FBA0Pack(
	const Rva0090FBA0Vector3 &color, float alpha)
{
	const float scale = 255.0f;
	unsigned int col;

	__asm
	{
		sub esp,20
		fwait
		fstcw [esp+16]
		mov eax,[esp+16]
		mov edi,eax
		and eax,~(1024|2048)
		or eax,(1024|2048)
		sub edi,eax
		jz rva0090fba0_fpu_unchanged
		mov [esp],eax
		fldcw [esp]
rva0090fba0_fpu_unchanged:
		mov esi,dword ptr color
		fld dword ptr[scale]
		fld dword ptr[esi]
		fld dword ptr[esi+4]
		fld dword ptr[esi+8]
		fld dword ptr[alpha]
		fld st(4)
		fmul st(4),st
		fmul st(3),st
		fmul st(2),st
		fmulp st(1),st
		fistp dword ptr[esp+0]
		fistp dword ptr[esp+4]
		fistp dword ptr[esp+8]
		fistp dword ptr[esp+12]
		mov ecx,[esp]
		mov eax,[esp+4]
		mov edx,[esp+8]
		mov ebx,[esp+12]
		shl ecx,24
		shl ebx,16
		shl edx,8
		or eax,ecx
		or eax,ebx
		or eax,edx
		fstp st(0)
		cmp edi,0
		je rva0090fba0_fpu_restored
		fwait
		fldcw [esp+16]
rva0090fba0_fpu_restored:
		add esp,20
		mov col,eax
	}

	return col;
}

static __forceinline unsigned int rva0090FBA0ConvertColorClamp(
	const Rva0090FBA0Vector4 &color)
{
	Rva0090FBA0Vector4 clamped_color = color;
	rva0090FBA0Clamp(clamped_color);
	return rva0090FBA0Pack(
		reinterpret_cast<const Rva0090FBA0Vector3 &>(clamped_color),
		clamped_color[3]);
}

void rva0090FBA0ConvertColors(
	unsigned int *out, int stride,
	const Rva0090FBA0Vector4 *colors, int count)
{
	for (; count; --count)
	{
		*out = rva0090FBA0ConvertColorClamp(*colors);
		++colors;
		out = (unsigned int *)((char *)out + stride);
	}
}
