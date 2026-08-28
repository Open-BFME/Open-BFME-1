// cl: /DNDEBUG /MD /EHsc
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	~AsciiString();
	void clear();

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	float red;
	float green;
	float blue;

	void setFromInt( int value )
	{
		red = ((value >> 16) & 0xff) / 255.0f;
		green = ((value >> 8) & 0xff) / 255.0f;
		blue = (value & 0xff) / 255.0f;
	}
};

typedef int Color;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerColorDefinition
{
public:
	MultiplayerColorDefinition();

private:
	AsciiString m_tooltipName;
	RGBColor m_rgbValue;
	Color m_color;
	RGBColor m_rgbValueNight;
	Color m_colorNight;
};

MultiplayerColorDefinition::MultiplayerColorDefinition()
{
	m_tooltipName.clear();
	m_rgbValue.setFromInt( 0xffffffff );
	m_rgbValueNight = m_rgbValue;
	m_color = 0xffffffff;
	m_colorNight = m_color;
}
