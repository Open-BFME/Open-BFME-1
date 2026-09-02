// ?bfmeDot006e1be0@@YGMMMM@Z
// partial score=0.5 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

struct BfmeVec4_006e1be0
{
	float x;
	float y;
	float z;
	float w;
};

extern "C" float g_bfmeDefault006e1be0;
extern "C" char *g_bfmeObj006e1be0;

float __stdcall bfmeDot006e1be0(float x, float y, float z)
{
	char *object = g_bfmeObj006e1be0;
	float result = g_bfmeDefault006e1be0;
	if (object)
	{
		BfmeVec4_006e1be0 row = *(BfmeVec4_006e1be0 *)(object + 0x84);
		result = row.z * z + row.y * y + row.x * x + row.w;
	}
	return result;
}
