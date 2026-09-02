// ?Add@Render2DRawArray@@QAEPAURender2DPackedVert@@H@Z
// partial score=0.72 date=2026-09-02
// cl: /DNDEBUG /MD /G6 /EHsc
// Render2D packed-vertex grow: 0x2C-byte elements, realloc on overflow.

extern "C" __declspec(dllimport) void *__cdecl realloc(void *p, unsigned int bytes);

struct Render2DPackedVert
{
	unsigned char bytes[0x2C];
};

class Render2DRawArray
{
public:
	Render2DPackedVert *Add(int count);

	Render2DPackedVert *Data;
	int Size;
	int Count;
	int GrowthStep;
};

// ?Add@Render2DRawArray@@QAEPAURender2DPackedVert@@H@Z
Render2DPackedVert *Render2DRawArray::Add(int count)
{
	if (count != 0)
	{
		if ((unsigned)count < 0x80000000u)
		{
			int new_count = Count + count;
			int cap = Size;
			Count = new_count;
			if ((unsigned)new_count > (unsigned)cap)
			{
				int grown = new_count + GrowthStep;
				Size = grown;
				Render2DPackedVert *p = (Render2DPackedVert *)realloc(Data, (unsigned)grown * sizeof(Render2DPackedVert));
				Data = p;
				if (p == 0)
					return 0;
				return p + (new_count - count);
			}
			return Data + (new_count - count);
		}
	}
	return 0;
}
