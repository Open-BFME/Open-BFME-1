class BfmeVec3FV
{
public:
	float x;
	float y;
	float z;
};

class BfmeArgFV
{
public:
	unsigned char m_bfmeHeadFV[4];
};

// ILT 0x0002F734 -> 0x00132780, the matched Thing::transformPoint
// (Common/Thing/Thing.cpp).
struct Coord3D;

class Thing
{
public:
	void transformPoint(const Coord3D *in, Coord3D *out);
};

class BfmeOwnerFV
{
public:
	unsigned char m_bfmeHeadFV[0x204];
	BfmeArgFV m_bfmeArgFV;
};

class BfmeHostFV
{
public:
	void bfmeGetFV(BfmeVec3FV *out);
};

void BfmeHostFV::bfmeGetFV(BfmeVec3FV *out)
{
	BfmeOwnerFV *o = *(BfmeOwnerFV **)((char *)this - 0x4c);
	Thing *t = *(Thing **)((char *)this - 0x48);

	if (t == 0)
	{
		out->x = 0.0f;
		out->y = 0.0f;
		out->z = 0.0f;

		return;
	}

	BfmeVec3FV tmp;

	t->transformPoint((const Coord3D *)&o->m_bfmeArgFV, (Coord3D *)&tmp);

	out->x = *(const volatile float *)&tmp.x;
	out->y = tmp.y;
	out->z = tmp.z;
}
