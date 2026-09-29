// cl: /DNDEBUG /MD /EHsc
//
// ParticleSystem::update, retail 0x005D1140 (1744 bytes).  Identity: slot 4 of
// the ParticleSystem vtable 0x0110FE48 (installed by the matched constructor
// 0x005CF850) reaches this body through ILT 0x00034928; slot 5 is the matched
// createParticle.  The Zero Hour ParticleSys.cpp update reworked by BFME:
// optional QueryPerformanceCounter timing, slaves of a master system skip
// straight to the particle update, the parent transform may come from a named
// bone of the attached Drawable, and emission is one out-of-line call.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter( __int64 *count );
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency( __int64 *frequency );

struct Coord3D
{
	void set( Real ax, Real ay, Real az ) { x = ax; y = ay; z = az; }
	Real x;
	Real y;
	Real z;
};

struct Vector4
{
	__forceinline Vector4 &operator=( const Vector4 &that )
	{
		X = that.X;
		Y = that.Y;
		Z = that.Z;
		W = that.W;
		return *this;
	}

	Real X;
	Real Y;
	Real Z;
	Real W;
};

__forceinline Real submul( const Vector4 &row, Real tmp1, Real tmp2, Real tmp3 )
{
	return row.X * tmp1 + row.Y * tmp2 + row.Z * tmp3;
}

struct Vector3
{
	Vector3( Real x, Real y, Real z ) : X( x ), Y( y ), Z( z ) {}
	Real X;
	Real Y;
	Real Z;
};

class Matrix3D
{
public:
	Matrix3D() {}
	__forceinline Matrix3D &operator=( const Matrix3D &that )
	{
		Row[ 0 ] = that.Row[ 0 ];
		Row[ 1 ] = that.Row[ 1 ];
		Row[ 2 ] = that.Row[ 2 ];
		return *this;
	}

	Vector3 Get_Translation() const { return Vector3( Row[ 0 ].W, Row[ 1 ].W, Row[ 2 ].W ); }

	__forceinline void mul( const Matrix3D &A, const Matrix3D &B )
	{
		Real tmp1, tmp2, tmp3;

		tmp1 = B.Row[ 0 ].X;
		tmp2 = B.Row[ 1 ].X;
		tmp3 = B.Row[ 2 ].X;
		Row[ 0 ].X = submul( A.Row[ 0 ], tmp1, tmp2, tmp3 );
		Row[ 1 ].X = submul( A.Row[ 1 ], tmp1, tmp2, tmp3 );
		Row[ 2 ].X = submul( A.Row[ 2 ], tmp1, tmp2, tmp3 );

		tmp1 = B.Row[ 0 ].Y;
		tmp2 = B.Row[ 1 ].Y;
		tmp3 = B.Row[ 2 ].Y;
		Row[ 0 ].Y = submul( A.Row[ 0 ], tmp1, tmp2, tmp3 );
		Row[ 1 ].Y = submul( A.Row[ 1 ], tmp1, tmp2, tmp3 );
		Row[ 2 ].Y = submul( A.Row[ 2 ], tmp1, tmp2, tmp3 );

		tmp1 = B.Row[ 0 ].Z;
		tmp2 = B.Row[ 1 ].Z;
		tmp3 = B.Row[ 2 ].Z;
		Row[ 0 ].Z = submul( A.Row[ 0 ], tmp1, tmp2, tmp3 );
		Row[ 1 ].Z = submul( A.Row[ 1 ], tmp1, tmp2, tmp3 );
		Row[ 2 ].Z = submul( A.Row[ 2 ], tmp1, tmp2, tmp3 );

		tmp1 = B.Row[ 0 ].W;
		tmp2 = B.Row[ 1 ].W;
		tmp3 = B.Row[ 2 ].W;
		Row[ 0 ].W = submul( A.Row[ 0 ], tmp1, tmp2, tmp3 ) + A.Row[ 0 ].W;
		Row[ 1 ].W = submul( A.Row[ 1 ], tmp1, tmp2, tmp3 ) + A.Row[ 1 ].W;
		Row[ 2 ].W = submul( A.Row[ 2 ], tmp1, tmp2, tmp3 ) + A.Row[ 2 ].W;
	}

	Real Get_X_Translation() const { return Row[ 0 ].W; }
	Real Get_Y_Translation() const { return Row[ 1 ].W; }
	Real Get_Z_Translation() const { return Row[ 2 ].W; }
	void Set_Translation( const Coord3D &t ) { Row[ 0 ].W = t.x; Row[ 1 ].W = t.y; Row[ 2 ].W = t.z; }
	void Set_X_Translation( Real x ) { Row[ 0 ].W = x; }
	void Set_Y_Translation( Real y ) { Row[ 1 ].W = y; }
	void Set_Z_Translation( Real z ) { Row[ 2 ].W = z; }

