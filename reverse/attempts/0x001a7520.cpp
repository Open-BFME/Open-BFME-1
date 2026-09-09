// ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z
// partial score=0.62 date=2026-09-09
// cl: /DNDEBUG /MD /EHs-c-
// Bridge::getBridgeHeight, retail 0x001A7520 size 664.
//
// ZH source: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// (Bridge::getBridgeHeight) -- the m_extra==0 "else" branch below is that ZH body near-verbatim.
// BFME added the m_extra!=0 slope branch; the m_extra offset (+0x8c) is cross-validated against
// the landed sibling Code/GameEngine/Source/GameLogic/Map/BridgeIsPointOnBridge.cpp, whose
// BridgePointOnBridgeShim class collapses m_from/m_to/m_bridgeWidth into one infoPad[0x1C] but
// otherwise shares this exact member layout through m_extra.
//
// Coord3D::normalize / PlaneClass::Set / PlaneClass::Compute_Intersection are declared WITHOUT
// bodies (matching retail, which calls all three out of line through an ICF-folded j_ thunk --
// confirmed in the disassembly at +0x112/+0x11b and the plane-path calls at +0x225/+0x266). The
// real WWMath headers define these inline, which the compiler WOULD inline here and produce a
// different, larger instruction stream (tried: regressed 652B -> 633B); the declare-only shim
// keeps retail's real-call shape.
//
// Named float constants confirmed by reading the retail image directly (not literals -- retail
// loads all three through memory operands, not FPU immediates): BfmeShadowScale (VA 0x0109BF3C)
// = -1.0f, BfmeZeroRange (VA 0x01075350) = 0.0f, g_bfmeDefaultBU (VA 0x01075334) = 1.0f. All
// three are already declared/pinned elsewhere in Code/ (grep BfmeShadowScale/BfmeZeroRange/
// g_bfmeDefaultBU); reusing the same extern spelling here so the compiled body references the
// same relocations retail does instead of materialising -1.0f/0.0f/1.0f as inline immediates.
//
// The slope branch reuses ONE packed scratch struct (Align34, matching retail's stack-slot
// reuse: nFrom/gap/nTo/scratch/tmp share the SAME memory the plane-path below also reuses)
// rather than separate named locals -- separate locals compiled 44B over target; the packed
// struct is what gets retail's tighter stack frame (sub esp,0x34).

extern const float BfmeShadowScale;
extern const float BfmeZeroRange;
extern const float g_bfmeDefaultBU;

struct Coord3D
{
	float x;
	float y;
	float z;
	void normalize();
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class PlaneClass
{
public:
	Vector3 N;
	float D;

	void Set(const Vector3 &point1, const Vector3 &point2, const Vector3 &point3);
	bool Compute_Intersection(const Vector3 &p0, const Vector3 &p1, float *set_t) const;
};

class Bridge
{
public:
	float getBridgeHeight(const Coord3D *pLoc, Coord3D *normal);

private:
	void *m_vptr;
	void *m_next;
	void *m_templateName;
	Coord3D m_from;
	Coord3D m_to;
	float m_bridgeWidth;
	Coord3D m_fromLeft;
	Coord3D m_fromRight;
	Coord3D m_toLeft;
	Coord3D m_toRight;
	char m_infoTail[0x78 - 0x58];
	char m_bounds[0x10];
	int m_layer;
	void *m_extra;
};

struct Align34
{
	Coord3D nFrom;
	float gap;
	Coord3D nTo;
	Vector3 scratch;
	float tmp;
	float pad[2];
};

float Bridge::getBridgeHeight(const Coord3D *pLoc, Coord3D *normal)
{
	Align34 f;
	if (m_extra)
	{
		Coord3D *toPtr = &m_to;
		f.scratch = *reinterpret_cast<Vector3 *>(toPtr);
		float alongX = f.scratch.X - m_from.x;
		float alongY = f.scratch.Y - m_from.y;
		f.nFrom.x = m_fromRight.y;
		f.nFrom.z = 0.0f;
		f.tmp = m_fromRight.x - m_fromLeft.x;
		f.nTo.z = 0.0f;
		f.nFrom.y = f.tmp;
		f.nFrom.x = f.nFrom.x - m_fromLeft.y;
		f.nTo.y = m_toRight.y;
		f.scratch.X = m_toRight.x - m_toLeft.x;
		f.scratch.Y = f.nTo.y - m_toLeft.y;
		f.nTo.x = f.scratch.Y;
		f.nFrom.x = -f.nFrom.x;
		f.nTo.y = -f.scratch.X;
		if (f.nFrom.x * alongX + f.nFrom.y * alongY < BfmeZeroRange)
		{
			f.nFrom.z = -0.0f;
			f.nFrom.x = f.nFrom.x * BfmeShadowScale;
			f.nFrom.y = f.tmp * BfmeShadowScale;
		}
		if (f.nTo.x * alongX + f.nTo.y * alongY > BfmeZeroRange)
		{
			f.nTo.z = -0.0f;
			f.nTo.x = f.scratch.Y * BfmeShadowScale;
			f.nTo.y = f.nTo.y * BfmeShadowScale;
		}
		f.nFrom.normalize();
		f.nTo.normalize();
		f.tmp = f.nFrom.x * (pLoc->x - m_from.x) + f.nFrom.y * (pLoc->y - m_from.y);
		f.gap = f.nTo.x * (pLoc->x - toPtr->x) + f.nTo.y * (pLoc->y - toPtr->y);
		f.scratch.X = g_bfmeDefaultBU / (f.tmp + f.gap);
		f.scratch.Y = f.scratch.X * f.tmp;
		f.scratch.Z = f.scratch.X * f.gap;
		f.tmp = (m_to.z + (m_from.z - m_to.z) * f.scratch.Z) * (g_bfmeDefaultBU - f.scratch.Z)
			+ (m_from.z + (m_to.z - m_from.z) * f.scratch.Y) * (g_bfmeDefaultBU - f.scratch.Y);
		if (normal)
		{
			normal->x = 0.0f;
			normal->y = 0.0f;
			normal->z = 1.0f;
		}
		return f.tmp;
	}

	{
		char *base = reinterpret_cast<char *>(&f);
		Vector3 &left1 = *reinterpret_cast<Vector3 *>(base + 0x10);
		Vector3 &right1 = *reinterpret_cast<Vector3 *>(base + 0x1c);
		Vector3 &left2 = *reinterpret_cast<Vector3 *>(base + 0x28);
		PlaneClass &plane = *reinterpret_cast<PlaneClass *>(base + 0x0c);
		left1 = *reinterpret_cast<Vector3 *>(&m_fromLeft);
		right1 = *reinterpret_cast<Vector3 *>(&m_fromRight);
		left2 = *reinterpret_cast<Vector3 *>(&m_toLeft);
		plane.Set(left1, right1, left2);
		right1.X = pLoc->x;
		left2.X = pLoc->x;
		right1.Y = pLoc->y;
		left2.Y = pLoc->y;
		right1.Z = 0.0f;
		left2.Z = 1000.0f;
		plane.Compute_Intersection(right1, left2, &f.tmp);
		if (normal)
		{
			normal->x = plane.N.X;
			normal->y = plane.N.Y;
			normal->z = plane.N.Z;
		}
		return f.tmp * 1000.0f;
	}
}
