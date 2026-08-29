// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of the BFME dynamic-decal FX nugget constructor.

typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	volatile Real red;
	volatile Real green;
	volatile Real blue;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	volatile Real x;
	volatile Real y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

protected:
	volatile int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class DynamicDecalFXNugget : public FXNugget
{
public:
	DynamicDecalFXNugget();
	virtual ~DynamicDecalFXNugget();

private:
	// These TU-local volatile qualifiers preserve retail's constructor store order.
	enum ShaderType
	{
		ALPHA
	};

	AsciiString m_decalName;
	volatile ShaderType m_shader;
	volatile Real m_size;
	RGBColor m_color;
	Coord2D m_offset;
	volatile Bool m_orientToObject;
	unsigned char m_padD5[3];
	volatile UnsignedInt m_opacityStart;
	volatile Real m_opacityFadeTimeOne;
	volatile UnsignedInt m_opacityPeak;
	volatile Real m_opacityPeakTime;
	volatile Real m_opacityFadeTimeTwo;
	volatile UnsignedInt m_opacityEnd;
	volatile Real m_startingDelay;
	volatile Real m_lifetime;
};

DynamicDecalFXNugget::DynamicDecalFXNugget() :
	m_shader(ALPHA),
	m_size(0.0f)
{
	m_nuggetType = 13;
	m_color.red = 0.0f;
	m_color.green = 0.0f;
	m_color.blue = 0.0f;
	m_offset.x = m_offset.y = 0.0f;
	m_opacityStart = 0;
	m_opacityFadeTimeOne = 0.0f;
	m_opacityPeak = 0;
	m_opacityPeakTime = 0.0f;
	m_opacityFadeTimeTwo = 0.0f;
	m_opacityEnd = 0;
	m_startingDelay = 0.0f;
	m_lifetime = 0.0f;
	m_orientToObject = true;
}
