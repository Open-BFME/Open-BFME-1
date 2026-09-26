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

class BfmeThingFV
{
public:
	void bfmeComputeFV(BfmeArgFV *a, BfmeVec3FV *out);
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
	BfmeThingFV *t = *(BfmeThingFV **)((char *)this - 0x48);

	if (t == 0)
	{
		out->x = 0.0f;
		out->y = 0.0f;
		out->z = 0.0f;

		return;
	}

	BfmeVec3FV tmp;

	t->bfmeComputeFV(&o->m_bfmeArgFV, &tmp);

	out->x = *(const volatile float *)&tmp.x;
	out->y = tmp.y;
	out->z = tmp.z;
}
