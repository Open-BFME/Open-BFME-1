// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00740600: one frame of a scripted camera-transform lerp on W3DView.
// Camera is at +0x104 (confirmed by calcDeltaScroll). Start/end Matrix3D sit
// at +0x13C/+0x16C, frame counters at +0x19C/+0x1A0, ParabolicEase at +0x1A4,
// and the doing-flag at +0x2354.

typedef float Real;
typedef int Int;

class Matrix3D
{
public:
	static void Lerp(const Matrix3D &A, const Matrix3D &B, float factor, Matrix3D &result);

private:
	float m[12];
};

class ParabolicEase
{
public:
	Real operator()(Real param) const;

private:
	Real m_in;
	Real m_out;
};

#define UNUSED_VIRTUALS_16(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9(); virtual void prefix##a(); virtual void prefix##b(); \
	virtual void prefix##c(); virtual void prefix##d(); virtual void prefix##e(); virtual void prefix##f()

class CameraClass
{
public:
	UNUSED_VIRTUALS_16(unused000_);
	virtual void unused040();
	virtual void unused044();
	virtual void unused048();
	virtual void unused04c();
	virtual void unused050();
	virtual void Set_Transform(const Matrix3D &transform);
};

struct CameraLerpFrames
{
	Int numFrames;
	Int curFrame;
	ParabolicEase ease;
};

class W3DView
{
private:
	void lerpCameraOneFrame();

	unsigned char m_pad000[0x104];
	CameraClass *m_3DCamera;
	unsigned char m_pad108[0x13C - 0x108];
	Matrix3D m_startTransform;
	Matrix3D m_endTransform;
	CameraLerpFrames m_frames;
	unsigned char m_pad1AC[0x2354 - 0x1AC];
	Int m_doingLerp;
};

// ?lerpCameraOneFrame@W3DView@@AAEXXZ
void W3DView::lerpCameraOneFrame()
{
	Int cur = m_frames.curFrame;
	Int num = m_frames.numFrames;
	if (cur <= num)
	{
		Real factor = m_frames.ease((Real)cur / (Real)num);
		Matrix3D result;
		Matrix3D::Lerp(m_startTransform, m_endTransform, factor, result);
		m_3DCamera->Set_Transform(result);
		++m_frames.curFrame;
	}
	if (m_frames.curFrame >= m_frames.numFrames)
		m_doingLerp = 0;
}
