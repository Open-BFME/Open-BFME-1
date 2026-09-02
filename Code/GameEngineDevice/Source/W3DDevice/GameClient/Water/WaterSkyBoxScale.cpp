// Clean reconstruction of the sky-box rescale helper at 0x0079F1E0.

struct Rva0079F1E0Matrix3D
{
	float value[3][4];
};

#define RVA0079F1E0_SLOT(n) virtual void slot##n();

class Rva0079F1E0RenderObj
{
public:
	RVA0079F1E0_SLOT(0) RVA0079F1E0_SLOT(1) RVA0079F1E0_SLOT(2) RVA0079F1E0_SLOT(3)
	RVA0079F1E0_SLOT(4) RVA0079F1E0_SLOT(5) RVA0079F1E0_SLOT(6) RVA0079F1E0_SLOT(7)
	RVA0079F1E0_SLOT(8) RVA0079F1E0_SLOT(9) RVA0079F1E0_SLOT(10) RVA0079F1E0_SLOT(11)
	RVA0079F1E0_SLOT(12) RVA0079F1E0_SLOT(13) RVA0079F1E0_SLOT(14) RVA0079F1E0_SLOT(15)
	RVA0079F1E0_SLOT(16) RVA0079F1E0_SLOT(17) RVA0079F1E0_SLOT(18) RVA0079F1E0_SLOT(19)
	virtual void validateTransform();
	virtual void setTransform(const Rva0079F1E0Matrix3D &transform);
	RVA0079F1E0_SLOT(22) RVA0079F1E0_SLOT(23) RVA0079F1E0_SLOT(24) RVA0079F1E0_SLOT(25)
	RVA0079F1E0_SLOT(26) RVA0079F1E0_SLOT(27) RVA0079F1E0_SLOT(28) RVA0079F1E0_SLOT(29)
	RVA0079F1E0_SLOT(30) RVA0079F1E0_SLOT(31) RVA0079F1E0_SLOT(32) RVA0079F1E0_SLOT(33)
	RVA0079F1E0_SLOT(34) RVA0079F1E0_SLOT(35) RVA0079F1E0_SLOT(36) RVA0079F1E0_SLOT(37)
	RVA0079F1E0_SLOT(38) RVA0079F1E0_SLOT(39) RVA0079F1E0_SLOT(40) RVA0079F1E0_SLOT(41)
	RVA0079F1E0_SLOT(42) RVA0079F1E0_SLOT(43) RVA0079F1E0_SLOT(44) RVA0079F1E0_SLOT(45)
	RVA0079F1E0_SLOT(46) RVA0079F1E0_SLOT(47) RVA0079F1E0_SLOT(48) RVA0079F1E0_SLOT(49)
	RVA0079F1E0_SLOT(50) RVA0079F1E0_SLOT(51) RVA0079F1E0_SLOT(52) RVA0079F1E0_SLOT(53)
	RVA0079F1E0_SLOT(54) RVA0079F1E0_SLOT(55) RVA0079F1E0_SLOT(56) RVA0079F1E0_SLOT(57)
	RVA0079F1E0_SLOT(58) RVA0079F1E0_SLOT(59) RVA0079F1E0_SLOT(60) RVA0079F1E0_SLOT(61)
	RVA0079F1E0_SLOT(62) RVA0079F1E0_SLOT(63) RVA0079F1E0_SLOT(64) RVA0079F1E0_SLOT(65)
	RVA0079F1E0_SLOT(66) RVA0079F1E0_SLOT(67) RVA0079F1E0_SLOT(68) RVA0079F1E0_SLOT(69)
	RVA0079F1E0_SLOT(70) RVA0079F1E0_SLOT(71) RVA0079F1E0_SLOT(72) RVA0079F1E0_SLOT(73)
	RVA0079F1E0_SLOT(74) RVA0079F1E0_SLOT(75) RVA0079F1E0_SLOT(76) RVA0079F1E0_SLOT(77)
	RVA0079F1E0_SLOT(78) RVA0079F1E0_SLOT(79) RVA0079F1E0_SLOT(80) RVA0079F1E0_SLOT(81)
	RVA0079F1E0_SLOT(82) RVA0079F1E0_SLOT(83) RVA0079F1E0_SLOT(84) RVA0079F1E0_SLOT(85)
	RVA0079F1E0_SLOT(86) RVA0079F1E0_SLOT(87) RVA0079F1E0_SLOT(88) RVA0079F1E0_SLOT(89)
	RVA0079F1E0_SLOT(90) RVA0079F1E0_SLOT(91)
	virtual void setObjectScale(float scale);
	unsigned char pad04[0x14];
	Rva0079F1E0Matrix3D transform;
	float objectScale;
};

class WaterSkyBoxScaleOwner
{
public:
	void setSkyBoxScale(const float *scale);

private:
	unsigned char pad00[0x250];
	Rva0079F1E0RenderObj *skyBox;
};

void WaterSkyBoxScaleOwner::setSkyBoxScale(const float *scale)
{
	Rva0079F1E0RenderObj *object = skyBox;
	if (object == 0) {
		return;
	}

	float oldScale = object->objectScale;
	float difference = *scale - oldScale;
	*(unsigned int *)&difference &= 0x7fffffff;
	if (!(difference > 0.01f)) {
		return;
	}

	object->validateTransform();
	float factor = *scale / oldScale;
	Rva0079F1E0Matrix3D transform;
	transform.value[0][0] = object->transform.value[0][0];
	transform.value[0][1] = object->transform.value[0][1];
	transform.value[0][2] = object->transform.value[0][2];
	transform.value[0][3] = object->transform.value[0][3];
	transform.value[1][0] = object->transform.value[1][0];
	transform.value[1][1] = object->transform.value[1][1];
	transform.value[1][2] = object->transform.value[1][2];
	transform.value[1][3] = object->transform.value[1][3];
	transform.value[2][0] = object->transform.value[2][0];
	transform.value[2][1] = object->transform.value[2][1];
	transform.value[2][2] = object->transform.value[2][2];
	transform.value[2][3] = object->transform.value[2][3];

	transform.value[0][0] *= factor;
	transform.value[1][0] *= factor;
	transform.value[2][0] *= factor;
	transform.value[0][1] *= factor;
	transform.value[1][1] *= factor;
	transform.value[2][1] *= factor;
	transform.value[0][2] *= factor;
	transform.value[1][2] *= factor;
	transform.value[2][2] *= factor;

	skyBox->setObjectScale(*scale);
	skyBox->setTransform(transform);
}

#undef RVA0079F1E0_SLOT
