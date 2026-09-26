// Address-derived identity.  The body at 0x009A2420 is reached only from the
// opaque collision refresh loop 0x009A3AD0 (two call sites), so the owning
// class stays address-qualified.  Boundary is independently proven: RET 4 at
// +0xF9 with INT3 padding at +0xFC.
//
// Naming: "Collision" has neighbourhood support -- the CollisionManager ctor
// sits at 0x009A25B0, and Rva009A45A0CollisionData's dtor 0x009A2390 is also
// called by the same caller 0x009A3AD0.  "Node" and "Source" are descriptors
// only.  The method word getMovementScore is an unproven descriptor, kept
// because the matched row landed under that symbol; the class carries the
// address token.  The bytes show only this: return 1 with no source; return 0
// when slot05's int equals the cached int at +0xA0 while +0x24 is non-null and
// the bool argument is set; otherwise 11 - ftol((max(|d0|,|d1|) - 50.0f) *
// BfmeShadowZLimit), unsigned-clamped at 10000, or 1 below the threshold.  That
// value could equally be an update interval or a priority countdown.
//
// The node caches the source's slot05 int at +0xA0 and six Reals: slot01's
// Real[3] output at +0x34/+0x5C/+0x84 (the first two are diffed against the
// fresh output before being overwritten) and slot00's Real[3] output at
// +0x48/+0x70/+0x98.  The 50.0f threshold at 0x0107FAA8 has no ledger pin, so
// it is referenced through its absolute address the same way
// Rva006FCC10NormalizedRange.cpp does; the scale at 0x010F0ADC is the pinned
// BfmeShadowZLimit global (symbols.csv ?BfmeShadowZLimit@@3MB).
//
// cl: /O2 /DNDEBUG /MD /EHs-c-

typedef float Real;

#include <math.h>

class Rva009A2420CollisionSource
{
public:
	// Slots 0 and 1 each fill a caller-provided Real[3]; nothing in the bytes
	// says which is current and which is previous.
	virtual void slot00(Real *value) = 0;
	virtual void slot01(Real *value) = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	// Slot 5 (+0x14) returns an int compared against the cached int at +0xA0.
	virtual int slot05() = 0;
};

// 0x0107FAA8 carries no symbols.csv pin; reference it by address rather than
// invent one (see game/GameEngine/Source/Common/Rva006FCC10NormalizedRange.cpp).
#define Rva009A2420MoveThreshold (*(const Real *)0x0107FAA8)

extern const Real BfmeShadowZLimit;

class Rva009A2420CollisionNode
{
public:
	unsigned int getMovementScore(bool allowCache);

private:
	unsigned char m_beforeSource[4];
	Rva009A2420CollisionSource *m_source;
	unsigned char m_beforeFlag[0x1c];
	void *m_flag;
	unsigned char m_beforeValue34[0xc];
	Real m_value34;
	unsigned char m_beforeValue48[0x10];
	Real m_value48;
	unsigned char m_beforeValue5c[0x10];
	Real m_value5c;
	unsigned char m_beforeValue70[0x10];
	Real m_value70;
	unsigned char m_beforeValue84[0x10];
	Real m_value84;
	unsigned char m_beforeValue98[0x10];
	Real m_value98;
	unsigned char m_beforeCachedVersion[4];
	int m_cachedVersion;
};

unsigned int Rva009A2420CollisionNode::getMovementScore(bool allowCache)
{
	if (m_source == 0)
		return 1;

	int version = m_source->slot05();
	if (version != m_cachedVersion)
		m_cachedVersion = version;
	else if (m_flag != 0 && allowCache)
		return 0;

	Real current[3];
	Real previous[3];
	m_source->slot00(current);
	m_source->slot01(previous);

	unsigned int score = 1;
	Real deltaX = (Real)fabs(m_value34 - previous[0]);
	Real deltaY = (Real)fabs(m_value5c - previous[1]);
	Real distance;
	if (deltaX > deltaY)
		distance = deltaX;
	else
		distance = deltaY;
	if (distance > Rva009A2420MoveThreshold)
	{
		score = 11 - (int)((distance - Rva009A2420MoveThreshold) * BfmeShadowZLimit);
		if (score > 10000)
			score = 10000;
	}

	m_value48 = current[0];
	m_value34 = previous[0];
	m_value70 = current[1];
	m_value5c = previous[1];
	m_value98 = current[2];
	m_value84 = previous[2];
	return score;
}
