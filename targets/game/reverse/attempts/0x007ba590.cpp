// ?updateOptimalExtrusionPadding@W3DVolumetricShadow@@IAEXXZ
// partial score=0.56 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

#include <math.h>

typedef float Real;

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;

	__forceinline Vector3(void) {}
	__forceinline Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	__forceinline Vector3 &operator-=(const Vector3 &v) { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
	__forceinline Vector3 &operator*=(Real scale) { X *= scale; Y *= scale; Z *= scale; return *this; }
	__forceinline Real Length2(void) const { return X * X + Y * Y + Z * Z; }
};

static __forceinline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

static __forceinline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

static __forceinline Vector3 operator*(const Vector3 &a, Real scale)
{
	return Vector3(a.X * scale, a.Y * scale, a.Z * scale);
}

class W3DShadowManager
{
public:
	Vector3 &getLightPosWorld(int index);
};

extern W3DShadowManager *TheW3DShadowManager;

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

#define RVO_DUMMY(n) virtual void v##n(void);
class RenderObjClass
{
public:
	RVO_DUMMY(0) RVO_DUMMY(1) RVO_DUMMY(2) RVO_DUMMY(3)
	RVO_DUMMY(4) RVO_DUMMY(5) RVO_DUMMY(6) RVO_DUMMY(7)
	RVO_DUMMY(8) RVO_DUMMY(9) RVO_DUMMY(10) RVO_DUMMY(11)
	RVO_DUMMY(12) RVO_DUMMY(13) RVO_DUMMY(14) RVO_DUMMY(15)
	RVO_DUMMY(16) RVO_DUMMY(17) RVO_DUMMY(18) RVO_DUMMY(19)
	RVO_DUMMY(20) RVO_DUMMY(21) RVO_DUMMY(22) RVO_DUMMY(23)
	RVO_DUMMY(24) RVO_DUMMY(25) RVO_DUMMY(26) RVO_DUMMY(27)
	RVO_DUMMY(28) RVO_DUMMY(29) RVO_DUMMY(30) RVO_DUMMY(31)
	RVO_DUMMY(32) RVO_DUMMY(33) RVO_DUMMY(34) RVO_DUMMY(35)
	RVO_DUMMY(36) RVO_DUMMY(37) RVO_DUMMY(38) RVO_DUMMY(39)
	RVO_DUMMY(40) RVO_DUMMY(41) RVO_DUMMY(42) RVO_DUMMY(43)
	RVO_DUMMY(44) RVO_DUMMY(45) RVO_DUMMY(46) RVO_DUMMY(47)
	RVO_DUMMY(48) RVO_DUMMY(49) RVO_DUMMY(50) RVO_DUMMY(51)
	RVO_DUMMY(52) RVO_DUMMY(53) RVO_DUMMY(54) RVO_DUMMY(55)
	RVO_DUMMY(56) RVO_DUMMY(57) RVO_DUMMY(58) RVO_DUMMY(59)
	RVO_DUMMY(60) RVO_DUMMY(61) RVO_DUMMY(62) RVO_DUMMY(63)
	RVO_DUMMY(64)
	virtual const AABoxClass &Get_Bounding_Box(void) const;
	Vector3 Get_Position(void) const;
};
#undef RVO_DUMMY

#define HT_DUMMY(n) virtual void h##n(void);
class BaseHeightMapRenderObjClass
{
public:
	HT_DUMMY(0) HT_DUMMY(1) HT_DUMMY(2) HT_DUMMY(3)
	HT_DUMMY(4) HT_DUMMY(5) HT_DUMMY(6) HT_DUMMY(7)
	HT_DUMMY(8) HT_DUMMY(9) HT_DUMMY(10) HT_DUMMY(11)
	HT_DUMMY(12) HT_DUMMY(13) HT_DUMMY(14) HT_DUMMY(15)
	HT_DUMMY(16) HT_DUMMY(17) HT_DUMMY(18) HT_DUMMY(19)
	HT_DUMMY(20) HT_DUMMY(21) HT_DUMMY(22) HT_DUMMY(23)
	HT_DUMMY(24) HT_DUMMY(25) HT_DUMMY(26) HT_DUMMY(27)
	HT_DUMMY(28) HT_DUMMY(29) HT_DUMMY(30) HT_DUMMY(31)
	HT_DUMMY(32) HT_DUMMY(33) HT_DUMMY(34) HT_DUMMY(35)
	HT_DUMMY(36) HT_DUMMY(37) HT_DUMMY(38) HT_DUMMY(39)
	HT_DUMMY(40) HT_DUMMY(41) HT_DUMMY(42) HT_DUMMY(43)
	HT_DUMMY(44) HT_DUMMY(45) HT_DUMMY(46) HT_DUMMY(47)
	HT_DUMMY(48) HT_DUMMY(49) HT_DUMMY(50) HT_DUMMY(51)
	HT_DUMMY(52) HT_DUMMY(53) HT_DUMMY(54) HT_DUMMY(55)
	HT_DUMMY(56) HT_DUMMY(57) HT_DUMMY(58) HT_DUMMY(59)
	HT_DUMMY(60) HT_DUMMY(61) HT_DUMMY(62) HT_DUMMY(63)
	HT_DUMMY(64) HT_DUMMY(65) HT_DUMMY(66) HT_DUMMY(67)
	HT_DUMMY(68) HT_DUMMY(69) HT_DUMMY(70) HT_DUMMY(71)
	HT_DUMMY(72) HT_DUMMY(73) HT_DUMMY(74) HT_DUMMY(75)
	HT_DUMMY(76) HT_DUMMY(77) HT_DUMMY(78) HT_DUMMY(79)
	HT_DUMMY(80) HT_DUMMY(81) HT_DUMMY(82) HT_DUMMY(83)
	HT_DUMMY(84) HT_DUMMY(85) HT_DUMMY(86) HT_DUMMY(87)
	HT_DUMMY(88) HT_DUMMY(89) HT_DUMMY(90) HT_DUMMY(91)
	HT_DUMMY(92) HT_DUMMY(93) HT_DUMMY(94) HT_DUMMY(95)
	HT_DUMMY(96) HT_DUMMY(97) HT_DUMMY(98) HT_DUMMY(99)
	HT_DUMMY(100) HT_DUMMY(101) HT_DUMMY(102) HT_DUMMY(103)
	HT_DUMMY(104) HT_DUMMY(105) HT_DUMMY(106) HT_DUMMY(107)
	HT_DUMMY(108) HT_DUMMY(109) HT_DUMMY(110) HT_DUMMY(111)
	HT_DUMMY(112) HT_DUMMY(113) HT_DUMMY(114) HT_DUMMY(115)
	HT_DUMMY(116) HT_DUMMY(117) HT_DUMMY(118) HT_DUMMY(119)
	HT_DUMMY(120) HT_DUMMY(121) HT_DUMMY(122) HT_DUMMY(123)
	HT_DUMMY(124) HT_DUMMY(125) HT_DUMMY(126) HT_DUMMY(127)
	HT_DUMMY(128) HT_DUMMY(129) HT_DUMMY(130) HT_DUMMY(131)
	HT_DUMMY(132) HT_DUMMY(133) HT_DUMMY(134) HT_DUMMY(135)
	HT_DUMMY(136) HT_DUMMY(137) HT_DUMMY(138) HT_DUMMY(139)
	HT_DUMMY(140) HT_DUMMY(141) HT_DUMMY(142) HT_DUMMY(143)
	HT_DUMMY(144) HT_DUMMY(145)
	virtual Real getHeightMapHeight(Real x, Real y, void *normal) const;
};
#undef HT_DUMMY

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

