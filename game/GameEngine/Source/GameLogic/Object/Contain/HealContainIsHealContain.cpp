// cl: /DNDEBUG /MD /EHsc
// HealContain::isHealContain, retail 0x00220230 (3 bytes, `mov al,1 / ret`):
// the ContainModuleInterface query HealContain alone answers true. Identity:
// targets/game/reverse/identity_evidence/containmodule-slot4-ishealcontain.md.

typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HealContain.h
class HealContain
{
public:
	virtual Bool isHealContain() const;
};

// ?isHealContain@HealContain@@UBE_NXZ
Bool HealContain::isHealContain() const
{
	return true;
}
