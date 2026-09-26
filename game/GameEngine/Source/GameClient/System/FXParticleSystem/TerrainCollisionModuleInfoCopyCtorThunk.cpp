// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TerrainCollisionModuleInfo copy constructor.

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &);
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &that)
		: StringBase<char>(that)
	{
	}
};

namespace FXParticleSystem
{

class TerrainCollisionModuleInfoBase
{
public:
	TerrainCollisionModuleInfoBase(const TerrainCollisionModuleInfoBase &) {}
	virtual ~TerrainCollisionModuleInfoBase() {}
};

struct TerrainCollisionValueBlock
{
	// The matched constructor at 0x005FD230 passes this+8 to
	// GameClientRandomVariable::setRange. The shared type stores distribution,
	// minimum, and maximum at +0/+4/+8; keep these as raw words for this copy.
	unsigned int m_distributionBits;
	unsigned int m_minimumBits;
	unsigned int m_maximumBits;
};

class TerrainCollisionModuleInfo : public TerrainCollisionModuleInfoBase
{
public:
	TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &);
	virtual ~TerrainCollisionModuleInfo();

private:
	BFMERetailAsciiString m_eventName;
	TerrainCollisionValueBlock m_eventTime;
	bool m_flag;
	unsigned int m_cached;
};

// ??0TerrainCollisionModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
TerrainCollisionModuleInfo::TerrainCollisionModuleInfo(
	const TerrainCollisionModuleInfo &that)
	: TerrainCollisionModuleInfoBase(that),
	  m_eventName(that.m_eventName),
	  m_eventTime(that.m_eventTime),
	  m_flag(that.m_flag),
	  m_cached(that.m_cached)
{
}

}
