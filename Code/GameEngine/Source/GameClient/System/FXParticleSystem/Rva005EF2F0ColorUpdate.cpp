// Clean C++ reconstruction of the BFME particle colour update at retail 0x005EF2F0.
// Layout is anchored by the matched BfmeHostEN::bfmeStepEN at 0x005EF250.

struct BfmeClockEF4
{
	unsigned char m_prefix[0x34];
	unsigned int m_now;
	unsigned char m_between[0x68 - 0x38];
	unsigned int m_start;
};

struct BfmeColorEF4
{
	float red;
	float green;
	float blue;
};

struct BfmeColorKeyEF4
{
	BfmeColorEF4 color;
	unsigned int frame;
};

class BfmeHostEN { public: void bfmeStepEN(); };

class Rva005EF2F0
{
public:
	void updateEF4();
	void bfmeStepEN() { reinterpret_cast<BfmeHostEN *>(this)->bfmeStepEN(); }

private:
	unsigned char m_prefix[4];
	BfmeClockEF4 *m_system;
	unsigned char m_headTail[8];
	BfmeColorKeyEF4 m_colorKey[8];
	volatile float m_colorScale;
	BfmeColorEF4 m_color;
	BfmeColorEF4 m_colorRate;
	int m_colorTargetKey;
};

void Rva005EF2F0::updateEF4()
{
	m_color.red += m_colorRate.red;
	int target = m_colorTargetKey;
	float greenValue = m_colorRate.green;
	greenValue += m_color.green;
	m_color.green = greenValue;
	m_color.blue += m_colorRate.blue;

	if (target < 8 && m_colorKey[target].frame)
	{
		if (m_system->m_now - m_system->m_start >= m_colorKey[target].frame)
		{
			++target;
			m_colorTargetKey = target;
			bfmeStepEN();
		}
	}
	else
	{
		m_colorRate.red = 0.0f;
		m_colorRate.green = 0.0f;
		m_colorRate.blue = 0.0f;
	}

	m_color.red += m_colorScale;
	m_color.green += m_colorScale;
	float blueValue = m_color.blue;
	blueValue += m_colorScale;
	m_color.blue = blueValue;

	if (m_color.red < 0.0f)
		m_color.red = 0.0f;
	else if (m_color.red > 1.0f)
		m_color.red = 1.0f;

	if (m_color.green < 0.0f)
		m_color.green = 0.0f;
	else if (m_color.green > 1.0f)
		m_color.green = 1.0f;

	if (m_color.blue < 0.0f)
		m_color.blue = 0.0f;
	else if (m_color.blue > 1.0f)
		m_color.blue = 1.0f;
}