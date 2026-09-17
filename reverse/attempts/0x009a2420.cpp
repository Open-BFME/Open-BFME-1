// ?d_009a2420@@YAXXZ
// partial score=0.9 date=2026-09-06
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

extern Real g_0107FAA8;
extern Real g_010F0ADC;

class Rva009A2420CollisionNode
{
public:
	int getMovementScore(int unused);

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

int Rva009A2420CollisionNode::getMovementScore(int unused)
{
	if (m_source == 0)
		return 1;

	int version = m_source->getVersion();
	if (version == m_cachedVersion)
		goto check_cached;

	refresh:
	m_cachedVersion = version;
	Real current[3];
	Real previous[3];
	m_source->getCurrent(current);
	m_source->getPrevious(previous);

	int result = 1;
	Real distance = (Real)fabs(m_value34 - previous[0]);
	if (distance <= (Real)fabs(m_value5c - previous[1]))
		distance = (Real)fabs(m_value5c - previous[1]);
	if (!(distance <= g_0107FAA8))
	{
		result = 11 - (int)((distance - g_0107FAA8) * g_010F0ADC);
		if (result > 10000)
			result = 10000;
	}

	m_value34 = previous[0];
	m_value48 = current[0];
	m_value5c = previous[1];
	m_value70 = current[1];
	m_value84 = previous[2];
	m_value98 = current[2];
	return result;

	check_cached:
	if (m_flag == 0 || unused == 0)
		goto refresh;
	return 0;
}
