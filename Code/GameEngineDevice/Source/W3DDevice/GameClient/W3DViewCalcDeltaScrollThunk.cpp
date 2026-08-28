// cl: /DNDEBUG /MD /EHsc

// Project two world points and take the screen-space difference. Either
// projection failing leaves the output at the zero written on entry, which is
// why both branches jump to the same epilogue rather than to a cleanup.
//
// The class is declared here from padding rather than pulled from a header: only
// four offsets matter and the real W3DView drags in most of the device layer.
// m_pos at 0xC, the camera at 0x104, the previous look-at at 0x23E4 and the
// ground level at 0x23F8.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	float x;
	float y;
};

class Vector3
{
public:
	Vector3(void) {}

	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	float X;
	float Y;
	float Z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/camera.h
class CameraClass
{
public:
	enum ProjectionResType
	{
		INSIDE_FRUSTUM = 0
	};

	ProjectionResType Project(Vector3 &dest, const Vector3 &src) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView
{
private:
	// AAE is private. Declaring this public would mangle QAE and the ledger
	// row would fail as symbol-not-found rather than as a byte mismatch.
	void calcDeltaScroll(Coord2D &delta);

	unsigned char m_pad00[0x0C];
	Coord2D m_pos;
	unsigned char m_pad14[0x104 - 0x14];
	CameraClass *m_3DCamera;
	unsigned char m_pad108[0x23E4 - 0x108];
	Coord2D m_previousLookAtPosition;
	unsigned char m_pad23EC[0x23F8 - 0x23EC];
	float m_groundLevel;
};

// ?calcDeltaScroll@W3DView@@AAEXAAUCoord2D@@@Z
void W3DView::calcDeltaScroll(Coord2D &delta)
{
	delta.x = 0.0f;
	delta.y = 0.0f;

	Vector3 prevWorld(m_previousLookAtPosition.x, m_previousLookAtPosition.y, m_groundLevel);
	Vector3 prevScreen;
	if (m_3DCamera->Project(prevScreen, prevWorld) != CameraClass::INSIDE_FRUSTUM)
		return;

	Vector3 world(m_pos.x, m_pos.y, m_groundLevel);
	Vector3 screen;
	if (m_3DCamera->Project(screen, world) != CameraClass::INSIDE_FRUSTUM)
		return;

	delta.x = screen.X - prevScreen.X;
	delta.y = screen.Y - prevScreen.Y;
}
