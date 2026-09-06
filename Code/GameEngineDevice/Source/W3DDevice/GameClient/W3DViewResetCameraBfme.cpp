// cl: /DNDEBUG /MD
//
// BFME W3DView::resetCamera, retail 0x00743640.

typedef float Real;
typedef int Int;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D
{
	char m_body[0x30];
};

class Rva0045A000
{

	// The scalar sampler is reached through the ILT at 0x00046FA1.
	public:
	char m_padding00[0x1C];
	Bool m_ready;
	char m_padding1D[0x70 - 0x1D];
};

extern void d_0073a9b0(void);
extern void j_00046fa1(void);
extern void j_000312a0(void);

class BfmeThingBRD
{
public:
	void bfmeDoBRD(void *easeIn, void *easeOut, void *milliseconds);

	char m_body[8];
};

class CameraResetAux
{
public:
	virtual void slot00();
	virtual Real slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18(Real *value, unsigned *position);
};

class W3DView
{
public:
	virtual void resetCamera(const Coord3D *location, Int milliseconds,
		Real easeIn, Real easeOut);

private:
	void buildCameraTransform(Matrix3D *transform);

	char m_padding00[0x08];
	Coord3D m_pos;
	char m_padding18[0x28 - 0x18];
	unsigned m_positionState;
	char m_padding2C[0x30 - 0x2C];
	Int m_field30;
	char m_padding34[0x3C - 0x34];
	Real m_cameraZoom;
	Real m_cameraHeight;
	char m_padding44[0x58 - 0x44];
	Int m_cameraFrame;
	Int m_cameraLastFrame;
	char m_padding60[0x68 - 0x60];
	Int m_cameraMode;
	Real m_fov;
	Real m_pitch;
	char m_padding74[0xA0 - 0x74];
	Real m_cameraScale;
	char m_paddingA4[0x13C - 0xA4];
	Matrix3D m_cameraTransform;
	Matrix3D m_cameraTransformScratch;
	Int m_cameraFrames;
	Int m_cameraFrameStart;
	BfmeThingBRD m_cameraEase;
	char m_padding1AC[0x1DC - 0x1AC];
	Bool m_rotatingCamera;
	char m_padding1DD[0x204 - 0x1DD];
	Bool m_zoomingCamera;
	char m_padding205[0x228 - 0x205];
	Bool m_pitchingCamera;
	char m_padding229[0x27C - 0x229];
	Bool m_cameraMovementAlternate;
	Bool m_cameraMovementFinished;
	char m_padding27E[0x2354 - 0x27E];
	Int m_cameraMovementMode;
	char m_padding2358[0x23B8 - 0x2358];
	Bool m_cameraMovedOnWaypointPath;
	char m_padding23B9[0x23D8 - 0x23B9];
	Real m_cameraValueA;
	Real m_cameraValueB;
	Real m_cameraOffsetZ;
	char m_padding23E4[0x23F8 - 0x23E4];
	Real m_groundLevel;
	char m_padding23FC[0x240C - 0x23FC];
	Bool m_cameraHasMovedSinceRequest;
	char m_padding240D[0x243C - 0x240D];
	Int m_cameraValueC;
	Int m_cameraValueD;
	Int m_cameraValueE;
	Rva0045A000 m_heightField;
	CameraResetAux m_cameraAux;
};

#pragma comment(linker, "/alternatename:?buildCameraTransform@W3DView@@AAEXPAVMatrix3D@@@Z=?j_0000a8df@@YAXXZ")

void W3DView::resetCamera(const Coord3D *location, Int milliseconds,
	Real easeIn, Real easeOut)
{
	if (location == 0)
		location = &m_pos;

	m_cameraAux.slot17();
	buildCameraTransform(&m_cameraTransform);
	m_cameraMovementMode = 0;
	m_rotatingCamera = false;
	m_zoomingCamera = false;
	m_pitchingCamera = false;
	m_cameraMovementFinished = false;
	m_cameraMovementAlternate = false;
	m_cameraMovedOnWaypointPath = false;
	m_cameraValueC = 0;
	m_cameraValueD = 0;
	m_cameraValueE = 0;
	m_cameraFrame = 0;
	m_cameraLastFrame = 0;
	m_cameraMode = 0;
	m_pos = *location;

	typedef Real (__cdecl *TerrainHeight)(Real, Real);
	Real terrainHeight = reinterpret_cast<TerrainHeight>(d_0073a9b0)(m_pos.x, m_pos.y);
	if (m_heightField.m_ready)
	{
		typedef Real (Rva0045A000::*Sample)(Real, Real);
		union
		{
			void (*function)(void);
			Sample member;
		} thunk;
		thunk.function = j_00046fa1;
		terrainHeight = (m_heightField.*thunk.member)(m_pos.x, m_pos.y);
	}

	if (terrainHeight != m_groundLevel)
	{
		m_groundLevel = terrainHeight;
		m_cameraHasMovedSinceRequest = false;
	}

	m_cameraZoom = (m_cameraAux.slot01() + m_groundLevel) / m_cameraOffsetZ;
	m_cameraHeight = m_cameraAux.slot01();
	m_cameraAux.slot18(&m_cameraValueA, &m_positionState);
	m_cameraValueA *= m_cameraScale;
	*(unsigned *)&m_fov = 0x3F5F66F3u;
	m_cameraValueB *= m_cameraScale;
	m_pitch = 1.0f;
	m_field30 = 0;
	buildCameraTransform(&m_cameraTransformScratch);

	if (milliseconds > 1)
	{
		m_cameraMovementMode = 3;
		Int frameCount = milliseconds / (*(Int *)0x012BB1CC);
		m_cameraFrames = frameCount;
		if (frameCount < 1)
			frameCount = 1;
		m_cameraFrameStart = 0;
		m_cameraFrames = frameCount;
		typedef void (BfmeThingBRD::*SetEase)(Real, Real, Real);
		SetEase setEase = reinterpret_cast<SetEase>(&BfmeThingBRD::bfmeDoBRD);
		(m_cameraEase.*setEase)(easeIn, easeOut, (Real)milliseconds);
	}
	else
	{
		union
		{
			void (*function)(void);
			void (W3DView::*member)(void);
		} thunk;
		thunk.function = j_000312a0;
		(this->*thunk.member)();
	}
}
