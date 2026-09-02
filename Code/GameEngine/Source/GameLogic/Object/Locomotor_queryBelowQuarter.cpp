// cl: /DNDEBUG /MD
//
// Retail 0x001B9C10: query the locomotor-side helper then test query*0.25
// against the float at this+0x3C.

class BfmeSub1CC_EC3
{
public:
	float query(void *val);
	int queryBelowQuarter(void *val);

private:
	unsigned char m_pad[0x3C];
	float m_value;
};

int BfmeSub1CC_EC3::queryBelowQuarter(void *val)
{
	float limit = m_value;
	return query(val) * 0.25f < limit;
}
