// Retail 0x0073B8E0 (152 bytes).  Identity: the matched caller
// BfmeViewETH::bfmeSetAngleETH (BfmeConv1985.cpp) calls it through ILT
// 0x00030846 with &m_bfmeSubETH, the x/y pair at +0x0C.  Guarded by the byte
// at +0x44: shifts the pair by a quarter of the render object's planar offset
// from it, lets the sub-object at +0x24B8 (slot 0x54) consume the shifted
// pair, then shifts it back.
//
// Shape: the offset is computed in place on the position Vector3
// (pos = pos - Vector3(...); pos *= 0.25f) with WWMath-style inline operators,
// and 0.25f is a literal (VA 0x01083B6C) so the multiply keeps retail's
// operand order.
extern const float g_bfmeScaleEW;

class Vector3
{
public:
	Vector3() {}
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	Vector3 &operator*=(float k) { X *= k; Y *= k; Z *= k; return *this; }
	friend Vector3 operator-(const Vector3 &a, const Vector3 &b)
	{
		return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
	}
	friend Vector3 operator*(const Vector3 &a, float k)
	{
		return Vector3(a.X * k, a.Y * k, a.Z * k);
	}

	float X;
	float Y;
	float Z;
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

class BfmeSubETH
{
public:
	float m_x;
	float m_y;
};

class BfmeSubEW
{
public:
	virtual void bfmeSlot0EW();
	virtual void bfmeSlot1EW();
	virtual void bfmeSlot2EW();
	virtual void bfmeSlot3EW();
	virtual void bfmeSlot4EW();
	virtual void bfmeSlot5EW();
	virtual void bfmeSlot6EW();
	virtual void bfmeSlot7EW();
	virtual void bfmeSlot8EW();
	virtual void bfmeSlot9EW();
	virtual void bfmeSlot10EW();
	virtual void bfmeSlot11EW();
	virtual void bfmeSlot12EW();
	virtual void bfmeSlot13EW();
	virtual void bfmeSlot14EW();
	virtual void bfmeSlot15EW();
	virtual void bfmeSlot16EW();
	virtual void bfmeSlot17EW();
	virtual void bfmeSlot18EW();
	virtual void bfmeSlot19EW();
	virtual void bfmeSlot20EW();
	virtual void bfmeApplyEW(BfmeSubETH *p);
};

class BfmeViewETH
{
public:
	void bfmeApplyETH(BfmeSubETH *p);

	unsigned char m_bfmeHeadEW[0xc];
	float m_bfmeXEW;
	float m_bfmeYEW;
	unsigned char m_bfmeGap0EW[0x30];
	unsigned char m_bfmeFlagEW;
	unsigned char m_bfmeGap1EW[0xbf];
	RenderObjClass *m_bfmeRenderEW;
	unsigned char m_bfmeGap2EW[0x23b0];
	BfmeSubEW m_bfmeSubEW;
};

void BfmeViewETH::bfmeApplyETH(BfmeSubETH *p)
{
	if (m_bfmeFlagEW)
	{
		Vector3 pos = m_bfmeRenderEW->Get_Position();
		pos.Z = 0.0f;
		pos = pos - Vector3(m_bfmeXEW, m_bfmeYEW, 0.0f);
		pos *= 0.25f;
		p->m_x += pos.X;
		p->m_y += pos.Y;
		m_bfmeSubEW.bfmeApplyEW(p);
		p->m_x -= pos.X;
		p->m_y -= pos.Y;
	}
}
