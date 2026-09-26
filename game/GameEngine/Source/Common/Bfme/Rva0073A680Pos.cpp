// 33-byte Vec3 getter with individual member assignments

struct Vec3
{
	int x;
	int y;
	int z;
};

class Rva0073A680
{
public:
	void getPosition( Vec3 *out ) const;

	char m_pad00[ 0x4B8 ];
	int  m_x;
	int  m_y;
	int  m_z;
};

void Rva0073A680::getPosition( Vec3 *out ) const
{
	out->x = m_x;
	out->y = m_y;
	out->z = m_z;
}
