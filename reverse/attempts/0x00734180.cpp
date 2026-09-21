// ?rva00734180@Rva00734180Owner@@QAEXPBVCameraClass@@@Z
// partial score=0.2 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// BFME W3DTreeBuffer camera-cull pass, retail 0x00734180 (192 bytes).
//
// Identity: the landed siblings 0x00733F50 (Rva00733F50::handle) and
// 0x00733FD0 (W3DTreeBuffer::removeTreeAtIndex) share this body's exact
// 0xE8-byte tree-record stride and +0x2A7CB0/+0x2A7CB4 numTrees/dirty pair,
// proving the owning object. The body Validate_Transform()s the passed
// CameraClass (vtable slot +0x50: vtable_lookup.py --target 0x00920270,
// the landed RenderObjClass::Validate_Transform, lands on slot +0x50 across
// every RenderObjClass-derived vtable), reads the camera's Matrix3D
// Transform directly (RenderObjClass::Get_Transform() is non-virtual and
// just returns Transform, proven at +0x18 by camera.h/rendobj.h's own BFME
// field naming: Bits+0x10, _bfme_unk_14+0x14, Transform+0x18), and calls
// CameraClass::Cull_Sphere() per tree -- inlining to the same
// Update_Frustum()+CollisionMath::Overlap_Test() pair this body performs.
// This is the same shape as ZH's W3DTreeBuffer::cull() (camera_matrix[i][2]
// scaled into m_cameraLookAtVector, m_updateAllKeys unconditionally
// cleared at the end) except retail's 192 bytes never compute a sort key
// (no Dot_Product call anywhere in the body) and advance the loop by a
// this-relative field read fresh every iteration instead of a literal 1 --
// both real divergences from the ZH twin, not translation slop, so the
// method identity stays address-derived rather than claiming "cull".
//
// zmod is folded into the named global BfmeShadowScale (already used with
// this exact `extern const float BfmeShadowScale;` spelling elsewhere,
// e.g. animobj.cpp) instead of ZH's literal -1.
//
// camera.h/colmath.h are not on this TU's include path (no reference/ -I
// list), so CameraClass/FrustumClass/SphereClass/CollisionMath are
// re-declared locally, opaque, matching only the ABI the retail callees
// need: RenderObjClass::Validate_Transform (landed 0x00920270) and
// CollisionMath::Overlap_Test (landed, colmathfrustum.cpp) are called
// through relocations, masked byte-for-byte by the gate regardless of
// where they ultimately resolve.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

extern const float BfmeShadowScale;

class FrustumClass;

class SphereClass
{
public:
	unsigned char m_opaque[1];
};

class CollisionMath
{
public:
	enum OverlapType { POS = 1, OUTSIDE = POS };
	static OverlapType Overlap_Test(const FrustumClass &frustum, const SphereClass &sphere);
};

class RenderObjClass
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void Validate_Transform(void) const;

	unsigned char m_pad0004[0x18 - 4];
	float m_transform[3][4];
};

class CameraClass : public RenderObjClass
{
public:
	const float (&Get_Transform(void) const)[3][4] { return m_transform; }

	void Update_Frustum(void) const;

	const FrustumClass &Get_Frustum_Raw(void) const
	{
		return *reinterpret_cast<const FrustumClass *>(
			reinterpret_cast<const unsigned char *>(this) + 0x104);
	}
};

class Rva00734180Owner
{
public:
	void rva00734180(const CameraClass *camera);

private:
	unsigned char m_pad0000[0x2A7CB0];
	Int m_numTrees;
	UnsignedByte m_anythingChanged;
	unsigned char m_pad2A7CB5[0x2A7CB6 - 0x2A7CB5];
	UnsignedByte m_updateAllKeys;
	unsigned char m_pad2A7CB7[0x2A93C0 - 0x2A7CB7];
	float m_cameraLookAtVector[3];
};

// ?rva00734180@Rva00734180Owner@@QAEXPBVCameraClass@@@Z
void Rva00734180Owner::rva00734180(const CameraClass *camera)
{
	Int curTree = 0;
	unsigned char *base = reinterpret_cast<unsigned char *>(this);
	camera->Validate_Transform();
	const float (&xform)[3][4] = camera->Get_Transform();
	float x = xform[0][2];
	float y = xform[1][2];
	float z = xform[2][2];
	m_cameraLookAtVector[0] = x * BfmeShadowScale;
	m_cameraLookAtVector[1] = y * BfmeShadowScale;
	m_cameraLookAtVector[2] = z * BfmeShadowScale;

	if (m_numTrees > 0) {
		do {
			unsigned char *tree = base + curTree * 0xE8;
			camera->Update_Frustum();
			bool visible = !(CollisionMath::Overlap_Test(
				camera->Get_Frustum_Raw(),
				*(const SphereClass *)(tree + 0x1F8)) == CollisionMath::OUTSIDE);
			UnsignedByte oldVisible = *(UnsignedByte *)(tree + 0x1F4);
			if ((UnsignedByte)visible != oldVisible) {
				*(UnsignedByte *)(tree + 0x1F4) = (UnsignedByte)visible;
				m_anythingChanged = 1;
			}
			curTree += *(Int *)(base + 0x2A9900);
		} while (curTree < m_numTrees);
	}
	m_updateAllKeys = 0;
}
