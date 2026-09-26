// cl: /O2 /Ob0

extern float g_bfmeScaleBC;

struct BfmeVecBC
{
	float x;
	float y;
	float z;
};

void bfmeFillBC(BfmeVecBC *out, int a, int b);

class BfmeObjBC
{
public:
	BfmeVecBC *bfmeGoBC(BfmeVecBC *out);
	float bfmeValBC();
	char m_00[0x84];
	int m_84;
	int m_88;
	int m_8C;
	int m_90;
	int m_94;
	int m_98;
};

BfmeVecBC *BfmeObjBC::bfmeGoBC(BfmeVecBC *out)
{
	int r = (int)(bfmeValBC() * g_bfmeScaleBC) % 3;
	if (r == 0)
	{
		bfmeFillBC(out, m_84, m_88);
		return out;
	}
	if (r == 1)
	{
		bfmeFillBC(out, m_8C, m_90);
		return out;
	}
	if (r == 2)
	{
		bfmeFillBC(out, m_94, m_98);
		return out;
	}
	out->x = 1000.0f;
	out->y = 1000.0f;
	out->z = 1000.0f;
	return out;
}
