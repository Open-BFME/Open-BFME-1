// cl: /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Five 46-byte bodies with one shape: build a two-byte flag pair on the stack
// with both bytes set, hand its address to slot 10 of the argument's vtable,
// and then pass the argument itself to a member of the sub-object at +0x1C.
//
//     mov al, 1
//     lea ecx, [esp + 8]        the flag pair
//     mov [esp + 8], al
//     mov [esp + 9], al
//
// One immediate materialised into al and stored twice, so the two flags are
// set from the same value rather than from two literals. The lea rather than a
// load at +0x1C says that second object is embedded, not pointed to.
//
// Each second call reaches the corresponding FXParticleSystem module's
// DoXfer through its ILT entry. Qualify the call to preserve direct dispatch.

#include "../GameClient/System/FXParticleSystem/fx_particle_system.h"

struct BfmeFlagPair
{
	bool m_bfmeFirst;						// +0x00
	bool m_bfmeSecond;						// +0x01
};

class BfmeFlagTarget
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot0C(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot1C(void) = 0;
	virtual void bfmeSlot20(void) = 0;
	virtual void bfmeSlot24(void) = 0;
	virtual void bfmeApply(BfmeFlagPair *flags) = 0;		// +0x28
};

class Gen_005ee5a0
{
public:
	void bfmeRefresh(BfmeFlagTarget *target);

private:
	char m_bfmeHead[0x1C];
	FXParticleSystem::DefaultAlphaModuleInfo m_bfmeSub;	// +0x1C
};

class Gen_005ef8b0
{
public:
	void bfmeRefresh(BfmeFlagTarget *target);

private:
	char m_bfmeHead[0x1C];
	FXParticleSystem::DefaultColorModuleInfo m_bfmeSub;	// +0x1C
};

class Gen_005fe880
{
public:
	void bfmeRefresh(BfmeFlagTarget *target);

private:
	char m_bfmeHead[0x1C];
	FXParticleSystem::WindModuleInfo m_bfmeSub;			// +0x1C
};

class Gen_005ff8d0
{
public:
	void bfmeRefresh(BfmeFlagTarget *target);

private:
	char m_bfmeHead[0x1C];
	FXParticleSystem::DefaultUpdateModuleInfo m_bfmeSub;	// +0x1C
};

class Gen_00600710
{
public:
	void bfmeRefresh(BfmeFlagTarget *target);

private:
	char m_bfmeHead[0x1C];
	FXParticleSystem::RenderObjectUpdateModuleInfo m_bfmeSub;	// +0x1C
};

// ?bfmeRefresh@Gen_005ee5a0@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_005ee5a0::bfmeRefresh(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeApply(&flags);

	m_bfmeSub.FXParticleSystem::DefaultAlphaModuleInfo::DoXfer(
		*reinterpret_cast<Xfer *>(target));
}

// ?bfmeRefresh@Gen_005ef8b0@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_005ef8b0::bfmeRefresh(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeApply(&flags);

	m_bfmeSub.FXParticleSystem::DefaultColorModuleInfo::DoXfer(
		*reinterpret_cast<Xfer *>(target));
}

// ?bfmeRefresh@Gen_005fe880@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_005fe880::bfmeRefresh(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeApply(&flags);

	m_bfmeSub.FXParticleSystem::WindModuleInfo::DoXfer(
		*reinterpret_cast<Xfer *>(target));
}

// ?bfmeRefresh@Gen_005ff8d0@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_005ff8d0::bfmeRefresh(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeApply(&flags);

	m_bfmeSub.FXParticleSystem::DefaultUpdateModuleInfo::DoXfer(
		*reinterpret_cast<Xfer *>(target));
}

// ?bfmeRefresh@Gen_00600710@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_00600710::bfmeRefresh(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeApply(&flags);

	m_bfmeSub.FXParticleSystem::RenderObjectUpdateModuleInfo::DoXfer(
		*reinterpret_cast<Xfer *>(target));
}
