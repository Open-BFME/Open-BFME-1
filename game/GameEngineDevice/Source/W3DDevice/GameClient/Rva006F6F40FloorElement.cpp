// ?update@Rva006F6F40FloorElement@@QAE_NXZ
// Retail 0x006F6F40, 376 bytes. Owner identity remains address-derived.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
#include "matrix3d.h"

typedef float Real;

extern const Real BfmeZeroRange;
extern Real g_bfmeDefaultBU;

class BfmeCalc919G
{
public:
	int bfmeCalc919G();
};

class Rva006F6F40Provider
{
private:
	unsigned char m_pad00[0xb0];

public:
	Real m_scale;
	Real m_step;
};

class Rva006F6F40FloorElement
{
public:
	bool update();

private:
	unsigned char m_head[0x28];
	Rva006F6F40Provider *m_provider;
	unsigned char m_pad2c[0x20];
	Matrix3D m_matrix;
	unsigned char m_pad7c[4];
	Real m_value;
	Real m_step;
	unsigned char m_pad88[8];
	int m_mode;
};

bool Rva006F6F40FloorElement::update()
{
	if (m_provider == 0 || m_mode != 1)
		return false;

	bool changed = false;
	Real value;
	if (m_step != BfmeZeroRange)
	{
		value = m_value + m_step;
		if (value < BfmeZeroRange)
			value = BfmeZeroRange;
		else if (value > g_bfmeDefaultBU)
			value = g_bfmeDefaultBU;
	}
	else
	{
		value = m_provider->m_step * m_provider->m_scale;
		Matrix3D *source = (Matrix3D *)(long)
			reinterpret_cast<BfmeCalc919G *>(m_provider)->bfmeCalc919G();
		if (m_matrix != *source)
		{
			source = (Matrix3D *)(long)
				reinterpret_cast<BfmeCalc919G *>(m_provider)->bfmeCalc919G();
			m_matrix = *source;
			changed = true;
		}
	}

	if (m_value != value)
	{
		m_value = value;
		changed = true;
	}
	return changed;
}
