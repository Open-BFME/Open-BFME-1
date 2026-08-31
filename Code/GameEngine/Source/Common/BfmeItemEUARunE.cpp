// cl: /DNDEBUG /MD /EHsc

class BfmePlayerSpecialPowerState
{
private:
	unsigned int m_unmodelled_00;
};

class BfmeSpecialPowerAllowanceStore
{
public:
	void bfmeRunEUAe(BfmePlayerSpecialPowerState *state, void *context);
};

extern BfmeSpecialPowerAllowanceStore *TheBfmeSpecialPowerAllowanceStore;

class BfmeItemEUA
{
public:
	void bfmeRunEUAe(void *context);

private:
	unsigned char m_unmodelled_000[0x274];
	BfmePlayerSpecialPowerState m_specialPowerState;
};

void BfmeItemEUA::bfmeRunEUAe(void *context)
{
	if (TheBfmeSpecialPowerAllowanceStore)
	{
		TheBfmeSpecialPowerAllowanceStore->bfmeRunEUAe(&m_specialPowerState, context);
	}
}
