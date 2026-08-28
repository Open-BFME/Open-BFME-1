// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?newOverride@LocomotorStore@@QAEPAVLocomotorTemplate@@PAV2@@Z: Code/GameEngine/Source/GameLogic/Object/Locomotor.cpp
// Open-BFME5: LocomotorStore::newOverride, retail 0x001B55D0,
// zh_sweep packet 001b55d0.
//
// The Zero Hour body unchanged, and compiled against Locomotor.cpp's headers
// it already reproduced every byte -- including both Overridable offsets,
// m_nextOverride at +0x04 and the override flag at +0x08, which setNextOverride
// and markAsOverride are inlined into -- except one immediate: retail allocates
// 0x140 bytes where the vendored LocomotorTemplate is 0xEC. BFME's is 84 bytes
// wider.
//
// So this is a pure sizeof drift, and it gets its own TU: Locomotor.cpp carries
// 45 other matched rows compiled against the narrower class, and the width has
// to change for this body alone. Only the three offsets retail proves are named
// below; the rest of the class is carried as one opaque run rather than
// invented members.
//
// newInstance(LocomotorTemplate) is a plain ::new here -- allocate, null-check,
// construct -- with no EH frame, so the pool glue is not in the path.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class LocomotorTemplate
{
public:
	LocomotorTemplate();											///< ILT 0x0000D049
	LocomotorTemplate &operator=(const LocomotorTemplate &that);	///< ILT 0x00038FAA

	void setNextOverride( LocomotorTemplate *o ) { m_nextOverride = o; }
	void markAsOverride( void ) { m_isOverride = true; }

private:
	void *m_unreconstructed_00;										///< +0x00
	LocomotorTemplate *m_nextOverride;								///< +0x04
	bool m_isOverride;												///< +0x08
	unsigned char m_unreconstructed_09[0x140 - 9];					///< out to sizeof 0x140
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class LocomotorStore
{
public:
	LocomotorTemplate *newOverride( LocomotorTemplate *locoTemplate );
};

//-------------------------------------------------------------------------------------------------
// ?newOverride@LocomotorStore@@QAEPAVLocomotorTemplate@@PAV2@@Z
LocomotorTemplate *LocomotorStore::newOverride( LocomotorTemplate *locoTemplate )
{
	if (locoTemplate == 0)
		return 0;

	// allocate new template
	LocomotorTemplate *newTemplate = ::new LocomotorTemplate;

	// copy data from final override to 'newTemplate' as a set of initial default values
	*newTemplate = *locoTemplate;
	locoTemplate->setNextOverride(newTemplate);

	newTemplate->markAsOverride();

	// return the newly created override for us to set values with etc
	return newTemplate;

}  // end newOverride
