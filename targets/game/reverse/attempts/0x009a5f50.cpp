// ?d_009a5f50@@YAXXZ
// partial score=0.5116 date=2026-09-30
// cl: /DNDEBUG /MD /O2
// Generic tier of the VP6 post-filter noise kernel at dispatch slot 0x01356E60
// (installer 0x009B0D60 stores it at 0x009B10C3); five-argument cdecl like Rva009BA790.

#include <math.h>
#include <stdlib.h>

// Same TU as the landed Gaussian at 0x009A5F00, which retail inlines here.
// ?bfmeGaussPdf@@YANNNN@Z
double __cdecl bfmeGaussPdf(double a, double b, double c)
{
	return exp(-((c - b) * (c - b)) / (a * a + a * a)) / (a * sqrt(6.2831853));
}

// ?Rva009A5F50AddNoise@@YAXPAEIIHH@Z
void __cdecl Rva009A5F50AddNoise(unsigned char *start, unsigned int width,
	unsigned int height, int pitch, int q)
{
	unsigned int i, j;
	char charDist[300];
	char noise[2048];
	double sigma;

	sigma = 1 + .8 * (63 - q) / 63.0;

	// 256-entry lookup table following a Gaussian whose sigma depends on q.
	{
		double x;
		int next, k;

		next = 0;
		for (x = -32; x < 32; x++)
		{
			int count = (int)(.5 + 256 * bfmeGaussPdf(sigma, 0, x));
			if (count)
			{
				for (k = 0; k < count; k++)
					charDist[next + k] = (char)x;
				next = next + k;
			}
		}
		for (; next < 256; next++)
			charDist[next] = 0;
	}

	for (i = 0; i < 2048; i++)
		noise[i] = charDist[rand() & 0xff];

	for (i = 0; i < height; i++)
	{
		unsigned char *pos = start + i * pitch;
		char *ref = noise + (rand() & 0xff);
		for (j = 0; j < width; j++)
		{
			if (pos[j] < -charDist[0])
				pos[j] = -charDist[0];
			if (pos[j] > 255 - charDist[0])
				pos[j] = 255 - charDist[0];
			pos[j] += ref[j];
		}
	}
}
