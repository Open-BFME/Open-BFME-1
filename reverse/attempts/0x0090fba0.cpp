// ?rva0090FBA0ConvertColors@@YAXPAIHPBURva0090FBA0Vector4@@H@Z
// partial score=0.92 date=2026-09-25
// ?rva0090FBA0ConvertColors@@YAXPAIHPBURva0090FBA0Vector4@@H@Z
// Address-derived four-argument strided Vector4 color conversion helper.

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
	if (!*(volatile unsigned char *)0x0134EDE8)
	{
		for (int i = 0; i < 4; ++i)
		{
			color[i] = (color[i] <= *(const float *)0x01075350)
				? *(const float *)0x01075350
				: ((color[i] > *(const float *)0x01075334)
					? *(const float *)0x01075334 : color[i]);
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

void rva0090FBA0ConvertColors(
	unsigned int *out, int stride,
	const Rva0090FBA0Vector4 *colors, int count)
{
	if (!count)
		return;

	Rva0090FBA0Vector4 clamped_color;
	Rva0090FBA0Vector4 *clamped_ptr = &clamped_color;
	Rva0090FBA0Vector3 *color3 = reinterpret_cast<Rva0090FBA0Vector3 *>(clamped_ptr);

	while (count)
	{
		*clamped_ptr = *colors;
		rva0090FBA0Clamp(*clamped_ptr);
		unsigned int packed = rva0090FBA0Pack(
			*color3,
			(*clamped_ptr)[3]);
		*out = packed;
		++colors;
		out = (unsigned int *)((char *)out + stride);
		--count;
	}
}
