// ?fill@Rva00726EA0TaintFill@@QAEXE@Z
// partial score=0.99 date=2026-09-04
// ?fill@Rva00726EA0TaintFill@@QAEXE@Z
// partial score=0.99 date=2026-09-04
// cl: /DNDEBUG /MD
// Retail 0x00726EA0: fill the taint overlay's dword and byte buffers.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_pad00[0xCA0];
	unsigned char m_taintAlpha;
	unsigned char m_padCA1[0xCF5 - 0xCA1];
	unsigned char m_taintOn;
};

extern GlobalData *TheWritableGlobalData;

class Rva00726EA0TaintFill
{
public:
	void fill(unsigned char alpha);

private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned char m_pad08[0x18 - 0x08];
	unsigned int *m_dwords;
	unsigned char m_pad1C[0x38 - 0x1C];
	unsigned char *m_bytes;
};

// ?fill@Rva00726EA0TaintFill@@QAEXE@Z
void Rva00726EA0TaintFill::fill(unsigned char alpha)
{
	GlobalData *g = TheWritableGlobalData;
	if (!g)
		return;
	if (!g->m_taintOn)
		return;
	unsigned char floor = g->m_taintAlpha;
	if (alpha < floor)
		alpha = floor;
	unsigned int color = alpha;
	color = (color << 8) | alpha;
	color = (color << 8) | alpha;
	color = (color << 8) | alpha;
	unsigned int *dst = m_dwords;
	unsigned int y;
	for (y = 0; y < m_height; y++)
	{
		unsigned int x;
		for (x = 0; x < m_width; )
		{
			*dst = color;
			x++;
			dst++;
		}
	}
	unsigned int row = (unsigned int)m_bytes;
	for (y = 0; y < m_height; y++)
	{
		unsigned int i;
		for (i = 0; i < m_width; )
		{
			*(char *)(i + row) = alpha;
			i++;
		}
		row += m_width;
	}
}
