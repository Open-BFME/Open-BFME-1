// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shadow.h
class Shadow
{
public:
	void setOpacity(Int value);

private:
	char m_pad00[0x24];
	UnsignedInt m_color;
	Int m_diffuse;
	UnsignedInt m_opacity;
	char m_pad30[4];
	UnsignedInt m_type;
};

void Shadow::setOpacity(Int value)
{
	m_opacity = value;

	if (m_type & 0x1420)
	{
		m_diffuse = (m_color & 0x00ffffff) + (value << 24);
	}
	else if (m_type & 0x0840)
	{
		Real fvalue = (Real)m_opacity / 255.0f;
		m_diffuse = (Int)((Real)(m_color & 0xff) * fvalue)
			| ((Int)((Real)((m_color >> 8) & 0xff) * fvalue) << 8)
			| ((Int)((Real)((m_color >> 16) & 0xff) * fvalue) << 16);
	}
}
