// cl: /DNDEBUG /MD /EHsc

typedef float Real;
typedef unsigned int UnsignedInt;

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

class Drawable
{
public:
	void applyTint(RGBColor color, UnsignedInt preColorTime,
		UnsignedInt postColorTime, UnsignedInt sustainedColorTime,
		Real frequency, Real amplitude);

private:
	char m_fields[0x6c];
	RGBColor m_tintColor;
	UnsignedInt m_preColorTime;
	UnsignedInt m_postColorTime;
	UnsignedInt m_sustainedColorTime;
	Real m_amplitude;
	Real m_frequency;
};

void Drawable::applyTint(RGBColor color, UnsignedInt preColorTime,
	UnsignedInt postColorTime, UnsignedInt sustainedColorTime,
	Real frequency, Real amplitude)
{
	m_tintColor = color;
	m_preColorTime = preColorTime;
	m_postColorTime = postColorTime;
	m_sustainedColorTime = sustainedColorTime;
	m_frequency = frequency;
	m_amplitude = amplitude;
}
