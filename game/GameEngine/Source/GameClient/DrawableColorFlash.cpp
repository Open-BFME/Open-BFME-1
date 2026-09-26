// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /Iinputs/reference/shims/sweep /Iinputs/reference/shims/locomotor /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// This isolated definition preserves the retail offsets: Drawable's tint
// envelope is at +0x68 and its status word is at +0x110, while BFME's full
// header has a different source-only layout in this TU.
typedef unsigned int UnsignedInt;

struct RGBColor
{
	float red;
	float green;
	float blue;

	void setFromInt(int color)
	{
		red = ((color >> 16) & 0xff) / 255.0f;
		green = ((color >> 8) & 0xff) / 255.0f;
		blue = (color & 0xff) / 255.0f;
	}
};

class TintEnvelope
{
public:
	TintEnvelope();
	void play(const RGBColor *, UnsignedInt = 0x1, UnsignedInt = 0x4,
		UnsignedInt = 0x1);
	unsigned char m_layout[0x50];
};

class Drawable
{
	unsigned char m_pad00[0x68];
	TintEnvelope *m_colorTintEnvelope;
	unsigned char m_pad6c[0xa4];
	unsigned int m_status;

public:
	void clearDrawableStatus(unsigned int bit) { m_status &= ~bit; }
	void colorFlash(const RGBColor *, UnsignedInt, UnsignedInt, UnsignedInt);
};

void Drawable::colorFlash(const RGBColor *color, UnsignedInt decayFrames,
	UnsignedInt attackFrames, UnsignedInt sustainAtPeak)
{
	if (m_colorTintEnvelope == 0)
		m_colorTintEnvelope = new TintEnvelope;

	if (color)
		m_colorTintEnvelope->play(color, attackFrames, decayFrames, sustainAtPeak);
	else
	{
		RGBColor white;
		white.setFromInt(0xffffffff);
		m_colorTintEnvelope->play(&white);
	}

	clearDrawableStatus(0x4);
}
