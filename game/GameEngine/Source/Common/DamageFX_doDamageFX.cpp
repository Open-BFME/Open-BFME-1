// cl: /DNDEBUG /MD /EHsc
// BFME DamageFX::doDamageFX, retail 0x00066780, returns whether an effect exists.
// The ActiveBody caller at 0x0020F240 passes the damage type, amount, source, and
// victim, then tests AL. The four-level DFX records use a 0x40-byte type stride.

typedef float Real;
typedef bool Bool;

enum DamageType
{
	DAMAGE_TYPE_ZERO
};

class Object;

class FXList
{
public:
	Bool bfmeIsBlocked() const;
	void doFXObj(const Object *primary, const Object *secondary) const;
};

extern const float BfmeZeroRange;

class DamageFX
{
	struct DFX
	{
		Real m_amountForMajorFX;
		const FXList *m_majorDamageFXList;
		const FXList *m_minorDamageFXList;
		unsigned int m_damageFXThrottleTime;
	};

	DFX m_dfx[16][4];

public:
	Bool doDamageFX(DamageType t, Real damageAmount, const Object *source, const Object *victim) const;
};

Bool DamageFX::doDamageFX(DamageType t, Real damageAmount, const Object *source, const Object *victim) const
{
	const FXList *fx = 0;

	if (damageAmount != BfmeZeroRange)
	{
		unsigned int offset = (unsigned int)t << 6;
		const DFX *dfx = reinterpret_cast<const DFX *>(
			offset + (unsigned int)this);
		if (damageAmount >= *(const Real *)dfx)
			fx = dfx->m_majorDamageFXList;
		else
			fx = dfx->m_minorDamageFXList;
	}

	if (fx == 0)
		return false;

	if (!fx->bfmeIsBlocked())
		fx->doFXObj(victim, source);

	return true;
}
