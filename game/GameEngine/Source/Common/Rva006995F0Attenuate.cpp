// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Distance attenuation into +0x94; refreshPair(i,1) x6.

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

void __stdcall refreshPair(int a, int b);

struct Rva006995F0Range
{
	char m_pad[0x1c];
	float m_near;
	float m_near2;
	float m_far;
	float m_far2;
	float m_scale;
};

struct Rva006995F0Vec3
{
	float x;
	float y;
	float z;
};

class Rva006995F0Owner
{
public:
	void attenuate(Rva006995F0Range *range, Rva006995F0Vec3 *pos);

	char m_pad[0x94];
	float m_vol;
};

void Rva006995F0Owner::attenuate(Rva006995F0Range *range, Rva006995F0Vec3 *pos)
{
	float scale = range->m_scale;
	float far2 = range->m_far2;

	if (scale > 0.0f)
	{
		float x = pos->x;
		float y = pos->y;
		float z = pos->z;
		float dist2 = x * x + y * y + z * z;
		if (dist2 < range->m_near2)
		{
			m_vol = 1.0f;
		}
		else if (dist2 < far2)
		{
			float nearv = range->m_near;
			m_vol = 1.0f - (((float)sqrt((double)dist2) - nearv) / (range->m_far - nearv)) * scale;
		}
		else
		{
			m_vol = 1.0f - scale;
		}
	}

	for (int i = 0; i < 6; ++i)
		refreshPair(i, 1);
}