	Vector4 Row[ 3 ];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	Bool isNotEmpty() const;
	const T *str() const { return m_data ? m_data->data : (const T *)""; }

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
};

struct GlobalData
{
	unsigned char m_beforeUseFX[ 0xa7f ];
	Bool m_useFX;
	unsigned char m_beforeA91[ 0xa91 - 0xa80 ];
	Bool m_boolA91;
};

extern GlobalData *TheWritableGlobalData;

class Drawable
{
public:
	Int getPristineBonePositions( const char *boneNamePrefix, Int startIndex, Coord3D *positions,
		Matrix3D *transforms, Int maxBones ) const;

	unsigned char m_before3B0[ 0x3b0 ];
	Bool m_bool3B0;
	Bool m_bool3B1;
};

class GameClient
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28();
	virtual Drawable *findDrawableByID( UnsignedInt id );
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3c(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4c(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64();
	virtual UnsignedInt getFrame();
};

extern GameClient *TheGameClient;

enum ObjectShroudStatus
{
	OBJECTSHROUD_FOGGED = 3
};

class Object
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable();

	ObjectShroudStatus getShroudedStatus( Int playerIndex ) const;
	const Matrix3D *getTransformMatrix() const { return &m_transform; }

private:
	void *m_field04;
	Matrix3D m_transform;
};

class GameLogic
{
public:
	Object *findObjectByID( Int id );
};

extern GameLogic *TheGameLogic;

class Particle
{
public:
	const Coord3D *getPosition() const { return &m_pos; }

private:
	unsigned char m_before1C[ 0x1c ];
	Coord3D m_pos;
};

// Thunked bodies whose ledger names are address-derived placeholders.
extern void j_00017512();
extern void j_00044ebd();
extern void j_00002153();

class Rva005D1140Call
{
};

// Drawable transform accessor at 0x0041CEC0 (ILT 0x00017512).
static __forceinline const Matrix3D *drawableTransform( Drawable *draw )
{
	typedef const Matrix3D *( Rva005D1140Call::*Function )();
	union { void ( *raw )(); Function member; } fn;
	fn.raw = j_00017512;
	return ( reinterpret_cast<Rva005D1140Call *>( draw )->*fn.member )();
}

class ParticleSystem
{
public:
	virtual Bool update( Int localPlayerIndex );

	void destroy();
	void setLocalTransform( const Matrix3D *matrix );
	void emit( const Coord3D *pos, Int priority, Bool isIdentity, const Matrix3D *transform );

private:
	// Particle update tail at 0x005CCA10 (ILT 0x00002153).
	Bool updateParticles()
	{
		typedef Bool ( Rva005D1140Call::*Function )();
		union { void ( *raw )(); Function member; } fn;
		fn.raw = j_00002153;
		return ( reinterpret_cast<Rva005D1140Call *>( this )->*fn.member )();
	}

	// Notifier at 0x005CC190 (ILT 0x00044EBD) run on the +0x1B0 member.
	void notify1B0()
	{
		typedef void ( Rva005D1140Call::*Function )();
		union { void ( *raw )(); Function member; } fn;
		fn.raw = j_00044ebd;
		( reinterpret_cast<Rva005D1140Call *>( &m_member1B0 )->*fn.member )();
	}

	unsigned char m_pad004[ 0x7c - 0x04 ];
	Int m_priority;
	unsigned char m_pad080[ 0xb0 - 0x80 ];
	Real m_updateTime;						// +0xb0
	UnsignedInt m_attachedToDrawableID;		// +0xb4
	Int m_attachedToObjectID;				// +0xb8
	AsciiString m_attachedBoneName;			// +0xbc
	Matrix3D m_localTransform;				// +0xc0
	Matrix3D m_transform;					// +0xf0
	UnsignedInt m_burstDelayLeft;			// +0x120
	UnsignedInt m_delayLeft;				// +0x124
	UnsignedInt m_startTimestamp;			// +0x128
	UnsignedInt m_systemLifetimeLeft;		// +0x12c
	unsigned char m_pad130[ 0x148 - 0x130 ];
	Coord3D m_pos;							// +0x148
	Coord3D m_lastPos;						// +0x154
	unsigned char m_pad160[ 0x170 - 0x160 ];
	ParticleSystem *m_masterSystem;			// +0x170
	unsigned char m_pad174[ 0x1a0 - 0x174 ];
	Particle *m_controlParticle;			// +0x1a0
	Bool m_isLocalIdentity;					// +0x1a4
	Bool m_isIdentity;						// +0x1a5
	Bool m_isForever;						// +0x1a6
	Bool m_isStopped;						// +0x1a7
	Bool m_isDestroyed;						// +0x1a8
	unsigned char m_pad1A9[ 3 ];
	Bool m_skipParentXfrm;					// +0x1ac
	unsigned char m_pad1AD[ 3 ];
	unsigned char m_member1B0[ 4 ];			// +0x1b0
};

