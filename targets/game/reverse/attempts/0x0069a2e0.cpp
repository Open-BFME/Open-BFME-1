// ?refresh0069A2E0@Rva0069A2E0Owner@@QAEXXZ
// partial score=0.26 date=2026-09-23
// ?refresh0069A2E0@Rva0069A2E0Owner@@QAEXXZ
// Opaque thiscall body; virtual slots, fields, imports, and attenuation helper are instruction-derived.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /FAsc /Fabuild/worker-0069a2e0/trials/trial-08.cod

extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_orientation(
	void *listener, float x, float y, float z, float upX, float upY, float upZ);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_position(
	void *listener, float x, float y, float z);
extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

extern float g_bfmeDefaultBU;
extern const float BfmeZeroRange;

struct Rva0069A2E0Vec3
{
	float x;
	float y;
	float z;
};

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

class Rva0069A2E0Owner
{
public:
#define RVA0069A2E0_SLOT(n) virtual void v##n() = 0;
	RVA0069A2E0_SLOT(00) RVA0069A2E0_SLOT(01) RVA0069A2E0_SLOT(02) RVA0069A2E0_SLOT(03)
	RVA0069A2E0_SLOT(04) RVA0069A2E0_SLOT(05) RVA0069A2E0_SLOT(06) RVA0069A2E0_SLOT(07)
	RVA0069A2E0_SLOT(08) RVA0069A2E0_SLOT(09) RVA0069A2E0_SLOT(10) RVA0069A2E0_SLOT(11)
	RVA0069A2E0_SLOT(12) RVA0069A2E0_SLOT(13) RVA0069A2E0_SLOT(14) RVA0069A2E0_SLOT(15)
	RVA0069A2E0_SLOT(16) RVA0069A2E0_SLOT(17) RVA0069A2E0_SLOT(18) RVA0069A2E0_SLOT(19)
	RVA0069A2E0_SLOT(20) RVA0069A2E0_SLOT(21) RVA0069A2E0_SLOT(22) RVA0069A2E0_SLOT(23)
	RVA0069A2E0_SLOT(24) RVA0069A2E0_SLOT(25) RVA0069A2E0_SLOT(26) RVA0069A2E0_SLOT(27)
	RVA0069A2E0_SLOT(28) RVA0069A2E0_SLOT(29) RVA0069A2E0_SLOT(30) RVA0069A2E0_SLOT(31)
	RVA0069A2E0_SLOT(32) RVA0069A2E0_SLOT(33) RVA0069A2E0_SLOT(34) RVA0069A2E0_SLOT(35)
	RVA0069A2E0_SLOT(36) RVA0069A2E0_SLOT(37) RVA0069A2E0_SLOT(38) RVA0069A2E0_SLOT(39)
	RVA0069A2E0_SLOT(40) RVA0069A2E0_SLOT(41) RVA0069A2E0_SLOT(42) RVA0069A2E0_SLOT(43)
	RVA0069A2E0_SLOT(44) RVA0069A2E0_SLOT(45) RVA0069A2E0_SLOT(46) RVA0069A2E0_SLOT(47)
	RVA0069A2E0_SLOT(48) RVA0069A2E0_SLOT(49) RVA0069A2E0_SLOT(50) RVA0069A2E0_SLOT(51)
	RVA0069A2E0_SLOT(52) RVA0069A2E0_SLOT(53) RVA0069A2E0_SLOT(54) RVA0069A2E0_SLOT(55)
	RVA0069A2E0_SLOT(56) RVA0069A2E0_SLOT(57) RVA0069A2E0_SLOT(58) RVA0069A2E0_SLOT(59)
	RVA0069A2E0_SLOT(60) RVA0069A2E0_SLOT(61) RVA0069A2E0_SLOT(62) RVA0069A2E0_SLOT(63)
	RVA0069A2E0_SLOT(64) RVA0069A2E0_SLOT(65) RVA0069A2E0_SLOT(66) RVA0069A2E0_SLOT(67)
	RVA0069A2E0_SLOT(68) RVA0069A2E0_SLOT(69) RVA0069A2E0_SLOT(70) RVA0069A2E0_SLOT(71)
	RVA0069A2E0_SLOT(72) RVA0069A2E0_SLOT(73) RVA0069A2E0_SLOT(74) RVA0069A2E0_SLOT(75)
	RVA0069A2E0_SLOT(76) RVA0069A2E0_SLOT(77) RVA0069A2E0_SLOT(78) RVA0069A2E0_SLOT(79)
	RVA0069A2E0_SLOT(80) RVA0069A2E0_SLOT(81) RVA0069A2E0_SLOT(82) RVA0069A2E0_SLOT(83)
	RVA0069A2E0_SLOT(84) RVA0069A2E0_SLOT(85) RVA0069A2E0_SLOT(86) RVA0069A2E0_SLOT(87)
	RVA0069A2E0_SLOT(88) RVA0069A2E0_SLOT(89) RVA0069A2E0_SLOT(90) RVA0069A2E0_SLOT(91)
	RVA0069A2E0_SLOT(92) RVA0069A2E0_SLOT(93) RVA0069A2E0_SLOT(94)
#undef RVA0069A2E0_SLOT
	virtual void getModePosition(Rva0069A2E0Vec3 *out) = 0;
	virtual bool getScreenCenterWorld(Rva0069A2E0Vec3 *out) = 0;
	void refresh0069A2E0();
};

