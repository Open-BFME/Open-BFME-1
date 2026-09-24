// cl: /DNDEBUG /MD
//
// Retail 0x001B9C10: query the locomotor-side helper then test query*0.25
// against the float at this+0x3C.

class BfmeSub1CC_EC3
{
public:
	float effectiveMaxSpeed(void *object);
	int queryBelowQuarter(void *object);

private:
	unsigned char m_pad[0x3C];
	float m_speedThreshold;
};

int BfmeSub1CC_EC3::queryBelowQuarter(void *object)
{
	float limit = m_speedThreshold;
	return effectiveMaxSpeed(object) * 0.25f < limit;
}
