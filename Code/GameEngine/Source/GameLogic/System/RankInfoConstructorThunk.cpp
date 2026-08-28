// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: RankInfo::RankInfo for retail 0x003A0810.
//
// The packet's lead is the right class but the reference's RankInfo cannot
// produce this body: its constructor is compiler-generated and 29 bytes, while
// retail runs 53 and explicitly initialises a block the reference does not have.
// The class is still RankInfo -- the body sits inside the RankInfo cluster
// (getRankInfo 0x003A0730, ??_GRankInfo 0x003A0AB0, ??1RankInfo 0x003A0AE0) and
// the already-claimed destructor walks a vector through this+0x2C and this+0x34,
// which are two of the three words this constructor zeroes.
//
// Layout read off the store sequence. The base's two fields and the vtable come
// first, then the members that have constructors in declaration order, then the
// constructor body's plain assignments:
//
//   +0x04/+0x08  Overridable's m_nextOverride and m_isAllocatedOverride
//   +0x00        RankInfo's vtable (the base's store is dead and eliminated)
//   +0x0C        m_rankName, one zeroed word
//   +0x2C..+0x34 the ScienceVec, three zeroed words
//   +0x10..+0x28 seven words assigned in the body: 0, then five -1, then 0
//
// That the seven-word block is assigned after the vector is constructed is what
// places it between m_rankName and m_sciencesGranted: member constructors run in
// declaration order and all of them precede the body. Only the first and last of
// those seven carry reference names; BFME's five -1 words have no counterpart
// there and nothing in this body says what they are, so they stay unnamed.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable() : m_nextOverride(0), m_isAllocatedOverride(0) {}

	virtual void overridableAnchor();

private:
	Overridable *m_nextOverride;
	unsigned char m_isAllocatedOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}

private:
	void *m_data;
};

class ScienceVec
{
public:
	ScienceVec() : m_start(0), m_finish(0), m_endOfStorage(0) {}

private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/RankInfo.h
class RankInfo : public Overridable
{
public:
	RankInfo();

	UnicodeString	m_rankName;						// +0x0C
	int				m_skillPointsNeeded;			// +0x10
	int				_bfme_14;						// +0x14 .. +0x24: five words BFME
	int				_bfme_18;						//   initialises to -1; purpose unknown
	int				_bfme_1c;
	int				_bfme_20;
	int				_bfme_24;
	int				m_sciencePurchasePointsGranted;	// +0x28
	ScienceVec		m_sciencesGranted;				// +0x2C
};

RankInfo::RankInfo()
{
	m_skillPointsNeeded = 0;
	_bfme_14 = -1;
	_bfme_18 = -1;
	_bfme_1c = -1;
	_bfme_20 = -1;
	_bfme_24 = -1;
	m_sciencePurchasePointsGranted = 0;
}
