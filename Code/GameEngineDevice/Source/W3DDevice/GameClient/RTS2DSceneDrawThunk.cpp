// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?draw@RTS2DScene@@UAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DScene.cpp
// Open-BFME5: RTS2DScene::draw, retail 0x00711AB0, converted out of a machine
// byte dump. The reference body is two lines and ports unchanged.
//
// What the bytes fix is where the scene is. draw() is a virtual of a second
// base: retail reaches its SceneClass by `add ecx,0xFFFFFEF8`, so the scene
// starts 0x108 bytes BEFORE the this pointer draw() is entered with, and
// m_camera sits at +0x0C from that same pointer. The cast below is that
// adjustment written out rather than a class graph guessed at, because one body
// cannot say what fills the 0x108.
//
// Everything else is WW3D::Render's default arguments: two false flags and a
// Vector3 zeroed into the frame three stores at a time.

typedef float Real;

#define NULL 0

class CameraClass;
class SceneClass;

class Vector3
{
public:
	Vector3( Real x, Real y, Real z ) : X(x), Y(y), Z(z) { }

	Real X, Y, Z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static bool Render( SceneClass *scene, CameraClass *cam, bool clear = false,
						bool clearz = false, const Vector3 &color = Vector3(0, 0, 0) );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DScene.h
class RTS2DScene
{
public:
	virtual void draw( void );

private:
	unsigned char m_unreconstructed_04[0x0C - 0x04];
	CameraClass *m_camera;									///< +0x0C
};

// ?draw@RTS2DScene@@UAEXXZ
void RTS2DScene::draw( )
{

	if (m_camera == NULL) {
		return;
	}
	WW3D::Render( (SceneClass *)((char *)this - 0x108), m_camera );


}  // end Customized_Render
