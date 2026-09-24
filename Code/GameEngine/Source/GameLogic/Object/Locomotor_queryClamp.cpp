// cl: /DNDEBUG /MD
//
// Retail 0x001B9B50 clamps this+0x3C toward a limit, then clamps the
// queried value against zero and that limit.
//
// The neighboring locomotor methods use the same class declaration in their
// own translation units. This file repeats only the fields and calls that
// this member needs.
//
// The first branch updates the cached value by the minimum query result.
// The second branch keeps the caller's limit when the cache is already high.
// The final query supplies the upper bound for the cached value.

class BfmeSub1CC_EC3
{
public:
	float effectiveMaxSpeed(void *val);
	float queryDivMin40(void *val);
	void queryClamp(float limit, void *val);

private:
	char m_pad[0x3C];
	float m_value;
};

extern float g_bfmeZeroCY;

void BfmeSub1CC_EC3::queryClamp(float limit, void *val)
{
	if (limit > m_value)
	{
		m_value = m_value + queryDivMin40(val);
		if (m_value > limit)
			m_value = limit;
	}
	else
		m_value = limit;

	// Keep the query result in the x87 stack while the cached value is tested.
	float q = effectiveMaxSpeed(val);
	// MSVC 7.1 needs this spill to retain the retail floating-point ordering.
	volatile float result = m_value;
	if (result < g_bfmeZeroCY)
		m_value = 0.0f;
	else if (result > q)
		m_value = q;
	else
		m_value = result;
}
