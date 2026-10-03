class BfmeFlagHH
{
public:
	unsigned char m_bfmeGapHH[0x40];
	int m_bfmeFlagsHH;
};

class BfmeCtrlHH
{
public:
	virtual void bfmeVtHH000();
	virtual void bfmeVtHH001();
	virtual void bfmeVtHH002();
	virtual void bfmeVtHH003();
	virtual void bfmeVtHH004();
	virtual void bfmeVtHH005();
	virtual void bfmeVtHH006();
	virtual void bfmeVtHH007();
	virtual void bfmeVtHH008();
	virtual void bfmeVtHH009();
	virtual void bfmeVtHH010();
	virtual void bfmeVtHH011();
	virtual void bfmeVtHH012();
	virtual void bfmeVtHH013();
	virtual void bfmeVtHH014();
	virtual void bfmeVtHH015();
	virtual void bfmeVtHH016();
	virtual void bfmeVtHH017();
	virtual void bfmeVtHH018();
	virtual void bfmeVtHH019();
	virtual void bfmeVtHH020();
	virtual void bfmeVtHH021();
	virtual void bfmeVtHH022();
	virtual void bfmeVtHH023();
	virtual void bfmeVtHH024();
	virtual void bfmeVtHH025();
	virtual void bfmeVtHH026();
	virtual void bfmeVtHH027();
	virtual void bfmeVtHH028();
	virtual void bfmeVtHH029();
	virtual void bfmeVtHH030();
	virtual void bfmeVtHH031();
	virtual void bfmeVtHH032();
	virtual void bfmeVtHH033();
	virtual void bfmeVtHH034();
	virtual void bfmeVtHH035();
	virtual void bfmeVtHH036();
	virtual void bfmeVtHH037();
	virtual void bfmeVtHH038();
	virtual void bfmeVtHH039();
	virtual void bfmeVtHH040();
	virtual void bfmeVtHH041();
	virtual void bfmeVtHH042();
	virtual void bfmeVtHH043();
	virtual void bfmeVtHH044();
	virtual void bfmeVtHH045();
	virtual void bfmeVtHH046();
	virtual void bfmeVtHH047();
	virtual void bfmeVtHH048();
	virtual void bfmeVtHH049();
	virtual void bfmeVtHH050();
	virtual void bfmeVtHH051();
	virtual void bfmeVtHH052();
	virtual void bfmeVtHH053();
	virtual void bfmeVtHH054();
	virtual void bfmeVtHH055();
	virtual void bfmeVtHH056();
	virtual void bfmeVtHH057();
	virtual void bfmeVtHH058();
	virtual void bfmeVtHH059();
	virtual void bfmeVtHH060();
	virtual void bfmeVtHH061();
	virtual void bfmeVtHH062();
	virtual void bfmeVtHH063();
	virtual void bfmeVtHH064();
	virtual void bfmeVtHH065();
	virtual void bfmeVtHH066();
	virtual void bfmeVtHH067();
	virtual void bfmeVtHH068();
	virtual void bfmeVtHH069();
	virtual void bfmeVtHH070();
	virtual void bfmeVtHH071();
	virtual void bfmeVtHH072();
	virtual void bfmeVtHH073();
	virtual void bfmeVtHH074();
	virtual void bfmeVtHH075();
	virtual void bfmeVtHH076();
	virtual void bfmeVtHH077();
	virtual void bfmeVtHH078();
	virtual void bfmeVtHH079();
	virtual void bfmeVtHH080();
	virtual void bfmeVtHH081();
	virtual void bfmeVtHH082();
	virtual void bfmeVtHH083();
	virtual void bfmeVtHH084();
	virtual void bfmeVtHH085();
	virtual void bfmeVtHH086();
	virtual void bfmeVtHH087();
	virtual void bfmeVtHH088();
	virtual void bfmeVtHH089();
	virtual void bfmeVtHH090();
	virtual void bfmeVtHH091();
	virtual void bfmeVtHH092();
	virtual void bfmeVtHH093();
	virtual void bfmeVtHH094();
	virtual void bfmeVtHH095();
	virtual void bfmeVtHH096();
	virtual void bfmeVtHH097();
	virtual void bfmeVtHH098();
	virtual void bfmeVtHH099();
	virtual void bfmeVtHH100();
	virtual void bfmeVtHH101();
	virtual void bfmeVtHH102();
	virtual void bfmeVtHH103();
	virtual void bfmeVtHH104();
	virtual void bfmeVtHH105();
	virtual void bfmeVtHH106();
	virtual void bfmeVtHH107();
	virtual void bfmeVtHH108();
	virtual void bfmeVtHH109();
	virtual void bfmeVtHH110();
	virtual void bfmeVtHH111();
	virtual void bfmeVtHH112();
	virtual void bfmeVtHH113();
	virtual void bfmeVtHH114();
	virtual void bfmeVtHH115();
	virtual void bfmeVtHH116();
	virtual void bfmeVtHH117();
	virtual void bfmeVtHH118();
	virtual void bfmeVtHH119();
	virtual void bfmeVtHH120();
	virtual void bfmeVtHH121();
	virtual void bfmeVtHH122();
	virtual void bfmeVtHH123();
	virtual void bfmeVtHH124();
	virtual void bfmeVtHH125();
	virtual void bfmeVtHH126();
	virtual void bfmeApplyHH(int a);

	unsigned char m_bfmeGapHH[0x1c8];
	BfmeFlagHH *m_bfmeFlagHH;
};

// The receiver of bfmeSomethingHH is an Object: the tested and cleared word
// is Object::m_modelConditionFlags[3] at +0x11C, the controller at +0x204 is
// Object::m_ai, and the call is the ILT 0x0002191D thunk to
// Object::notifyModelConditionChanged.
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "../GameLogic/Object/object.h"

class BfmeOwnerHH
{
public:
	unsigned char m_bfmeGapHH[0x10];
	Object *m_bfmeThingHH;
};

class BfmeSelfHH
{
public:
	void bfmeResetHH(void *p);

	unsigned char m_bfmeGapHH[0x1c];
	BfmeOwnerHH *m_bfmeOwnerHH;
};

// Retail's call at 0x0017B28D reaches the ILT 0x00029311, the ledger's
// ?onExit@AIInternalMoveToState@@UAEXW4StateExitType@@@Z
// (AIInternalMoveToStateOnExitShim.cpp), through ECX with one stack word that
// the thunk's tail jump consumes with `ret 4`.
enum StateExitType
{
};

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType);
};

void BfmeSelfHH::bfmeResetHH(void *p)
{
	((AIInternalMoveToState *)this)->AIInternalMoveToState::onExit((StateExitType)(int)p);

	BfmeCtrlHH *c = (BfmeCtrlHH *)m_bfmeOwnerHH->m_bfmeThingHH->m_ai;

	if (c != 0)
	{
		BfmeFlagHH *f = c->m_bfmeFlagHH;

		if (f != 0)
			f->m_bfmeFlagsHH &= ~8;
	}

	Object *t = m_bfmeOwnerHH->m_bfmeThingHH;

	if (t != 0)
	{
		if (t->m_modelConditionFlags[3] & 0x4000000)
		{
			t->m_modelConditionFlags[3] &= ~0x4000000;
			t->notifyModelConditionChanged();
		}

		((BfmeCtrlHH *)t->m_ai)->bfmeApplyHH(0);
	}
}
