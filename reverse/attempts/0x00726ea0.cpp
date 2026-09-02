// ?fill@Rva00726EA0TaintFill@@QAEXE@Z
// partial score=0.99 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x00726EA0: fill two taint buffers when GlobalData::TaintOn is set.
// TaintAlpha at +0xCA0 and TaintOn at +0xCF5 (docs/ini_schema.md).  The byte
// argument is raised to TaintAlpha, then splat into a dword and written
// across m_width x m_height at +0x18 (dwords) and +0x38 (bytes).

class GlobalData
{
public:
	unsigned char m_pad[0xCA0];
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
	unsigned char *bytes = m_bytes;
	for (y = 0; y < m_height; y++)
	{
		unsigned int x;
		for (x = 0; x < m_width; )
		{
			bytes[x] = alpha;
			x++;
		}
		bytes += m_width;
	}
}
