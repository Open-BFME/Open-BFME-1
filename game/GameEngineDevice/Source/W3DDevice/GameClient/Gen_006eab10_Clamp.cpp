// cl: /DNDEBUG /MD /EHsc

// Retail 0x006EAB10. g = (g > 0) ? 0 : a; return true.

int g_006eab10;

// ?clamp_006eab10@@YG_NHH@Z
bool __stdcall clamp_006eab10(int a, int)
{
	if (g_006eab10 > 0)
		g_006eab10 = 0;
	else
		g_006eab10 = a;
	return true;
}
