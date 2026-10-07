// Retail calls ILT 0x37A56 -> 0x001C1DA0, matched Object::applyAttributeModifier
// (ObjectContainQueries.cpp); the range holds AsciiString names.
class AsciiString;
class Object
{
public:
	bool applyAttributeModifier(const AsciiString &name, int amount);
};

class BfmeSinkAY;

class BfmeRangeAY
{
public:
	unsigned char m_bfmeHeadAY[0x14];
	int *m_bfmeBeginAY;
	int *m_bfmeEndAY;
};

class BfmeOwnAY
{
public:
	void bfmeFeedAY(BfmeSinkAY *sink);

	unsigned char m_bfmeHeadAY[4];
	BfmeRangeAY *m_bfmeRangeAY;
};

void BfmeOwnAY::bfmeFeedAY(BfmeSinkAY *sink)
{
	if (sink == 0)
		return;

	BfmeRangeAY *range = m_bfmeRangeAY;

	for (int *slot = range->m_bfmeBeginAY; slot != range->m_bfmeEndAY; ++slot)
		reinterpret_cast<Object *>(sink)->applyAttributeModifier(*reinterpret_cast<const AsciiString *>(slot), -1);
}