#define BfmeZeroRange (*(const Real *)0x01075350)
#define BfmeSamplingInterval (*(const Real *)0x010977E0)
#define BfmeMaxExtrusionLength (*(const Real *)0x01083C44)
#define BfmeShadowLengthLimit (*(const Real *)0x011284C8)
#define g_bfmeScaleBK (*(const Real *)0x01075C70)

class WWMath
{
public:
	static Real __fastcall Inv_Sqrt(Real value);
};

class W3DVolumetricShadow
{
private:
	char m_padding[0x70];
	RenderObjClass *m_robj;
	Real m_shadowLengthScale;
	Real m_robjExtent;
	Real m_extraExtrusionPadding;

protected:
	void updateOptimalExtrusionPadding(void);
};

// ?updateOptimalExtrusionPadding@W3DVolumetricShadow@@IAEXXZ present-unmatched
void W3DVolumetricShadow::updateOptimalExtrusionPadding(void)
{
	if (m_robj)
	{
		Vector3 lightPosWorld = TheW3DShadowManager->getLightPosWorld(0);
		if (m_shadowLengthScale)
		{
			Real lightXYDistance = sqrt(lightPosWorld.X * lightPosWorld.X + lightPosWorld.Y * lightPosWorld.Y);
			Real newZ = lightXYDistance * m_shadowLengthScale;
			if (newZ > lightPosWorld.Z)
				lightPosWorld.Z = newZ;
		}

		Vector3 objPos = m_robj->Get_Position();
		Real baseGroundHeight = objPos.Z;
		const AABoxClass &box = m_robj->Get_Bounding_Box();
		Vector3 corners[4];
		corners[0] = box.Extent + box.Center;
		corners[1] = corners[0];
		corners[1].X -= 2.0f * box.Extent.X;
		corners[2] = corners[1];
		corners[2].Y -= 2.0f * box.Extent.Y;
		corners[3] = corners[2];
		corners[3].X += 2.0f * box.Extent.X;

		for (int i = 0; i < 4; ++i)
		{
			Vector3 lightRay = corners[i] - lightPosWorld;
			Real length2 = lightRay.Length2();
			if (length2 != BfmeZeroRange)
			{
				Real inverseLength = WWMath::Inv_Sqrt(length2);
				lightRay.X *= inverseLength;
				lightRay.Y *= inverseLength;
				lightRay.Z *= inverseLength;
			}

			Vector3 sampleRay = lightRay * BfmeSamplingInterval;
			Vector3 shadowRay = lightRay * BfmeMaxExtrusionLength;
			Real currentLength = BfmeSamplingInterval;
			do
			{
				Vector3 samplePoint = corners[i] + sampleRay;
				Real sampleHeight = TheTerrainRenderObject->getHeightMapHeight(samplePoint.X, samplePoint.Y, 0);
				if (sampleHeight < samplePoint.Z)
				{
					Vector3 shadowPoint = corners[i] + shadowRay;
					Real shadowHeight = TheTerrainRenderObject->getHeightMapHeight(shadowPoint.X, shadowPoint.Y, 0);
					if (shadowHeight < shadowPoint.Z && shadowHeight < baseGroundHeight)
						baseGroundHeight = shadowHeight;
				}

				currentLength += BfmeSamplingInterval;
			} while (currentLength < BfmeShadowLengthLimit);
		}

		m_extraExtrusionPadding = objPos.Z - baseGroundHeight + g_bfmeScaleBK;
	}
}
