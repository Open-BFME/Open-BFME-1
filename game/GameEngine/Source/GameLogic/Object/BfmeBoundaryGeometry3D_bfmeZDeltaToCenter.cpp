// cl: /O2 /Ob2 /G6
// BFME's boundary geometry stores the vertical center delta at this+0x20.
// The retail helper is the direct float accessor at 0x0087DBF0.

class BfmeBoundaryGeometry3D
{
public:
	float bfmeZDeltaToCenter(void) const;

private:
	unsigned char m_prefix[0x20];
	float m_zDeltaToCenter;
};

// ?bfmeZDeltaToCenter@BfmeBoundaryGeometry3D@@QBEMXZ
float BfmeBoundaryGeometry3D::bfmeZDeltaToCenter(void) const
{
	return m_zDeltaToCenter;
}
