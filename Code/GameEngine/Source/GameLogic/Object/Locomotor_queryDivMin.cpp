// cl: /DNDEBUG /MD
//
// Retail 0x001B8010 / 0x001B8070: resolve the locomotor template override
// chain then return min(query(arg) / (float)unsigned(field), this-cap).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	char m_pad00[4];
	const Overridable *m_nextOverride;
	char m_pad08[0x38];
	int m_40;
	char m_pad44[8];
	int m_4C;
};

class BfmeSub1CC_EC3
{
public:
	float query(void *val);
	float queryDivMin40(void *val);
	float queryDivMin4C(void *val);

private:
	char m_pad00[4];
	const Overridable *m_template;
	char m_pad08[0x24];
	float m_2C;
	float m_30;
};

float BfmeSub1CC_EC3::queryDivMin40(void *val)
{
	float q = query(val);
	const Overridable *t = m_template;
	if (t != 0 && t->m_nextOverride != 0)
		t = t->m_nextOverride->getFinalOverride();
	float d = (float)(unsigned)t->m_40;
	float r = q / d;
	if (r > m_2C)
		r = m_2C;
	return r;
}

float BfmeSub1CC_EC3::queryDivMin4C(void *val)
{
	float q = query(val);
	const Overridable *t = m_template;
	if (t != 0 && t->m_nextOverride != 0)
		t = t->m_nextOverride->getFinalOverride();
	float d = (float)(unsigned)t->m_4C;
	float r = q / d;
	if (r > m_30)
		r = m_30;
	return r;
}
