// ?Validate_Texture_Size@TextureLoader@@SAXAAI0@Z
// partial score=0.9 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// TextureLoader::Validate_Texture_Size(unsigned&, unsigned&)

struct D3DCapsPrefix
{
	unsigned char reserved[0x58];
	unsigned int MaxTextureWidth;
	unsigned int MaxTextureHeight;
};

class DX8Caps
{
public:
	const D3DCapsPrefix &Get_DX8_Caps() const { return Caps; }

private:
	int MaxDisplayWidth;
	int MaxDisplayHeight;
	D3DCapsPrefix Caps;
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
	static void Validate_Texture_Size(unsigned &width, unsigned &height);
};

static unsigned Valid_Texture_Dimension(unsigned dimension, unsigned maximum)
{
	unsigned result = 1;
	while (result < dimension) {
		result <<= 1;
	}
	if (result >= maximum) {
		result = maximum;
	}
	return result;
}

void TextureLoader::Validate_Texture_Size(unsigned &width, unsigned &height)
{
	const DX8Caps *currentCaps = DX8Wrapper::Get_Current_Caps();
	if (currentCaps == 0) {
		return;
	}
	const D3DCapsPrefix &caps = currentCaps->Get_DX8_Caps();
	unsigned validWidth = Valid_Texture_Dimension(width, caps.MaxTextureWidth);
	unsigned &heightOutput = height;
	width = validWidth;
	unsigned maximumHeight = caps.MaxTextureHeight;
	unsigned inputHeight = heightOutput;
	heightOutput = Valid_Texture_Dimension(inputHeight, maximumHeight);
}
