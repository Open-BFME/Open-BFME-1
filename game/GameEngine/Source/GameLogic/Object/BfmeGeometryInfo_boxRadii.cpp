// cl: /O2 /Ob2 /G6
// BFME's box geometry accessors expose the major and minor radii at
// this+0x24 and this+0x28 respectively.

class BfmeGeometryInfo
{
public:
	float boxMajorRadius(void) const;
	float boxMinorRadius(void) const;

private:
	unsigned char m_prefix[0x24];
	float m_majorRadius;
	float m_minorRadius;
};

// ?boxMajorRadius@BfmeGeometryInfo@@QBEMXZ
float BfmeGeometryInfo::boxMajorRadius(void) const
{
	return m_majorRadius;
}

// ?boxMinorRadius@BfmeGeometryInfo@@QBEMXZ
float BfmeGeometryInfo::boxMinorRadius(void) const
{
	return m_minorRadius;
}
