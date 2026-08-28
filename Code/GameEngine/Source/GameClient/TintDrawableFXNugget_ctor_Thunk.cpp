// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of the BFME tint-drawable FX nugget constructor.

typedef float Real;
typedef unsigned int UnsignedInt;

struct RGBColor
{
	RGBColor(Real r, Real g, Real b) : red(r), green(g), blue(b) {}

	Real red;
	Real green;
	Real blue;
};

class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

protected:
	int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class TintDrawableFXNugget : public FXNugget
{
public:
	TintDrawableFXNugget();
	virtual ~TintDrawableFXNugget();

private:
	RGBColor m_color;
	UnsignedInt m_preColorTime;
	UnsignedInt m_postColorTime;
	UnsignedInt m_sustainedColorTime;
	Real m_frequency;
	Real m_amplitude;
};

TintDrawableFXNugget::TintDrawableFXNugget() :
	m_color(1.0f, 1.0f, 1.0f),
	m_preColorTime(2000),
	m_postColorTime(2000),
	m_sustainedColorTime(1000),
	m_frequency(1.0f),
	m_amplitude(1.0f)
{
}
