// cl: /DNDEBUG /MD /EHsc
// Object::setGeometryInfo. Assigns GeometryInfo at +0xAC then notifies four
// optional helpers. Call order is +0x3B0 PartitionData::makeDirty, +0x3B8
// Rva009A2350::init, +0x3B4 Rva009F2BA0::init, +0x80 BfmeBCNG::bfmeThreeCNG.
// The assign callee is the ILT at 0x00003828 already pinned as bfmeAssign.

struct BfmeCopyElementA
{
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *other);
};

class PartitionData
{
public:
	void makeDirty();
};

class Rva009A2350
{
public:
	void init();
};

class Rva009F2BA0
{
public:
	void init();
};

class BfmeBCNG
{
public:
	void bfmeThreeCNG();
};

class GeometryInfo
{
};

class Object
{
public:
	void setGeometryInfo(const GeometryInfo &geom);

private:
	char m_raw[0x3BC];
};

void Object::setGeometryInfo(const GeometryInfo &geom)
{
	reinterpret_cast<BfmeCopyElementA *>(m_raw + 0xAC)->bfmeAssign(
		(BfmeCopyElementA *)&geom);

	PartitionData *part = *reinterpret_cast<PartitionData **>(m_raw + 0x3B0);
	if (part)
		part->makeDirty();

	Rva009A2350 *a = *reinterpret_cast<Rva009A2350 **>(m_raw + 0x3B8);
	if (a)
		a->init();

	Rva009F2BA0 *b = *reinterpret_cast<Rva009F2BA0 **>(m_raw + 0x3B4);
	if (b)
		b->init();

	BfmeBCNG *c = *reinterpret_cast<BfmeBCNG **>(m_raw + 0x80);
	if (c)
		c->bfmeThreeCNG();
}
