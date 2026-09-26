// cl: /Ireference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// TextureLoader::Validate_Texture_Size(unsigned &, unsigned &) at 0x009056F0.
// Identity: matched callers W3DShroud::init and TaintBuffer::init call it, and the
// Generals W3DShroud.cpp twin names the two-argument call. BFME added the null-caps
// early out and clamps each power-of-two dimension through one inlined helper.

struct D3DCapsPrefix  // leading D3DCAPS8 fields (DirectX 8 SDK layout)
{
	unsigned char unmodelled_0[0x58];
	unsigned long MaxTextureWidth;
	unsigned long MaxTextureHeight;
};

class DX8Caps
{
public:
	const D3DCapsPrefix &Get_DX8_Caps() const { return Caps; }

private:
	int dword_0;
	int dword_4;
	D3DCapsPrefix Caps;
};

class DX8Wrapper
{
public:
	static const DX8Caps *Get_Current_Caps() { return CurrentCaps; }

protected:
	static DX8Caps *CurrentCaps;
};

class TextureLoader
{
public:
	static void Validate_Texture_Size(unsigned &width, unsigned &height);
};

// Returning the clamp as one conditional expression (not an assignment to the
// result) gives retail's ECX/EDX assignment in the height half.
static unsigned ClampedPowerOfTwo009056F0(unsigned dimension, unsigned maximum)
{
	unsigned result = 1;
	while (result < dimension) {
		result <<= 1;
	}
	return (result < maximum) ? result : maximum;
}

void TextureLoader::Validate_Texture_Size(unsigned &width, unsigned &height)
{
	const DX8Caps *caps = DX8Wrapper::Get_Current_Caps();
	if (caps == 0) {
		return;
	}
	const D3DCapsPrefix &dx8caps = caps->Get_DX8_Caps();
	width = ClampedPowerOfTwo009056F0(width, dx8caps.MaxTextureWidth);
	height = ClampedPowerOfTwo009056F0(height, dx8caps.MaxTextureHeight);
}
