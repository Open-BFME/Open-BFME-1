// BFME cache calculation body at retail 0x0041CEC0.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeVector3
{
	float x;
	float y;
	float z;
};

class Matrix3D
{
public:
	float m[ 12 ];

	Matrix3D &operator=( const Matrix3D &other )
	{
		m[ 0 ] = other.m[ 0 ];
		m[ 1 ] = other.m[ 1 ];
		m[ 2 ] = other.m[ 2 ];
		m[ 3 ] = other.m[ 3 ];
		m[ 4 ] = other.m[ 4 ];
		m[ 5 ] = other.m[ 5 ];
		m[ 6 ] = other.m[ 6 ];
		m[ 7 ] = other.m[ 7 ];
		m[ 8 ] = other.m[ 8 ];
		m[ 9 ] = other.m[ 9 ];
		m[ 10 ] = other.m[ 10 ];
		m[ 11 ] = other.m[ 11 ];
		return *this;
	}

	static void Lerp( const Matrix3D &a, const Matrix3D &b, float t,
		Matrix3D &result );
};

class ClientFrameSubsystem
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void *getFrameStamp();
};

extern ClientFrameSubsystem *TheGameClientClientUpdate;

class GameLogic
{
private:
	unsigned char m_unmodelled[ 0x3C ];

public:
	unsigned int m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class GameEngine
{
private:
	unsigned char m_unmodelled[ 0x38 ];

public:
	float m_interpolationFactor;
};

extern GameEngine *TheGameEngine;

extern BfmeVector3 *__stdcall bfmeVec3Hermite(
	BfmeVector3 *result,
	const Coord3D *position0,
	const Coord3D *tangent0,
	const Coord3D *position1,
	const Coord3D *tangent1,
	float factor );

class BFMERopeDrawableGetPositionShim
{
	friend class BfmeCalc919G;

	// This helper is a private Drawable member in the BFME layout.
	void bfmeRebuild( int force );
};

class BfmeCacheObject
{
private:
	unsigned char m_unmodelled[ 8 ];

public:
	Matrix3D m_matrix;
};

class BfmeCalc919G
{
private:
	unsigned char m_unmodelled_000[ 8 ];
	Matrix3D m_baseMatrix;
	unsigned char m_unmodelled_038[ 0xC4 ];
	BfmeCacheObject *m_object;
	unsigned char m_unmodelled_100[ 0x100 ];
	Matrix3D m_cachedMatrix;
	unsigned char m_unmodelled_20C[ 0x0C ];
	unsigned int m_lastFrameStamp;
	unsigned char m_unmodelled_240[ 0xD4 ];
	unsigned int m_updateFrame;
	unsigned char m_ready;
	unsigned char m_unmodelled_319[ 3 ];
	Matrix3D m_matrix0;
	Matrix3D m_matrix1;
	Coord3D m_position0;
	Coord3D m_tangent0;
	Coord3D m_position1;
	Coord3D m_tangent1;
	unsigned char m_unmodelled_3AC[ 8 ];
	unsigned char m_rebuildReady;

public:
	int bfmeCalc919G();
};

int BfmeCalc919G::bfmeCalc919G()
{
	BfmeCacheObject *object = m_object;
	if( object == 0 )
		return (int)&m_baseMatrix;

	register float factor;
	register unsigned int frameStamp =
		(unsigned int)TheGameClientClientUpdate->getFrameStamp();
	if( m_lastFrameStamp == frameStamp )
		goto return_cached;

	unsigned int updateFrame = m_updateFrame;
	unsigned int logicFrame = TheBfmeGameLogic->m_frame;
	if( updateFrame < logicFrame - 2 )
	{
		if( m_ready == 0 )
		{
			m_ready = 1;
			m_cachedMatrix.m[ 0 ] = object->m_matrix.m[ 0 ];
			m_cachedMatrix.m[ 1 ] = object->m_matrix.m[ 1 ];
			m_cachedMatrix.m[ 2 ] = object->m_matrix.m[ 2 ];
			m_cachedMatrix.m[ 3 ] = object->m_matrix.m[ 3 ];
			m_cachedMatrix.m[ 4 ] = object->m_matrix.m[ 4 ];
			m_cachedMatrix.m[ 5 ] = object->m_matrix.m[ 5 ];
			m_cachedMatrix.m[ 6 ] = object->m_matrix.m[ 6 ];
			m_cachedMatrix.m[ 7 ] = object->m_matrix.m[ 7 ];
			m_cachedMatrix.m[ 8 ] = object->m_matrix.m[ 8 ];
			m_cachedMatrix.m[ 9 ] = object->m_matrix.m[ 9 ];
			m_cachedMatrix.m[ 10 ] = object->m_matrix.m[ 10 ];
			m_cachedMatrix.m[ 11 ] = object->m_matrix.m[ 11 ];
		}
		goto return_cached;
	}

	if( m_rebuildReady == 0 )
		((BFMERopeDrawableGetPositionShim *)this)->bfmeRebuild( 0 );

	factor = TheGameEngine->m_interpolationFactor;
	Matrix3D *cachedMatrix = &m_cachedMatrix;
	Matrix3D::Lerp( m_matrix0, m_matrix1, factor, *cachedMatrix );

	m_lastFrameStamp = frameStamp;
	BfmeVector3 interpolated;
	bfmeVec3Hermite( &interpolated, &m_position0, &m_tangent0,
		&m_position1, &m_tangent1, factor );
	cachedMatrix->m[ 3 ] = interpolated.x;
	cachedMatrix->m[ 7 ] = interpolated.y;
	cachedMatrix->m[ 11 ] = interpolated.z;

return_cached:
	return (int)&m_cachedMatrix;
}
