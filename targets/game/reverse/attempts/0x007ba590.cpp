// ?updateOptimalExtrusionPadding@W3DVolumetricShadow@@IAEXXZ
// partial score=0.9947 date=2026-10-01
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
// ?updateOptimalExtrusionPadding@W3DVolumetricShadow@@IAEXXZ
// Retail 0x007BA590, 760 bytes. Identity: W3DVolumetricShadow::Update
// (0x007BF7D0) does `if (m_extraExtrusionPadding == 0) call ILT 0x00042127
// (-> 0x007BA590); updateVolumes(m_extraExtrusionPadding)`, Zero Hour's
// Update line for line, and this body writes +0x7C. BFME replaced ZH's
// Cast_Ray search with a fixed 20-unit terrain walk up to 5120 per top-box
// corner (probe 200 units ahead when the sample dips under the terrain).
// Remaining four bytes: corners[0].X loads Center before Extent (retail
// loads Extent first; Y/Z match). Copying lightRay before scaling sampleStep
// fixes the sample-point store schedule without changing the 760-byte extent.
#include "rendobj.h"

typedef float Real;
struct Coord3D;

class W3DShadowManager
{
public:
	Vector3 &getLightPosWorld(int lightIndex);
};
extern W3DShadowManager *TheW3DShadowManager;

#define BHM_SLOT(n) virtual void slot##n(void);
class BaseHeightMapRenderObjClass
{
public:
	BHM_SLOT(0) BHM_SLOT(1) BHM_SLOT(2) BHM_SLOT(3) BHM_SLOT(4) BHM_SLOT(5) BHM_SLOT(6) BHM_SLOT(7)
	BHM_SLOT(8) BHM_SLOT(9) BHM_SLOT(10) BHM_SLOT(11) BHM_SLOT(12) BHM_SLOT(13) BHM_SLOT(14) BHM_SLOT(15)
	BHM_SLOT(16) BHM_SLOT(17) BHM_SLOT(18) BHM_SLOT(19) BHM_SLOT(20) BHM_SLOT(21) BHM_SLOT(22) BHM_SLOT(23)
	BHM_SLOT(24) BHM_SLOT(25) BHM_SLOT(26) BHM_SLOT(27) BHM_SLOT(28) BHM_SLOT(29) BHM_SLOT(30) BHM_SLOT(31)
	BHM_SLOT(32) BHM_SLOT(33) BHM_SLOT(34) BHM_SLOT(35) BHM_SLOT(36) BHM_SLOT(37) BHM_SLOT(38) BHM_SLOT(39)
	BHM_SLOT(40) BHM_SLOT(41) BHM_SLOT(42) BHM_SLOT(43) BHM_SLOT(44) BHM_SLOT(45) BHM_SLOT(46) BHM_SLOT(47)
	BHM_SLOT(48) BHM_SLOT(49) BHM_SLOT(50) BHM_SLOT(51) BHM_SLOT(52) BHM_SLOT(53) BHM_SLOT(54) BHM_SLOT(55)
	BHM_SLOT(56) BHM_SLOT(57) BHM_SLOT(58) BHM_SLOT(59) BHM_SLOT(60) BHM_SLOT(61) BHM_SLOT(62) BHM_SLOT(63)
	BHM_SLOT(64) BHM_SLOT(65) BHM_SLOT(66) BHM_SLOT(67) BHM_SLOT(68) BHM_SLOT(69) BHM_SLOT(70) BHM_SLOT(71)
	BHM_SLOT(72) BHM_SLOT(73) BHM_SLOT(74) BHM_SLOT(75) BHM_SLOT(76) BHM_SLOT(77) BHM_SLOT(78) BHM_SLOT(79)
	BHM_SLOT(80) BHM_SLOT(81) BHM_SLOT(82) BHM_SLOT(83) BHM_SLOT(84) BHM_SLOT(85) BHM_SLOT(86) BHM_SLOT(87)
	BHM_SLOT(88) BHM_SLOT(89) BHM_SLOT(90) BHM_SLOT(91) BHM_SLOT(92) BHM_SLOT(93) BHM_SLOT(94) BHM_SLOT(95)
	BHM_SLOT(96) BHM_SLOT(97) BHM_SLOT(98) BHM_SLOT(99) BHM_SLOT(100) BHM_SLOT(101) BHM_SLOT(102) BHM_SLOT(103)
	BHM_SLOT(104) BHM_SLOT(105) BHM_SLOT(106) BHM_SLOT(107) BHM_SLOT(108) BHM_SLOT(109) BHM_SLOT(110) BHM_SLOT(111)
	BHM_SLOT(112) BHM_SLOT(113) BHM_SLOT(114) BHM_SLOT(115) BHM_SLOT(116) BHM_SLOT(117) BHM_SLOT(118) BHM_SLOT(119)
	BHM_SLOT(120) BHM_SLOT(121) BHM_SLOT(122) BHM_SLOT(123) BHM_SLOT(124) BHM_SLOT(125) BHM_SLOT(126) BHM_SLOT(127)
	BHM_SLOT(128) BHM_SLOT(129) BHM_SLOT(130) BHM_SLOT(131) BHM_SLOT(132) BHM_SLOT(133) BHM_SLOT(134) BHM_SLOT(135)
	BHM_SLOT(136) BHM_SLOT(137) BHM_SLOT(138) BHM_SLOT(139) BHM_SLOT(140) BHM_SLOT(141) BHM_SLOT(142) BHM_SLOT(143)
	BHM_SLOT(144) BHM_SLOT(145)
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;
};
#undef BHM_SLOT
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DVolumetricShadow
{
protected:
	void updateOptimalExtrusionPadding(void);

private:
	char m_unmodelled00[0x70];
	RenderObjClass *m_robj;
	Real m_shadowLengthScale;
	Real m_robjExtent;
	Real m_extraExtrusionPadding;
};

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

		corners[0] = box.Center + box.Extent;
		corners[1] = corners[0];
		corners[1].X -= 2.0f * box.Extent.X;
		corners[2] = corners[1];
		corners[2].Y -= 2.0f * box.Extent.Y;
		corners[3] = corners[2];
		corners[3].X += 2.0f * box.Extent.X;

		for (int i = 0; i < 4; i++)
		{
			Vector3 lightRay = corners[i] - lightPosWorld;
			lightRay.Normalize();

			Vector3 samplePoint = corners[i];
			Vector3 sampleStep = lightRay;
			sampleStep *= 20.0f;
			Vector3 shadowRay = lightRay * 200.0f;
			Real length = 20.0f;
			do
			{
				samplePoint += sampleStep;
				Real height = TheTerrainRenderObject->getHeightMapHeight(samplePoint.X, samplePoint.Y, NULL);
				if (samplePoint.Z < height)
				{
					Vector3 shadowPoint = samplePoint + shadowRay;
					if (TheTerrainRenderObject->getHeightMapHeight(shadowPoint.X, shadowPoint.Y, NULL) < shadowPoint.Z)
						break;
				}
				if (height < baseGroundHeight)
					baseGroundHeight = height;
				length += 20.0f;
			} while (length < 5120.0f);
		}

		m_extraExtrusionPadding = objPos.Z - baseGroundHeight + 0.1f;
	}
}
