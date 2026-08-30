// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/GameClient /ICode/GameEngine/Include/Precompiled
//
// Retail 0x0079D180 compares four pairs of floats in two inline tables.  The
// first table begins at +0x4DC and the second at +0x524; the compiler's retail
// shape walks from the second float of each first-table pair, which gives the
// characteristic [-4]/[+0x44] and [0]/[+0x48] x87 loads.
// The address-derived class and method name are intentional: the bytes and
// surrounding layout identify the operation, but not a recovered public name.

class Rva0079D180
{
	char m_pad[0x4dc];
	float m_left[8];
	char m_gap[0x28];
	float m_right[8];

public:
	bool compare() const;
};

bool Rva0079D180::compare() const
{
	int i = 0;
	const float *p = &m_left[1];
	while( i < 4 )
	{
		if( p[17] != p[-1] || p[18] != p[0] )
			return true;
		++i;
		p += 2;
	}
	return false;
}
