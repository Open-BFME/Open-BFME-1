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
	unsigned char m_beforeX[0xc];
	Real m_x;
	unsigned char m_betweenXAndY[0x10];
	Real m_y;
	unsigned char m_betweenYAndZ[0x10];
	Real m_z;
	unsigned char m_afterZ[0x40];
	int m_cachedVersion;
};

int Rva009A2420CollisionNode::getMovementScore(int unused)
{
	if (m_source == 0)
		return 1;

	int version = m_source->getVersion();
	if (version != m_cachedVersion)
		goto refresh;
	if (m_flag != 0 && unused == 0)
		return 0;

	refresh:
	m_cachedVersion = version;
	Real current[4];
	Real previous[3];
	m_source->getCurrent(current);
	m_source->getPrevious(previous);

	int result = 1;
	Real distance = (Real)fabs(m_x - previous[0]);
	if (distance <= (Real)fabs(m_z - previous[1]))
		distance = (Real)fabs(m_z - previous[1]);
	if (!(distance <= g_0107FAA8))
	{
		result = 11 - (int)((distance - g_0107FAA8) * g_010F0ADC);
		if (result > 10000)
			result = 10000;
	}

	if (m_flag != 0 && (unsigned char)distance == 0)
		return 0;

	m_x = previous[0];
	m_y = current[0];
	m_z = previous[1];
	return result;
}
