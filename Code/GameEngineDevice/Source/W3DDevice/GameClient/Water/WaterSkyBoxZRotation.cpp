// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: clean reconstruction of the WaterRenderObjClass skybox
// Z-rotation accessor at retail 0x0079F3E0.  The address-derived method name
// remains until the BFME-only declaration is recovered.

class Matrix3D
{
public:
	Matrix3D(const Matrix3D &that)
	{
		m_rows[0] = that.m_rows[0];
		m_rows[1] = that.m_rows[1];
		m_rows[2] = that.m_rows[2];
		m_rows[3] = that.m_rows[3];
		m_rows[4] = that.m_rows[4];
		m_rows[5] = that.m_rows[5];
		m_rows[6] = that.m_rows[6];
		m_rows[7] = that.m_rows[7];
		m_rows[8] = that.m_rows[8];
		m_rows[9] = that.m_rows[9];
		m_rows[10] = that.m_rows[10];
		m_rows[11] = that.m_rows[11];
	}

	float Get_Z_Rotation(void) const;

private:
	float m_rows[12];
};

class RenderObjLayout0050
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual void bfmeSlot12(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot15(void) = 0;
	virtual void bfmeSlot16(void) = 0;
	virtual void bfmeSlot17(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot19(void) = 0;
	virtual void Validate_Transform(void) const = 0;

	const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return m_transform;
	}

private:
	unsigned char m_beforeTransform[0x14];
	Matrix3D m_transform;
};

extern const float BfmeZeroRange;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
public:
	float bfmeSkyBoxZRotation0079F3E0(void) const;

private:
	unsigned char m_beforeSkyBox[0x250];
	RenderObjLayout0050 *m_skyBox;
};

float WaterRenderObjClass::bfmeSkyBoxZRotation0079F3E0(void) const
{
	float rotation = BfmeZeroRange;
	if (m_skyBox != 0)
	{
		Matrix3D transform = m_skyBox->Get_Transform();
		rotation = transform.Get_Z_Rotation();
	}
	return rotation;
}
