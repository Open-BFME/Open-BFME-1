// ?setCameraTransform@W3DView@@AAEXXZ
// partial score=0.92 date=2026-08-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#include "matrix3d.h"

typedef float Real;

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

inline Real minf( Real a, Real b ) { return a < b ? a : b; }
inline Real maxf( Real a, Real b ) { return a > b ? a : b; }

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
	virtual void Set_Transform( const Matrix3D &transform );

	void Set_Clip_Planes( Real nearZ, Real farZ );
	void Set_View_Plane( Real horizontalFOV, Real verticalFOV );
};

class RenderObjClass;
template <class T> class RefMultiListIterator;
typedef RefMultiListIterator<RenderObjClass> RefRenderObjListIterator;

class RTS3DScene
{
public:
	RefRenderObjListIterator *createLightsIterator();
	void destroyLightsIterator( RefRenderObjListIterator *iterator );
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class BaseHeightMapRenderObjClass
{
public:
	UNUSED_VIRTUALS_16(unused000_);
	UNUSED_VIRTUALS_16(unused040_);
	UNUSED_VIRTUALS_16(unused080_);
	UNUSED_VIRTUALS_16(unused0c0_);
	UNUSED_VIRTUALS_16(unused100_);
	UNUSED_VIRTUALS_16(unused140_);
	UNUSED_VIRTUALS_16(unused180_);
	UNUSED_VIRTUALS_16(unused1c0_);
	virtual void unused200();
	virtual void unused204();
	virtual void unused208();
	virtual void unused20c();
	virtual void unused210();
	virtual void unused214();
	virtual void unused218();
	virtual void updateCenter( CameraClass *camera, RefRenderObjListIterator *lights );
};

class ScriptEngine
{
public:
	void notifyCameraChange();
};

struct GlobalData
{
	unsigned char m_padding0000[0xA28];
	Real m_maxCameraHeight;
	unsigned char m_padding0A2C[0xED0 - 0xA2C];
	bool m_debugCamera;
	unsigned char m_padding0ED1[3];
	Real m_debugCameraFOV;
	Real m_debugCameraAngle;
};

extern GlobalData *TheWritableGlobalData;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern ScriptEngine *TheScriptEngine;

// BFME's W3DView and terrain vtables predate the shared Zero Hour layouts.
// Keeping the verified offsets local avoids changing already matched users of
// those shared headers.
class W3DView
{
private:
	unsigned char m_padding0000[0x0C];
	Coord3D m_pos;
	unsigned char m_padding0018[0x44 - 0x18];
	bool m_applyCameraConstraints;
	unsigned char m_padding0045[0x6C - 0x45];
	Real m_FOV;
	unsigned char m_padding0070[0x104 - 0x70];
	CameraClass *m_3DCamera;
	unsigned char m_padding0108[0x23C8 - 0x108];
	bool m_cameraHasMovedSinceRequest;
	unsigned char m_padding23C9[0x23FC - 0x23C9];
	Region2D m_cameraConstraint;
	bool m_cameraConstraintValid;

	const Coord3D *getPosition() const { return &m_pos; }
	void setPosition( const Coord3D *position ) { m_pos = *position; }
	void setCameraTransform();
	void buildCameraTransform( Matrix3D *transform );
	void calcCameraConstraints();
};

void W3DView::setCameraTransform()
{
	m_cameraHasMovedSinceRequest = true;
	Matrix3D cameraTransform( true );

	m_3DCamera->Set_Clip_Planes( 10.0f, TheWritableGlobalData->m_maxCameraHeight * 1800.0f );

	if (!m_cameraConstraintValid)
	{
		buildCameraTransform( &cameraTransform );
		m_3DCamera->Set_Transform( cameraTransform );
		calcCameraConstraints();
	}

	if (m_cameraConstraintValid && m_applyCameraConstraints)
	{
		Coord3D pos;
		pos.x = getPosition()->x;
		pos.y = getPosition()->y;
		pos.z = getPosition()->z;
		pos.x = maxf( m_cameraConstraint.lo.x, pos.x );
		pos.x = minf( m_cameraConstraint.hi.x, pos.x );
		pos.y = maxf( m_cameraConstraint.lo.y, pos.y );
		pos.y = minf( m_cameraConstraint.hi.y, pos.y );
		setPosition( &pos );
	}

	m_3DCamera->Set_View_Plane(
		TheWritableGlobalData->m_debugCamera ? TheWritableGlobalData->m_debugCameraFOV : m_FOV,
		-1.0f );

	buildCameraTransform( &cameraTransform );
	if (TheWritableGlobalData->m_debugCamera)
		cameraTransform.Rotate_Y( TheWritableGlobalData->m_debugCameraAngle );
	m_3DCamera->Set_Transform( cameraTransform );

	if (TheTerrainRenderObject)
	{
		RefRenderObjListIterator *iterator = W3DDisplay::m_3DScene->createLightsIterator();
		TheTerrainRenderObject->updateCenter( m_3DCamera, iterator );
		if (iterator)
			W3DDisplay::m_3DScene->destroyLightsIterator( iterator );
	}

	TheScriptEngine->notifyCameraChange();
}

#undef UNUSED_VIRTUALS_16
