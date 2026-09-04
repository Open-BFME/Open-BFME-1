// cl: /DNDEBUG /MD /EHsc
// BFME W3DSupplyDraw::updateDrawModuleSupplyStatus, retail 0x0077DDF0 (384B).
//
// The body is entered through the secondary W3DModelDrawInterface view.  Its
// receiver is therefore the +0x0C view of the complete draw module: module
// data and Drawable are at -0x08/-0x04, while the supply counters are at
// +0x270/+0x274 in this view.  The interface has more methods than the ZH
// header; only the proven slot used by this body is named.

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>

typedef int Int;
typedef bool Bool;

static const Int& bfmeMax(const Int& left, const Int& right)
{
	return left > right ? left : right;
}

class AsciiString
{
public:
	AsciiString(const AsciiString& other);
	AsciiString(const char* text);
	~AsciiString();

	const char* str() const
	{
		if (m_data)
			return reinterpret_cast<const char*>(m_data + 8);
		return reinterpret_cast<const char*>(0x0107388B);
	}

private:
	int m_data;
};

struct Coord3D;
class Matrix3D;

class BFMEDrawableBoneQuery
{
public:
	Int getPristineBonePositions(const char* boneNamePrefix, Int startIndex,
		Coord3D* positions, Matrix3D* transforms,
		Int maxBones, Int extra) const;
};

// The secondary interface is 42 slots in the BFME image.  Slot 0x78 is the
// five-argument sub-object update used by the supply loop.
class W3DModelDrawInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void updateSubObject(const AsciiString& name, Bool show,
		Bool unused, Int unused2, Int unused3) = 0;
};

class W3DSupplyDrawModuleData
{
public:
	unsigned char m_unmodelled_000[0x15C];
	AsciiString m_supplyBonePrefix;
};

class W3DSupplyDraw : public W3DModelDrawInterface
{
public:
	virtual void updateDrawModuleSupplyStatus(Int maxSupply, Int currentSupply);

private:
	unsigned char m_unmodelled_004[0x26C];
	Int m_totalBones;
	Int m_lastNumberShown;

	W3DSupplyDrawModuleData* getW3DSupplyDrawModuleData() const
	{
		return *reinterpret_cast<W3DSupplyDrawModuleData**>(
			reinterpret_cast<unsigned char*>(const_cast<W3DSupplyDraw*>(this)) - 8);
	}

	BFMEDrawableBoneQuery* getDrawable() const
	{
		return *reinterpret_cast<BFMEDrawableBoneQuery**>(
			reinterpret_cast<unsigned char*>(const_cast<W3DSupplyDraw*>(this)) - 4);
	}
};

void W3DSupplyDraw::updateDrawModuleSupplyStatus(Int maxSupply, Int currentSupply)
{
	AsciiString boneName = getW3DSupplyDrawModuleData()->m_supplyBonePrefix;
	Int* totalBones = &m_totalBones;
	if (*totalBones == -1)
	{
		*totalBones = getDrawable()->getPristineBonePositions(
			boneName.str(), 1, 0, 0, INT_MAX, 0);
		m_lastNumberShown = *totalBones;
	}

	Int bonesToShow = (Int)ceil(*totalBones * (currentSupply / (float)maxSupply));
	bonesToShow = std::min(*totalBones, bonesToShow);

	if (bonesToShow != m_lastNumberShown)
	{
		Int lowIndex = std::min(bonesToShow, m_lastNumberShown);
		Int highIndex = bfmeMax(m_lastNumberShown, bonesToShow);
		Bool hide = bonesToShow < m_lastNumberShown;
		Int currentIndex = lowIndex + 1;
		while (currentIndex <= highIndex)
		{
			char buffer[16];
			sprintf(buffer, "%s%02d", boneName.str(), currentIndex);
			{
				AsciiString name(buffer);
				updateSubObject(name, !hide, false, 0, 0);
			}
			++currentIndex;
		}
		m_lastNumberShown = bonesToShow;
	}
}
