// cl: /DNDEBUG /MD /EHsc

typedef int Color;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayString.h
class W3DDisplayString
{
public:
	void setTextColor(Color *colors);
	void setDropColor(Color *colors);

private:
	unsigned char m_unmodelled_000[0x1CC];
	Color m_textColors[4];
	Color m_dropColors[4];
	volatile bool m_colorsChanged;
};

void W3DDisplayString::setTextColor(Color *colors)
{
	if (!m_colorsChanged && m_textColors[0] != colors[0])
		m_colorsChanged = true;
	m_textColors[0] = colors[0];
	_ReadWriteBarrier();

	if (!m_colorsChanged && m_textColors[1] != colors[1])
		m_colorsChanged = true;
	m_textColors[1] = colors[1];
	_ReadWriteBarrier();

	if (!m_colorsChanged && m_textColors[2] != colors[2])
		m_colorsChanged = true;
	m_textColors[2] = colors[2];
	_ReadWriteBarrier();

	if (!m_colorsChanged && m_textColors[3] != colors[3])
		m_colorsChanged = true;
	m_textColors[3] = colors[3];
}

void W3DDisplayString::setDropColor(Color *colors)
{
	if (!m_colorsChanged && m_dropColors[0] != colors[0])
		m_colorsChanged = true;
	m_dropColors[0] = colors[0];
	_ReadWriteBarrier();

	if (!m_colorsChanged && m_dropColors[1] != colors[1])
		m_colorsChanged = true;
	m_dropColors[1] = colors[1];
	_ReadWriteBarrier();

	if (!m_colorsChanged && m_dropColors[2] != colors[2])
		m_colorsChanged = true;
	m_dropColors[2] = colors[2];
	_ReadWriteBarrier();

	if (!m_colorsChanged && m_dropColors[3] != colors[3])
		m_colorsChanged = true;
	m_dropColors[3] = colors[3];
}
