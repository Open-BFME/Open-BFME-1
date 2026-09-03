// cl: /DNDEBUG /MD /EHs-c-
#include <math.h>

extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline long bfme_fistp(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Gen_009431F0
{
public:
	int map_x(float x);
	int map_y(float y);

private:
	float origin_x;
	float origin_y;
	unsigned char pad[0x18];
	float scale;
	int count;
};

int Gen_009431F0::map_x(float x)
{
	float t = (x - origin_x) * scale * (float)(unsigned)count;
	int i = (int)bfme_fistp((float)floor((double)t));
	if (i < 0)
		return 0;
	int c = count;
	if ((unsigned)i >= (unsigned)c)
		return c - 1;
	return i;
}

int Gen_009431F0::map_y(float y)
{
	float t = (y - origin_y) * scale * (float)(unsigned)count;
	int i = (int)bfme_fistp((float)floor((double)t));
	if (i < 0)
		return 0;
	int c = count;
	if ((unsigned)i >= (unsigned)c)
		return c - 1;
	return i;
}
