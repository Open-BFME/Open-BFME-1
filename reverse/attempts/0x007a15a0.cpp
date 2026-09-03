// ?setSkyBoxRotation007A15A0@WaterSkyBoxSettingsOwner@@QAEXPBM@Z
// partial score=0.6 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc

#include <math.h>

extern const float BfmeZeroRange;

class Matrix3
{
public:
	float row[3][3];

	__forceinline Matrix3(void) {}

	__forceinline Matrix3(float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22)
	{
		row[0][0] = m00;
		row[0][1] = m01;
		row[0][2] = m02;
		row[1][0] = m10;
		row[1][1] = m11;
		row[1][2] = m12;
		row[2][0] = m20;
		row[2][1] = m21;
		row[2][2] = m22;
	}

	__forceinline void Set(float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22)
	{
		row[0][0] = m00;
		row[0][1] = m01;
		row[0][2] = m02;
		row[1][0] = m10;
		row[1][1] = m11;
		row[1][2] = m12;
		row[2][0] = m20;
		row[2][1] = m21;
		row[2][2] = m22;
	}

	__forceinline void Rotate_Z(float theta)
	{
		Rotate_Z(sinf(theta), cosf(theta));
	}

	__forceinline void Rotate_Z(float s, float c)
	{
		float tmp1,tmp2;

		tmp1 = row[0][0];
		tmp2 = row[0][1];
		row[0][0] = (float)(c * tmp1 + s * tmp2);
		row[0][1] = (float)(-s * tmp1 + c * tmp2);

		tmp1 = row[1][0];
		tmp2 = row[1][1];
		row[1][0] = (float)(c * tmp1 + s * tmp2);
		row[1][1] = (float)(-s * tmp1 + c * tmp2);

		tmp1 = row[2][0];
		tmp2 = row[2][1];
		row[2][0] = (float)(c * tmp1 + s * tmp2);
		row[2][1] = (float)(-s * tmp1 + c * tmp2);
	}
};

class Matrix3D
{
public:
	Matrix3D(const Matrix3D &that)
	{
		row[0][0] = that.row[0][0];
		row[0][1] = that.row[0][1];
		row[0][2] = that.row[0][2];
		row[0][3] = that.row[0][3];
		row[1][0] = that.row[1][0];
		row[1][1] = that.row[1][1];
		row[1][2] = that.row[1][2];
		row[1][3] = that.row[1][3];
		row[2][0] = that.row[2][0];
		row[2][1] = that.row[2][1];
		row[2][2] = that.row[2][2];
		row[2][3] = that.row[2][3];
	}

	void Set_Rotation(const Matrix3 &rotation);

	float row[3][4];
};

#define SKYBOX_SLOT(n) virtual void slot##n();
class SkyBoxRenderObject
{
public:
	SKYBOX_SLOT(0) SKYBOX_SLOT(1) SKYBOX_SLOT(2) SKYBOX_SLOT(3)
	SKYBOX_SLOT(4) SKYBOX_SLOT(5) SKYBOX_SLOT(6) SKYBOX_SLOT(7)
	SKYBOX_SLOT(8) SKYBOX_SLOT(9) SKYBOX_SLOT(10) SKYBOX_SLOT(11)
	SKYBOX_SLOT(12) SKYBOX_SLOT(13) SKYBOX_SLOT(14) SKYBOX_SLOT(15)
	SKYBOX_SLOT(16) SKYBOX_SLOT(17) SKYBOX_SLOT(18) SKYBOX_SLOT(19)
	virtual void Validate_Transform() const;
	virtual void Set_Transform(const Matrix3D &transform);
	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return transform;
	}
	unsigned char beforeTransform[0x14];
	Matrix3D transform;
	float objectScale;
};
#undef SKYBOX_SLOT

class WaterSkyBoxSettingsOwner
{
public:
	void setSkyBoxRotation007A15A0(const float *rotation);
	unsigned char beforeSkyBox[0x250];
	SkyBoxRenderObject *skyBox;
};

void WaterSkyBoxSettingsOwner::setSkyBoxRotation007A15A0(const float *rotation)
{
	if (skyBox != 0) {
		Matrix3D transform = skyBox->Get_Transform();
		float scale = skyBox->objectScale;
		Matrix3 rotationMatrix(scale,
			scale * BfmeZeroRange,
			scale * BfmeZeroRange,
			scale * BfmeZeroRange,
			scale,
			scale * BfmeZeroRange,
			scale * BfmeZeroRange,
			scale * BfmeZeroRange,
			scale);
		rotationMatrix.Rotate_Z(*rotation);
		transform.Set_Rotation(rotationMatrix);
		skyBox->Set_Transform(transform);
	}
}
