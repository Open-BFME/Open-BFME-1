// ?advance@Rva002D0510Behavior@@QAEHXZ
// partial score=0.86 date=2026-09-09
// experiment v1: single combined guard `busy > 0 || isEmpty()`, where
// isEmpty() is an inline bool accessor -- trying to reproduce retail's
// sete/test/je idiom for the inner ammo==0 check via an inlined bool return.
// cl: /DNDEBUG /MD /EHsc

class Rva002D0510Behavior
{
public:
	int advance();

private:
	bool isAmmoEmpty() const { return m_ammo == 0; }

	unsigned char m_pad00[0x14];
	int m_ammo;
	unsigned char m_pad18[0x2C - 0x14 - 4];
	unsigned int m_reloadTimer;
};

int Rva002D0510Behavior::advance()
{
	if (m_reloadTimer > 0 || isAmmoEmpty())
	{
		m_ammo = 0;
		return 1;
	}

	--m_ammo;
	return 1;
}
