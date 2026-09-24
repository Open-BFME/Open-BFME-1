// cl: /DNDEBUG /MD /EHsc /I Code/Libraries/Source/WWVegas/WWLib /I Code/Libraries/Source/WWVegas/WWMath /I Code/Libraries/Source/WWVegas/WWDebug /I Code/Libraries/Source/WWVegas/WWSaveLoad /I Code/Libraries/Include
// Sky-box Z rotation setter at retail 0x007A15A0, called by the SkyboxSettings
// chunk parser at 0x007A5BA0; the owner keeps its address-qualified method name.

#include "matrix3.h"
#include "matrix3d.h"

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
		Matrix3 rotationMatrix;
		rotationMatrix.Make_Identity();
		rotationMatrix[0][0] *= scale;
		rotationMatrix[0][1] *= scale;
		rotationMatrix[0][2] *= scale;
		rotationMatrix[1][0] *= scale;
		rotationMatrix[1][1] *= scale;
		rotationMatrix[1][2] *= scale;
		rotationMatrix[2][0] *= scale;
		rotationMatrix[2][1] *= scale;
		rotationMatrix[2][2] *= scale;
		rotationMatrix.Rotate_Z(*rotation);
		transform.Set_Rotation(rotationMatrix);
		skyBox->Set_Transform(transform);
	}
}
