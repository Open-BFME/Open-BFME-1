// cl: /DNDEBUG /MD /EHsc
// ShaderClass::Set_Cull_Mode, retail 0x006C5310 (21 bytes): Zero Hour's inline
// setter, emitted out of line. It replaces the cull-mode bit of ShaderBits
// (bit 20 here, bit 19 in Zero Hour) and keeps every other bit. Open-BFME-2's
// matched Set_Cull_Mode is byte-identical and BFME1's ILT slot confirms the
// decoration.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	enum CullModeType
	{
		CULL_MODE_DISABLE = 0,
		CULL_MODE_ENABLE,
		CULL_MODE_MAX
	};

	void Set_Cull_Mode( CullModeType x );

private:
	enum
	{
		SHIFT_CULLMODE = 20,
		MASK_CULLMODE = ( 1 << SHIFT_CULLMODE )
	};

	unsigned int ShaderBits;
};

void ShaderClass::Set_Cull_Mode( CullModeType x )
{
	ShaderBits &= ~MASK_CULLMODE;
	ShaderBits |= x << SHIFT_CULLMODE;
}