void Rva0069A2E0Owner::refresh0069A2E0()
{
	float *self = (float *)this;
	float *profile = (float *)((char *)*(void **)((char *)this + 0x0c) + 0xa8 +
		*(int *)((char *)this + 0x604) * 0x30);
	Rva0069A2E0Vec3 position = { 0.0f, 0.0f, 0.0f };
	Rva0069A2E0Vec3 center = { 0.0f, 0.0f, 0.0f };
	bool hasCenter;

	getModePosition(&position);
	hasCenter = getScreenCenterWorld(&center);
	if (position.x == self[0x2c / 4] && position.y == self[0x30 / 4] && position.z == self[0x34 / 4] &&
		center.x == self[0x38 / 4] && center.y == self[0x3c / 4] && center.z == self[0x40 / 4])
		return;

	self[0x2c / 4] = position.x;
	self[0x30 / 4] = position.y;
	self[0x34 / 4] = position.z;
	self[0x38 / 4] = center.x;
	self[0x3c / 4] = center.y;
	self[0x40 / 4] = center.z;

	float delta[3];
	delta[0] = position.x - center.x;
	delta[1] = position.y - center.y;
	delta[2] = position.z - center.z;
	float distanceSquared = delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];
	float scaledDistance = distanceSquared * profile[1];
	float fraction;
	if (scaledDistance >= profile[5])
		fraction = profile[4] / (float)sqrt((double)distanceSquared);
	else if (distanceSquared <= profile[3])
		fraction = g_bfmeDefaultBU;
	else if (scaledDistance > profile[3])
		fraction = 1.0f;
	else
		fraction = profile[2] / (float)sqrt((double)distanceSquared);

	float scale = profile[0] * fraction;
	float positionX = position.x - delta[0] * scale;
	float positionY = position.y - delta[1] * scale;
	float positionZ = position.z - delta[2] * scale;
	if (hasCenter)
	{
		positionX += (center.x - positionX) * profile[6];
		positionY += (center.y - positionY) * profile[6];
	}
	self[0x14 / 4] = positionX;
	self[0x18 / 4] = positionY;
	self[0x1c / 4] = positionZ;

	float directionX = -delta[0];
	float directionY = -delta[1];
	float directionLength = (float)sqrt((double)(directionX * directionX + directionY * directionY));
	if (directionLength != BfmeZeroRange)
	{
		float inverseLength = g_bfmeDefaultBU / directionLength;
		directionX *= inverseLength;
		directionY *= inverseLength;
	}
	self[0x20 / 4] = directionX;
	self[0x24 / 4] = directionY;
	self[0x28 / 4] = 0.0f;

	void *listener = *(void **)((char *)this + 0x964);
	if (listener)
	{
		AIL_set_3D_orientation(listener, self[0x20 / 4], self[0x24 / 4], -self[0x28 / 4], 0.0f, 0.0f, -1.0f);
		AIL_set_3D_position(listener, self[0x14 / 4], self[0x18 / 4], -self[0x1c / 4]);
	}

	Rva006995F0Vec3 offset;
	offset.x = position.x - self[0x14 / 4];
	offset.y = position.y - self[0x18 / 4];
	offset.z = position.z - self[0x1c / 4];
	Rva006995F0Owner *channel = (Rva006995F0Owner *)((char *)this + 0xb8 +
		*(int *)((char *)this + 0x604) * 0x1c4);
	channel->attenuate((Rva006995F0Range *)profile, &offset);
}