// ?update@ParticleSystem@@UAE_NH@Z
Bool ParticleSystem::update( Int localPlayerIndex )
{
	__int64 frequency;
	__int64 start;
	__int64 end;

	m_updateTime = 0.0f;
	if( TheWritableGlobalData->m_boolA91 )
	{
		QueryPerformanceFrequency( &frequency );
		QueryPerformanceCounter( &start );
	}

	if( TheWritableGlobalData->m_useFX == false )
		return false;

	if( m_delayLeft )
	{
		--m_delayLeft;
		if( m_delayLeft == 0 )
			m_startTimestamp = TheGameClient->getFrame();
		return true;
	}

	Bool isHidden = false;
	Bool isShrouded = false;

	if( m_masterSystem == 0 )
	{
		const Matrix3D *parentXfrm = 0;

		if( m_attachedToDrawableID )
		{
			Drawable *attachedTo = TheGameClient->findDrawableByID( m_attachedToDrawableID );
			if( attachedTo )
			{
				if( !attachedTo->m_bool3B1 )
					isHidden = true;
				if( attachedTo->m_bool3B0 )
					isShrouded = true;

				parentXfrm = drawableTransform( attachedTo );

				m_lastPos = m_pos;
				Vector3 translation = parentXfrm->Get_Translation();
				m_pos.set( translation.X, translation.Y, translation.Z );

				if( m_attachedBoneName.isNotEmpty() )
				{
					Matrix3D boneTransform;
					if( attachedTo->getPristineBonePositions( m_attachedBoneName.str(), 0, 0, &boneTransform, 1 ) )
						setLocalTransform( &boneTransform );
				}
			}
			else
			{
				m_attachedToDrawableID = 0;
				destroy();
			}
		}
		else if( m_attachedToObjectID )
		{
			Object *objectAttachedTo = TheGameLogic->findObjectByID( m_attachedToObjectID );
			if( objectAttachedTo )
			{
				isShrouded = objectAttachedTo->getShroudedStatus( localPlayerIndex ) >= OBJECTSHROUD_FOGGED;

				Drawable *draw = objectAttachedTo->getDrawable();
				if( draw )
				{
					if( !draw->m_bool3B1 )
						isHidden = true;

					parentXfrm = drawableTransform( draw );

					if( m_attachedBoneName.isNotEmpty() )
					{
						Matrix3D boneTransform;
						if( draw->getPristineBonePositions( m_attachedBoneName.str(), 0, 0, &boneTransform, 1 ) )
							setLocalTransform( &boneTransform );
					}
				}
				else
					parentXfrm = objectAttachedTo->getTransformMatrix();

				m_lastPos = m_pos;
				Vector3 translation = parentXfrm->Get_Translation();
				m_pos.set( translation.X, translation.Y, translation.Z );
			}
			else
			{
				m_attachedToObjectID = 0;
				destroy();
			}
		}

		if( parentXfrm )
		{
			if( m_skipParentXfrm )
				m_transform = m_localTransform;
			else if( m_isLocalIdentity == false )
				m_transform.mul( *parentXfrm, m_localTransform );
			else
				m_transform = *parentXfrm;
			m_isIdentity = false;
		}
		else if( m_isLocalIdentity == false )
		{
			m_transform = m_localTransform;
			m_isIdentity = false;
		}
		else
			m_isIdentity = true;

		if( m_controlParticle )
		{
			const Coord3D *controlPos = m_controlParticle->getPosition();
			m_transform.Set_Translation( *controlPos );
			m_isIdentity = false;
			m_lastPos = m_pos;
			m_pos = *controlPos;
		}

		if( m_isDestroyed == false && ( m_isForever || ( m_isForever == false && m_systemLifetimeLeft > 0 ) ) )
		{
			if( !isShrouded && m_isStopped == false && !isHidden )
				emit( &m_pos, m_priority, m_isIdentity, &m_transform );
		}
	}

	notify1B0();
	Bool result = updateParticles();

	if( TheWritableGlobalData->m_boolA91 )
	{
		QueryPerformanceCounter( &end );
		m_updateTime = (Real)( end - start ) * 1000.0f / (Real)frequency;
	}
	return result;
}
