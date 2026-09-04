extern "C" double sqrt( double value );
#pragma intrinsic( sqrt )

struct Rva00264B80Point
{
	char m_pad[ 0x38 ];
	float m_x;
	float m_y;
};

struct Rva00264B80Position
{
	float m_x;
	float m_y;
	float m_z;
};

struct Rva00264B80Delta
{
	float m_x;
	float m_y;
	float m_z;

	Rva00264B80Delta( float x, float y ) : m_x( x ), m_y( y ) {}

	Rva00264B80Delta &operator-=( const Rva00264B80Delta &that )
	{
		m_x -= that.m_x;
		m_y -= that.m_y;
		return *this;
	}

	float length() const
	{
		return (float)sqrt( m_x * m_x + m_y * m_y );
	}
};

class Rva00264B80DistanceCheck
{
public:
	unsigned char isOutside( const Rva00264B80Point *point );

private:
	char m_pad[ 8 ];
	float m_radius;
	Rva00264B80Position *m_position;
};

unsigned char Rva00264B80DistanceCheck::isOutside( const Rva00264B80Point *point )
{
    Rva00264B80Delta delta( point->m_x, point->m_y );
	Rva00264B80Delta origin( m_position->m_x, m_position->m_y );
	delta -= origin;
	return delta.length() > m_radius;
}
