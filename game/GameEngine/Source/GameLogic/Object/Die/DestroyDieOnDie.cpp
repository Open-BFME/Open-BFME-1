// DestroyDie::onDie at retail 0x002550A0 (50 B): slot 0 of the DieModuleInterface
// table 0x010B2D08, which DestroyDie's registered constructor 0x00254F80 stores
// at +0x10. The body is reached only through ILT 0x0001E718, whose VA appears
// once in the image. Zero Hour's DieModuleInterface declares one virtual,
// onDie(const DamageInfo *), and the body is Zero Hour's DestroyDie::onDie:
// return unless isDieApplicable(damageInfo) (the +0x8 die-mux helper of the
// module data), then TheGameLogic->destroyObject(getObject()), tail-called.
// Evidence: targets/game/reverse/identity_evidence/diemodule-slot0-ondie.md
// Moved from BfmeConv1025.cpp.

class Object;
class DamageInfo;

// retail ILT 0x000357D8 -> 0x002551F0 is the matched
// DieMuxData::isDieApplicable row
class DieMuxData
{
public:
	bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;
};

class BfmeT1025
{
};

struct BfmeOwner1025
{
	char m_bfmePad[8];
	BfmeT1025 m_bfmeTab;
};


// The retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined
// once in game/GameEngine/Source/GameLogic/System/GameLogic.cpp. The call below
// is the matched GameLogic::destroyObject row (ILT 0x0001D0DE -> 0x0038B0C0).
class GameLogic
{
public:
	void destroyObject(Object *obj);
};
extern GameLogic *TheGameLogic;

class DestroyDie
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
};

void DestroyDie::onDie(const DamageInfo *damageInfo)
{
	void *h = *(void **)((char *)this - 8);
	BfmeOwner1025 *o = *(BfmeOwner1025 **)((char *)this - 0xc);

	if (((const DieMuxData *)&o->m_bfmeTab)->isDieApplicable((const Object *)h, damageInfo))
		TheGameLogic->destroyObject(*(Object **)((char *)this - 8));
}
