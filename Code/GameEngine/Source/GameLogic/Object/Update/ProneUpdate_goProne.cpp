// cl: /DNDEBUG /MD /EHsc

// ProneUpdate::goProne, retail 0x002A0120. Zero Hour's body unchanged: remember
// whether the object was already prone, take the damage actually dealt, add
// damage times the module data's ratio to the prone frame count, and start the
// effects only on the transition into prone.
//
// The arithmetic is what the two __ftol2 calls are. The damage dealt is a Real
// at damageInfo+0x50 truncated to an Int, then multiplied by the ratio at
// module data +0x08 as a float, added to the old frame count with fiadd, and
// truncated back. Retail computes the was-prone test before any of it, which is
// what reading m_proneFrames into a local first compiles to.

typedef int Int;
typedef float Real;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	unsigned char m_unmodelled_00[ 0x50 ];
	Real m_actualDamageDealt;				// +0x50, in the output half
	unsigned char m_unmodelled_54[ 0x5C - 0x54 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProneUpdate.h
struct ProneUpdateModuleData
{
	unsigned char m_unmodelled_00[ 8 ];
	Real m_damageToFramesRatio;				// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProneUpdate.h
class ProneUpdate
{
public:
	void goProne( const DamageInfo *damageInfo );

private:
	void startProneEffects();				// ILT thunk at 0x00042884

	const ProneUpdateModuleData *getProneUpdateModuleData() const
	{
		return m_moduleData;
	}

	unsigned int m_unmodelled_00;
	const ProneUpdateModuleData *m_moduleData;	// +0x04
	unsigned char m_unmodelled_08[ 0x20 - 8 ];
	Int m_proneFrames;						// +0x20
};

// ?goProne@ProneUpdate@@QAEXPBVDamageInfo@@@Z
void ProneUpdate::goProne( const DamageInfo *damageInfo )
{
	//add to the prone time
	Bool wasProne = ( m_proneFrames > 0 );
	Int damageTaken = (Int)damageInfo->m_actualDamageDealt;
	m_proneFrames = (Int)( damageTaken * getProneUpdateModuleData()->m_damageToFramesRatio + m_proneFrames );

	if( !wasProne && ( m_proneFrames > 0 ) )
		startProneEffects();
}
