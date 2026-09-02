// cl: /DNDEBUG /MD
//
// Retail 0x001B9590: cached wrapper around BfmeSub1CC_EC3::query.  When the
// dword at this+0x5C is still the current TheGameLogic frame the cached float
// at +0x58 is returned; otherwise the call tails into query.

class GameLogic
{
public:
	unsigned char m_pad[0x3C];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class BfmeSub1CC_EC3
{
public:
	float query(void *val);
	float queryCached(void *val);

private:
	unsigned char m_pad[0x58];
	float m_cached;
	unsigned int m_frame;
};

float BfmeSub1CC_EC3::queryCached(void *val)
{
	if (m_frame < TheGameLogic->m_frame)
		return query(val);
	return m_cached;
}
