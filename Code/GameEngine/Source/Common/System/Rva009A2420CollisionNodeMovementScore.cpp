// Address-derived identity.  The body at 0x009A2420 is reached only from the
// opaque collision refresh loop 0x009A3AD0 (two call sites), so the owning
// class stays address-qualified.  Boundary is independently proven: RET 4 at
// +0xF9 with INT3 padding at +0xFC.
//
// The node caches a source object's version at +0xA0 and six coordinates at
// +0x34/+0x48/+0x5C/+0x70/+0x84/+0x98 (previous/current interleaved).  The
// 50.0f threshold at 0x0107FAA8 has no ledger pin, so it is referenced through
// its absolute address the same way Rva006FCC10NormalizedRange.cpp does; the
// scale at 0x010F0ADC is pinned as ?BfmeShadowZLimit@@3MB.
//
// cl: /O2 /DNDEBUG /MD /EHs-c-

typedef float Real;

#include <math.h>

class Rva009A2420CollisionSource
{
public:
	virtual void getCurrent(Real *value) = 0;
	virtual void getPrevious(Real *value) = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual int getVersion() = 0;
};

// 0x0107FAA8 carries no symbols.csv pin; reference it by address rather than
// invent one (see Code/GameEngine/Source/Common/Rva006FCC10NormalizedRange.cpp).
#define Rva009A2420MoveThreshold (*(const Real *)0x0107FAA8)

extern const Real BfmeShadowZLimit;

class Rva009A2420CollisionNode
{
public:
	unsigned int getMovementScore(bool allowCache);

private:
	void *m_link;
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

	int version = m_source->getVersion();
	if (version != m_cachedVersion)
		m_cachedVersion = version;
	else if (m_flag != 0 && allowCache)
		return 0;

	Real current[3];
	Real previous[3];
	m_source->getCurrent(current);
	m_source->getPrevious(previous);

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
