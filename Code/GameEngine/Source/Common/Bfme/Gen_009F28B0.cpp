// ?m@Gen_009F28B0@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc

struct Gen_009F28B0Value
{
	float m_value0;
	float m_value1;
	float m_value2;
	float m_value3;
	float m_value4;
	float m_value5;

	Gen_009F28B0Value()
	{
		m_value0 = 0;
		m_value1 = 0;
		m_value2 = 0;
		m_value3 = 0;
		m_value4 = 0;
		m_value5 = 0;
	}
};

struct T_009f4fb0
{
	void m(void);
};

typedef void (T_009f4fb0::*T_009F28B0Method)(Gen_009F28B0Value *value);

class Gen_009F28B0
{
public:
	void m(void);

private:
	unsigned char m_unmodelled_000[0x0C];
	T_009f4fb0 *m_target;
};

void Gen_009F28B0::m(void)
{
	T_009f4fb0 *target = m_target;
	(target->*(T_009F28B0Method)&T_009f4fb0::m)(
		&Gen_009F28B0Value());
}
