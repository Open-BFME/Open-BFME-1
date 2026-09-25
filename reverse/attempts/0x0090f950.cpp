// ?d_0090f950@@YAXXZ
// partial score=0.2 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc
// Retail 0x0090F950 packs one clamped Vector4 into an output word.

class Vector3
{
	public:
	float X;
	float Y;
	float Z;
};

class Vector4
{
	public:
	float X;
	float Y;
	float Z;
	float W;
	Vector4(const Vector4 &other)
		: X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}

	const float &operator[](int index) const { return (&X)[index]; }
	float &operator[](int index) { return (&X)[index]; }
};

class DX8Wrapper
{
public:
	static __forceinline void Clamp_Color(Vector4 &color)
	{
		if (!*(volatile unsigned char *)0x0134EDE8) {
			for (int i = 0; i < 4; ++i) {
				float f = (color[i] <= *(const float *)0x01075350)
					? *(const float *)0x01075350 : color[i];
				if (f > *(const float *)0x01075334)
					f = *(const float *)0x01075334;
				color[i] = f;
			}
			return;
		}

		__asm
		{
			mov	esi,dword ptr color
			mov	edx,0x3f800000

			mov	edi,dword ptr[esi]
			mov	ebx,edi
			sar	edi,31
			not	edi
			and	edi,ebx
			cmp	edi,edx
			cmovnb	edi,edx
			mov	dword ptr[esi],edi

			mov	edi,dword ptr[esi+4]
			mov	ebx,edi
			sar	edi,31
			not	edi
			and	edi,ebx
			cmp	edi,edx
			cmovnb	edi,edx
			mov	dword ptr[esi+4],edi

			mov	edi,dword ptr[esi+8]
			mov	ebx,edi
			sar	edi,31
			not	edi
			and	edi,ebx
			cmp	edi,edx
			cmovnb	edi,edx
			mov	dword ptr[esi+8],edi

			mov	edi,dword ptr[esi+12]
			mov	ebx,edi
			sar	edi,31
			not	edi
			and	edi,ebx
			cmp	edi,edx
			cmovnb	edi,edx
			mov	dword ptr[esi+12],edi
		}
	}
};

static __forceinline unsigned int Rva0090F950ConvertColor(
	const Vector3 &color, float alpha)
{
	const float scale = 255.0;
	unsigned int col;

	__asm
	{
		sub	esp,20
		fwait
		fstcw	[esp+16]
		mov	eax,[esp+16]
		mov	edi,eax
		and	eax,~(1024|2048)
		or	eax,(1024|2048)
		sub	edi,eax
		jz	rva0090f950_fpu_unchanged
		mov	[esp],eax
		fldcw	[esp]
	rva0090f950_fpu_unchanged:
		mov	esi,dword ptr color
		fld	dword ptr[scale]
		fld	dword ptr[esi]
		fld	dword ptr[esi+4]
		fld	dword ptr[esi+8]
		fld	dword ptr[alpha]
		fld	st(4)
		fmul	st(4),st
		fmul	st(3),st
		fmul	st(2),st
		fmulp	st(1),st
		fistp	dword ptr[esp+0]
		fistp	dword ptr[esp+4]
		fistp	dword ptr[esp+8]
		fistp	dword ptr[esp+12]
		mov	ecx,[esp]
		mov	eax,[esp+4]
		mov	edx,[esp+8]
		mov	ebx,[esp+12]
		shl	ecx,24
		shl	ebx,16
		shl	edx,8
		or	eax,ecx
		or	eax,ebx
		or	eax,edx
		fstp	st(0)
		cmp	edi,0
		je	rva0090f950_fpu_restored
		fwait
		fldcw	[esp+16]
	rva0090f950_fpu_restored:
		add	esp,20
		mov	col,eax
	}
	return col;
}

static __forceinline unsigned int Rva0090F950ConvertColorClamp(
	const Vector4 &color)
{
	Vector4 clamped_color = color;
	DX8Wrapper::Clamp_Color(clamped_color);
	return Rva0090F950ConvertColor(
		reinterpret_cast<const Vector3 &>(clamped_color), clamped_color[3]);
}

// ?Rva0090F950PackColor@@YAXPAIPBVVector4@@@Z
void Rva0090F950PackColor(unsigned int *out, const Vector4 *color)
{
	Vector4 clamped_color = *color;
	Vector4 *clamped_ptr = &clamped_color;
	DX8Wrapper::Clamp_Color(*clamped_ptr);
	unsigned int packed = Rva0090F950ConvertColor(
		reinterpret_cast<const Vector3 &>(*clamped_ptr), (*clamped_ptr)[3]);
	*out = packed;
}
