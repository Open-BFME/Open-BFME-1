// ?Convert_Color_Clamp@Rva0090F460@@SAIVVector4@@@Z, retail 0x0090F460.

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

	float &operator[](int index) { return (&X)[index]; }
	const float &operator[](int index) const { return (&X)[index]; }
};

class Rva0090F460
{
public:
	static unsigned int Convert_Color_Clamp(Vector4 color);

private:
	static __forceinline unsigned int Convert_Color(const Vector3 &color, float alpha);
};

// ?Convert_Color@Rva0090F460@@SAIABVVector3@@M@Z present-unmatched
__forceinline unsigned int Rva0090F460::Convert_Color(const Vector3 &color, float alpha)
{
	const float scale = 255.0;
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
		jz skip
		mov [esp],eax
		fldcw [esp]
skip:
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
		fistp dword ptr[esp]
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
		je not_changed
		fwait
		fldcw [esp+16]
not_changed:
		add esp,20
		mov col,eax
	}

	return col;
}

unsigned int Rva0090F460::Convert_Color_Clamp(Vector4 color)
{
	Vector4 *clamped_color = &color;

	if (!(*(volatile bool *)0x0134EDE8)) {
		for (int i = 0; i < 4; ++i) {
			(*clamped_color)[i] = ((*clamped_color)[i] <= 0.0f) ? 0.0f :
				(((*clamped_color)[i] > 1.0f) ? 1.0f : (*clamped_color)[i]);
		}
	} else {
		__asm
		{
			mov esi,dword ptr clamped_color
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

	const float alpha = (*clamped_color)[3];
	const Vector3 &rgb = reinterpret_cast<const Vector3 &>(*clamped_color);
	return Convert_Color(rgb, alpha);
}
