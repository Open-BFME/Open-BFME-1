class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

class BfmeHostYI
{
public:
	Vector3 *bfmeGetPosYI(Vector3 *out);

	unsigned char m_bfmeHeadYI[0x70];
	RenderObjClass *m_bfme70YI;
};

Vector3 *BfmeHostYI::bfmeGetPosYI(Vector3 *out)
{
	RenderObjClass *r = m_bfme70YI;

	if (r != 0)
	{
		Vector3 p = r->Get_Position();

		out->X = *(volatile float *)&p.X;
		out->Y = p.Y;
		out->Z = p.Z;
	}
	else
	{
		out->X = 0.0f;
		out->Y = 0.0f;
		out->Z = 0.0f;
	}

	return out;
}
