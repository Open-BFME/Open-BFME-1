// ?d_008f7f00@@YAXXZ
// partial score=0.35 date=2026-09-24
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /ICode/Libraries/Include/Lib

#include "trig.h"

// ?method@Rva008F7F00@@QAE_NMMMMM@Z
//
// No proven callers (0 callers in carved.csv), so the receiver, world grid
// and cell types are address-derived rather than claimed real names. Scans
// a rectangle of half-extents (halfW, halfH) centred at (cx, cy) and rotated
// by angle, cell by cell through the world grid at m_00 (same bfmeAt shape
// as Bfme5SeventySevenWorldAt.cpp / Gen_008F7CD0), and head-links one
// Element per hit cell from the m_1c array (same field BfmeThingCDEInitializeArray.cpp
// fills and Rva008F7EC0Sweep.cpp unlinks) into that cell's intrusive list.

class Element;

class BfmeCellFD
{
public:
	Element *m_firstElem;
	unsigned char m_pad04[0x60];
	unsigned int m_frameStamp;
};

class Element
{
public:
	BfmeCellFD *m_cell;
	void *m_04;
	Element **m_pprev;
	Element *m_next;
};

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(float x, float y) const;

	unsigned char m_pad00[0x1c];
	float m_cellSize;
	float m_scale;
};

class Rva008F7F00
{
public:
	bool method(float cx, float cy, float halfW, float halfH, float angle);

	Gen_008F7CD0 *m_00;
	unsigned char m_pad04[0x18];
	Element *m_1c;
};

extern const float g_bfmeK1253;
extern const float g_rva003D2B80NegHalf;
extern const float g_bfmeK1266B;
extern unsigned int g_0133f408;

extern "C" __declspec(dllimport) double bfmeMathVE(double value);

bool Rva008F7F00::method(float cx, float cy, float halfW, float halfH, float angle)
{
	float c = Cos(angle);
	float s = Sin(angle);

	Gen_008F7CD0 *world = m_00;
	float dxCol = c * world->m_cellSize * g_bfmeK1253;
	float dyCol = s * world->m_cellSize * g_bfmeK1253;
	float dxRow = dyCol;
	float dyRow = c * world->m_cellSize * g_rva003D2B80NegHalf;

	int countX = (int)(float)bfmeMathVE((double)(world->m_scale * halfW * g_bfmeK1266B));
	int countY = (int)(float)bfmeMathVE((double)(world->m_scale * halfH * g_bfmeK1266B));

	float worldX = cx - c * halfW - s * halfH;
	float worldY = cy + c * halfH - s * halfW;

	if (countY <= 0)
		return true;

	++g_0133f408;

	float baseX = worldX;
	float baseY = worldY;
	Element *e = m_1c;
	int rows = countY;
	do
	{
		if (countX > 0)
		{
			float curX = baseX;
			float curY = baseY;
			int cols = countX;
			do
			{
				BfmeCellFD *cell = world->bfmeAt(curX, curY);
				if (cell && g_0133f408 != cell->m_frameStamp)
				{
					cell->m_frameStamp = g_0133f408;
					e->m_cell = cell;
					Element *head = cell->m_firstElem;
					e->m_next = head;
					if (head)
						head->m_pprev = &e->m_next;
					e->m_pprev = (Element **)cell;
					cell->m_firstElem = e;
				}
				++e;
				curX += dxCol;
				curY += dyCol;
			} while (--cols);
		}
		baseX += dxRow;
		baseY += dyRow;
	} while (--rows);

	return true;
}
