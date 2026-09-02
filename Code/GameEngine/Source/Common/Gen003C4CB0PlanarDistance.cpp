// Address-derived planar distance body at 0x003C4CB0.

extern "C" double sqrt( double value );
#pragma intrinsic( sqrt )

class Gen003C4CB0Point
{
public:
	char m_pad00[ 0x10 ];
	float m_x;
	float m_y;
};

class Gen003C4CB0Owner
{
public:
	float planarDistance( const Gen003C4CB0Point *other ) const;

private:
	char m_pad00[ 0x10 ];
	float m_x;
	float m_y;
};

float Gen003C4CB0Owner::planarDistance( const Gen003C4CB0Point *other ) const
{
	float otherY = *(volatile const float *)&other->m_y;
	float local[ 2 ];
	*(volatile float *)&local[ 0 ] = other->m_x - m_x;
	float dy = otherY - m_y;
	return (float)sqrt( dy * dy + local[ 0 ] * local[ 0 ] );
}
