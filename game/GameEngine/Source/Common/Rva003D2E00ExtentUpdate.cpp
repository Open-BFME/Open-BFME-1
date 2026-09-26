// cl: /O2 /Ob0

// The 0x003D2EE0 caller walks a pointer range and invokes the anonymous
// element body at 0x003D2E00.  The retail body refreshes four cached XY
// extent values from TheTerrainLogic and then forwards the new extent to
// each element.  No stronger source-level owner name is established by the
// caller or the retail vtable, so this reconstruction keeps the RVA identity.

struct Rva003D2E00Region
{
	float loX;
	float loY;
	float loZ;
	float hiX;
	float hiY;
	float hiZ;
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

class __declspec(novtable) Rva003D2E00TerrainView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void getMaximumPathfindExtent(Rva003D2E00Region *extent) const = 0;
};

extern void j_0002588d(void);

class Rva003D2E00ElementCall
{
public:
	void apply(const Rva003D2E00Region *extent);
};

class Rva003D2E00
{
public:
	void refresh();

private:
	char m_pad00[0x18];
	Rva003D2E00ElementCall **m_begin;
	Rva003D2E00ElementCall **m_end;
	char m_pad20[0x78];
	float m_loX;
	float m_loY;
	float m_hiX;
	float m_hiY;
};

void Rva003D2E00::refresh()
{
	Rva003D2E00Region extent;
	reinterpret_cast<Rva003D2E00TerrainView *>(TheTerrainLogic)
		->getMaximumPathfindExtent(&extent);

	if (extent.hiX == m_hiX && extent.hiY == m_hiY &&
		extent.loX == m_loX && extent.loY == m_loY)
		return;

	m_hiX = extent.hiX;
	m_hiY = extent.hiY;
	m_loX = extent.loX;
	m_loY = extent.loY;
	Rva003D2E00ElementCall **it = m_begin;
	while (it != m_end)
	{
		typedef void (Rva003D2E00ElementCall::*Function)(
			const Rva003D2E00Region *);
		union
		{
			void (*raw)(void);
			Function member;
		} fn;
		fn.raw = j_0002588d;
		((*it)->*fn.member)(&extent);
		++it;
	}
}
