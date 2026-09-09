// ?bfmeDot006e1be0@@YGMMMM@Z
// partial score=0.93 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc

struct BfmeVec4_006e1be0
{
	float x;
	float y;
	float z;
	float w;
};

#define g_bfmeDefault006e1be0 (*(float *)0x0111E238)
#define g_bfmeObj006e1be0 (*(char * volatile *)0x012F8048)

float __stdcall bfmeDot006e1be0(float x, float y, float z)
{
	char *object = g_bfmeObj006e1be0;
	float result = g_bfmeDefault006e1be0;
	if (object)
	{
		const int offset = 0x84;
		BfmeVec4_006e1be0 row = *(BfmeVec4_006e1be0 *)(object + offset);
		result = row.z * z;
		result += row.y * y;
		result += row.x * x;
		result += row.w;
	}
	return result;
}
