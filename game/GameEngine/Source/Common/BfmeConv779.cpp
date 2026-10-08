// retail ILT 0x0001FDC5 -> 0x00154B80 is the matched private AIGroup::recompute
// row and ILT 0x00032231 -> 0x0018F400 the matched protected
// PolygonTrigger::updateBounds row
class AIGroup
{
	friend struct BfmeThingDTI;
	void recompute();
};

class PolygonTrigger
{
	friend struct BfmeThingDTJ;
protected:
	void updateBounds() const;
};

struct BfmeThingDTI
{
	float bfmeGoDTI();
	unsigned char m_bfmeHead[0xc];
	float m_bfmeVal;
	char m_bfmeFlag;
};

float BfmeThingDTI::bfmeGoDTI()
{
	if (m_bfmeFlag)
		((AIGroup *)this)->recompute();
	return m_bfmeVal;
}

struct BfmeThingDTJ
{
	float bfmeGoDTJ();
	unsigned char m_bfmeHead[0x2c];
	float m_bfmeVal;
	char m_bfmeFlag;
};

float BfmeThingDTJ::bfmeGoDTJ()
{
	if (m_bfmeFlag)
		((const PolygonTrigger *)this)->updateBounds();
	return m_bfmeVal;
}
