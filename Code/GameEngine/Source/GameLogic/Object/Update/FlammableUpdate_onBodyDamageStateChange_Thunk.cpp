// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FlammableUpdate's standard empty damage-state callback.

class DamageInfo;
enum BodyDamageType
{
};

class FlammableUpdate
{
public:
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo,
		BodyDamageType oldState, BodyDamageType newState);
};

// ?onBodyDamageStateChange@FlammableUpdate@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z
void FlammableUpdate::onBodyDamageStateChange(const DamageInfo *,
	BodyDamageType, BodyDamageType)
{
}
