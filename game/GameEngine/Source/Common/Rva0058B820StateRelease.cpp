// Address-derived owner for the 18-byte body at 0x0058B820.  Its one-byte
// state guards the retail HideRankInterface thunk and is cleared after it runs.

void j_00001f32();

class Rva0058B820StateRelease
{
public:
	void release();

private:
	bool m_active;
};

void Rva0058B820StateRelease::release()
{
	if( m_active )
	{
		j_00001f32();
		m_active = false;
	}
}
