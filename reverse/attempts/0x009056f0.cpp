// ?d_009056f0@@YAXXZ
// partial score=0.86 date=2026-08-31
// Clean reconstruction of the two-dimensional texture-size validator used by
// the retail renderer.  These compact declarations retain only the witnessed
// prefix of the renderer-capabilities classes.

struct D3DCapsPrefix
{
	unsigned char reserved[0x58];
	unsigned int maxTextureWidth;
	unsigned int maxTextureHeight;
};

class DX8Caps
{
public:
	const D3DCapsPrefix &Get_DX8_Caps() const { return caps; }

private:
	unsigned int maxDisplayWidth;
	unsigned int maxDisplayHeight;
	D3DCapsPrefix caps;
};

class DX8Wrapper
{
public:
	static const DX8Caps *Get_Current_Caps() { return CurrentCaps; }
	static DX8Caps *CurrentCaps;
};

class TextureLoader
{
public:
	static void Validate_Texture_Size(unsigned int &width, unsigned int &height);
};

static unsigned int Valid_Texture_Dimension(unsigned int dimension, unsigned int maximum)
{
	unsigned int result = 1;
	while (result < dimension) {
		result <<= 1;
	}
	if (result >= maximum) {
		result = maximum;
	}
	return result;
}

void TextureLoader::Validate_Texture_Size(unsigned int &width, unsigned int &height)
{
	const DX8Caps *currentCaps = DX8Wrapper::Get_Current_Caps();
	if (currentCaps == 0) {
		return;
	}
	const D3DCapsPrefix &caps = currentCaps->Get_DX8_Caps();
	unsigned int validWidth = Valid_Texture_Dimension(width, caps.maxTextureWidth);
	unsigned int &heightOutput = height;
	width = validWidth;
	unsigned int maximumHeight = caps.maxTextureHeight;
	unsigned int inputHeight = heightOutput;
	heightOutput = Valid_Texture_Dimension(inputHeight, maximumHeight);
}
