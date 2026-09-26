// 18-byte guarded offset addition getter

class Inner00489360
{
public:
	int m_pad0;
	int m_val;
};

class Rva00489360
{
public:
	int get() const;

	char            m_pad00[ 0x4 ];
	int             m_baseVal;
	char            m_pad08[ 0x8 ];
	Inner00489360 * m_inner;
};

int Rva00489360::get() const
{
	if( m_inner )
		return m_inner->m_val + m_baseVal;
	return m_baseVal;
}
