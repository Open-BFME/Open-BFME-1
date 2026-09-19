// BFME-specific Drawable reconstructions whose upstream bodies differ from Zero Hour.
// readable body of ?clearAndSetModelConditionFlags@Drawable@@QAEXABV?$BitFlags@$0HF@@@0@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?enableAmbientSoundFromScript@Drawable@@QAEX_N@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?friend_clearSelected@Drawable@@QAEXXZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?friend_setSelected@Drawable@@QAEXXZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?getBarrelCount@Drawable@@QBEHW4WeaponSlotType@@@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?getProjectileLaunchOffset@Drawable@@QBE_NW4WeaponSlotType@@HPAVMatrix3D@@W4WhichTurretType@@PAUCoord3D@@3@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
//
// Three more BFME-only members join them, all of which reach the object the
// drawable is attached to at this+0xFC:
//
//   bfmeNotifyCondition4Modules  0x0041A290   54 B
//   bfmeRegionDispatch           0x0041AA00  114 B
//   bfmeVisibilityGate           0x0041B8B0  128 B
//
// Each had described the drawable's head as one anonymous run -- 0x150 bytes
// in one file, 0xFC in the next two -- and the object pointer they all load is
// the same field, so it is named once here and the head splits around it.
//
// DrawModule was the sharper drift. This file ended its vtable at slot 39,
// getObjectDrawInterface; the condition-module file ended its own copy at slot
// 58 with the condition-4 callback and had nothing at 39. Neither file was
// wrong and neither could tell you it was partial. The table below carries
// both, so the two calls sit in one vtable at 0x9C and 0xE8.
//
// The object itself is a Thing -- the region dispatch asks Thing::isKindOf
// while the visibility gate walks Object's own template and team -- but see
// the note on Object below for why the model states that in a cast rather than
// in a base clause.
class ModelConditionFlags
{
public:
	unsigned int m_bits[10];
	void clearAndSet(const ModelConditionFlags &clear, const ModelConditionFlags &set);
};

struct BfmeRecordOwnerRB
{
	unsigned char m_bfmeHead[0x110];
	ModelConditionFlags m_bfmeRecord;
};

enum WeaponSlotType { PRIMARY_WEAPON };
enum WhichTurretType { TURRET_INVALID };
class Matrix3D { unsigned char m[48]; };
struct Coord3D { float x, y, z; };

enum KindOfType
{
	KINDOF_STRUCTURE = 7
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Team;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOf( KindOfType kind ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_bfmePadding[ 0xC8 - 8 ];
	unsigned int m_kindOf[ 5 ];					// +0xc8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Relationship getRelationship( const Team *team ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
private:
	unsigned char m_bfmePadding[ 0x0C ];

public:
	Player *m_localPlayer;						// +0x0c
};

class BfmeTargetGate
{
public:
	virtual bool bfmeAllowsAttack() const;
};

class BfmeTargetGateModule
{
private:
	unsigned char m_bfmePadding[ 0x24 ];

public:
	BfmeTargetGate m_gate;						// +0x24
	volatile unsigned int m_objectID;				// +0x28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
// Retail's Object IS a Thing, but the model keeps them apart: MSVC lays an
// empty base down after the vptr rather than folding it to offset 0, so
// `class Object : public Thing` makes every Object* -> Thing* conversion emit
// a lea + null test that retail's region dispatch does not have. The dispatch
// casts instead, which is the conversion retail actually performs.
class Object
{
public:
	virtual void bfmeObjectSlot00();
	virtual void bfmeObjectSlot01();
	virtual void bfmeObjectSlot02();
	virtual void bfmeObjectSlot03();
	virtual void bfmeObjectSlot04();
	virtual void bfmeObjectSlot05();
	virtual void bfmeObjectSlot06();
	virtual void bfmeObjectSlot07();
	virtual void bfmeObjectSlot08();
	virtual void bfmeObjectSlot09();
	virtual int bfmeVisibilityResult() const;			// slot 10, vtable+0x28

	ThingTemplate *m_template;					// +0x04
	unsigned char m_bfmePadding04[ 0x118 - 8 ];
	unsigned int m_modelConditionWord0;				// +0x118
	unsigned char m_bfmePadding11c[ 0x23C - 0x11C ];
	Team *m_team;							// +0x23c

	ThingTemplate *getFinalTemplate() const
	{
		ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = (ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( int objectID );
};

extern BfmeTargetGateModule *bfmeFindTargetGate( const Object *object );
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;

extern void bfmeRegionRenderA( void *region, int first, int second );
extern void bfmeRegionRenderB( void *region, int first, int second );
extern void bfmeRegionRenderC( void *region, int first, int second );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &state, bool dirty, unsigned int effect);
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear, const ModelConditionFlags &set);
	int getBarrelCount(WeaponSlotType slot) const;
	bool getProjectileLaunchOffset(WeaponSlotType slot, int barrel, Matrix3D *launch,
		WhichTurretType turret, Coord3D *turretRotation, Coord3D *turretPitch) const;
	void enableAmbientSoundFromScript(bool enable);
	void friend_setSelected();
	void friend_clearSelected();
	void bfmeNotifyCondition4Modules(Object *object);
	void bfmeRegionDispatch(int first, int second);
	int bfmeVisibilityGate();

private:
	void applyPendingModelConditionFlags(bool immediate);
	void startAmbientSound(bool onlyIfPermanent);
	void refreshAmbientSound();
	unsigned char m_bfmeHead[0xfc];
	Object *m_object;						// +0x0fc
	unsigned char m_bfmeGap100[0x140 - 0x100];
	bool m_ambientSoundEnabled;
	bool m_ambientSoundEnabledFromScript;
	unsigned char m_bfmeGap142;
	bool m_selected;
	class DynamicAudioEventRTS *m_ambientSound;
	class DynamicAudioEventRTS *m_damagedAmbientSound;
	class DynamicAudioEventRTS *m_selectedAmbientSound;
	class DrawModule **m_drawModules;
	unsigned char m_bfmeGap154[4];
	class SelectionModule **m_selectionModules;
	unsigned char m_bfmeGap15c[0xf4];
	mutable ModelConditionFlags m_conditionState;
	mutable ModelConditionFlags m_pendingConditionClear;
	mutable ModelConditionFlags m_pendingConditionSet;
	unsigned char m_bfmeGap2c8[0xeb];
	mutable bool m_isModelDirty;
};

void Drawable::clearAndSetModelConditionFlags(const ModelConditionFlags &clear, const ModelConditionFlags &set)
{
	m_pendingConditionClear = clear;
	m_pendingConditionSet = set;
	applyPendingModelConditionFlags(true);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class ObjectDrawInterface
{
public:
	virtual void anchor00(); virtual void anchor04(); virtual void anchor08(); virtual void anchor0c();
	virtual void anchor10(); virtual void anchor14();
	virtual bool getProjectileLaunchOffset(const ModelConditionFlags &state, WeaponSlotType slot,
		int barrel, Matrix3D *launch, WhichTurretType turret, Coord3D *turretRotation,
		Coord3D *turretPitch);
	virtual void anchor1c();
	virtual void anchor20(); virtual void anchor24(); virtual void anchor28(); virtual void anchor2c();
	virtual void anchor30(); virtual void anchor34(); virtual void anchor38(); virtual void anchor3c();
	virtual void anchor40(); virtual void anchor44(); virtual void anchor48();
	virtual void replaceModelConditionState(const ModelConditionFlags &state, bool immediate, unsigned int effect);
	virtual void anchor50(); virtual void anchor54();
	virtual int getBarrelCount(int slot);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	virtual void anchor00(); virtual void anchor04(); virtual void anchor08(); virtual void anchor0c();
	virtual void anchor10(); virtual void anchor14(); virtual void anchor18(); virtual void anchor1c();
	virtual void anchor20(); virtual void anchor24(); virtual void anchor28(); virtual void anchor2c();
	virtual void anchor30(); virtual void anchor34(); virtual void anchor38(); virtual void anchor3c();
	virtual void anchor40(); virtual void anchor44(); virtual void anchor48(); virtual void anchor4c();
	virtual void anchor50(); virtual void anchor54(); virtual void anchor58(); virtual void anchor5c();
	virtual void anchor60(); virtual void anchor64(); virtual void anchor68(); virtual void anchor6c();
	virtual void anchor70(); virtual void anchor74(); virtual void anchor78(); virtual void anchor7c();
	virtual void anchor80(); virtual void anchor84(); virtual void anchor88(); virtual void anchor8c();
	virtual void anchor90(); virtual void anchor94(); virtual void anchor98();
	virtual ObjectDrawInterface *getObjectDrawInterface();		// slot 39, vtable+0x9c
	virtual void anchora0(); virtual void anchora4(); virtual void anchora8(); virtual void anchorac();
	virtual void anchorb0(); virtual void anchorb4(); virtual void anchorb8(); virtual void anchorbc();
	virtual void anchorc0(); virtual void anchorc4(); virtual void anchorc8(); virtual void anchorcc();
	virtual void anchord0(); virtual void anchord4(); virtual void anchord8(); virtual void anchordc();
	virtual void anchore0(); virtual void anchore4();
	virtual void bfmeCondition4Callback();				// slot 58, vtable+0xe8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class DynamicAudioEventRTS
{
public:
	unsigned char m_bfmeHead[0x10];
	unsigned int m_playingHandle;
};

class SelectionInterface
{
public:
	virtual void selected();
	virtual void unselected();
};

class SelectionModule
{
public:
	virtual void anchor00(); virtual void anchor04(); virtual void anchor08(); virtual void anchor0c();
	virtual void anchor10(); virtual void anchor14(); virtual void anchor18(); virtual void anchor1c();
	virtual void anchor20(); virtual void anchor24();
	virtual SelectionInterface *getSelectionInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void anchor00(); virtual void anchor04(); virtual void anchor08(); virtual void anchor0c();
	virtual void anchor10(); virtual void anchor14(); virtual void anchor18(); virtual void anchor1c();
	virtual void anchor20(); virtual void anchor24(); virtual void anchor28(); virtual void anchor2c();
	virtual void anchor30(); virtual void anchor34(); virtual void anchor38(); virtual void anchor3c();
	virtual void anchor40(); virtual void anchor44(); virtual void anchor48();
	virtual void removeAudioEvent(unsigned int handle);
};

extern AudioManager *TheAudio;

void Drawable::enableAmbientSoundFromScript(bool enable)
{
	m_ambientSoundEnabledFromScript = enable;
	if (enable)
	{
		startAmbientSound(false);
		refreshAmbientSound();
		return;
	}

	if (m_ambientSound)
		TheAudio->removeAudioEvent(m_ambientSound->m_playingHandle);
	if (m_damagedAmbientSound)
		TheAudio->removeAudioEvent(m_damagedAmbientSound->m_playingHandle);
	if (m_selectedAmbientSound)
		TheAudio->removeAudioEvent(m_selectedAmbientSound->m_playingHandle);
}

void Drawable::friend_setSelected()
{
	if (m_selected)
		return;

	m_selected = true;
	refreshAmbientSound();
	startAmbientSound(false);

	SelectionModule **module = m_selectionModules;
	if (!module)
		return;

	do
	{
		if (!*module)
			return;
		SelectionInterface *interface = (*module)->getSelectionInterface();
		if (interface)
			interface->selected();
		++module;
	} while (module);
}

void Drawable::friend_clearSelected()
{
	if (!m_selected)
		return;

	m_selected = false;
	if (m_selectedAmbientSound)
		TheAudio->removeAudioEvent(m_selectedAmbientSound->m_playingHandle);
	if (m_ambientSound)
		TheAudio->removeAudioEvent(m_ambientSound->m_playingHandle);
	if (m_damagedAmbientSound)
		TheAudio->removeAudioEvent(m_damagedAmbientSound->m_playingHandle);

	SelectionModule **module = m_selectionModules;
	if (!module)
		return;

	do
	{
		if (!*module)
			return;
		SelectionInterface *interface = (*module)->getSelectionInterface();
		if (interface)
			interface->unselected();
		++module;
	} while (module);
}

void Drawable::applyPendingModelConditionFlags(bool immediate)
{
	if (!m_isModelDirty && !immediate)
		return;

	m_conditionState.clearAndSet(m_pendingConditionClear, m_pendingConditionSet);
	for (DrawModule **module = m_drawModules; *module; ++module)
	{
		ObjectDrawInterface *interface = (*module)->getObjectDrawInterface();
		if (interface)
			interface->replaceModelConditionState(m_conditionState, immediate, 0);
	}
	m_isModelDirty = false;
}

int Drawable::getBarrelCount(WeaponSlotType slot) const
{
	if (m_isModelDirty)
	{
		m_conditionState.clearAndSet(m_pendingConditionClear, m_pendingConditionSet);
		for (DrawModule **module = m_drawModules; *module; ++module)
		{
			ObjectDrawInterface *interface = (*module)->getObjectDrawInterface();
			if (interface)
				interface->replaceModelConditionState(m_conditionState, false, 0);
		}
		m_isModelDirty = false;
	}

	for (DrawModule **module = m_drawModules; *module; ++module)
	{
		ObjectDrawInterface *interface = (*module)->getObjectDrawInterface();
		if (interface)
		{
			int count = interface->getBarrelCount(slot);
			if (count)
				return count;
		}
	}
	return 0;
}

bool Drawable::getProjectileLaunchOffset(WeaponSlotType slot, int barrel, Matrix3D *launch,
	WhichTurretType turret, Coord3D *turretRotation, Coord3D *turretPitch) const
{
	if (m_isModelDirty)
	{
		m_conditionState.clearAndSet(m_pendingConditionClear, m_pendingConditionSet);
		for (DrawModule **module = m_drawModules; *module; ++module)
		{
			ObjectDrawInterface *interface = (*module)->getObjectDrawInterface();
			if (interface)
				interface->replaceModelConditionState(m_conditionState, false, 0);
		}
		m_isModelDirty = false;
	}

	for (DrawModule **module = m_drawModules; *module; ++module)
	{
		ObjectDrawInterface *interface = (*module)->getObjectDrawInterface();
		if (interface && interface->getProjectileLaunchOffset(m_conditionState, slot,
			barrel, launch, turret, turretRotation, turretPitch))
			return true;
	}
	return false;
}

class BfmeNodeRB
{
public:
	__declspec(noinline) void bfmeTellRB(void *what);
	unsigned char m_bfmeHead[0xfc];
	BfmeRecordOwnerRB *m_bfmeRecordOwner;
	unsigned int m_bfmeSpare;
	BfmeNodeRB *m_bfmeNext;
};

void BfmeNodeRB::bfmeTellRB(void *what)
{
	BfmeRecordOwnerRB *owner = m_bfmeRecordOwner;
	ModelConditionFlags record = owner->m_bfmeRecord;

	if ((unsigned int)what == 4)
		record.m_bits[0] |= 0x80;
	else
		record.m_bits[0] &= ~0x80;

	((Drawable *)this)->replaceModelConditionState(record, false, 0);
}

class BfmeHolderRB
{
public:
	virtual void bfmeSpareRB0();
	virtual void bfmeSpareRB1();
	virtual void bfmeSpareRB2();
	virtual void bfmeSpareRB3();
	virtual void bfmeSpareRB4();
	virtual void bfmeSpareRB5();
	virtual void bfmeSpareRB6();
	virtual void bfmeSpareRB7();
	virtual void bfmeSpareRB8();
	virtual void bfmeSpareRB9();
	virtual void bfmeSpareRBA();
	virtual void bfmeSpareRBB();
	virtual BfmeNodeRB *bfmeHeadRB();
	void bfmeTellAllRB(void *what);
};

void BfmeHolderRB::bfmeTellAllRB(void *what)
{
	for (BfmeNodeRB *at = bfmeHeadRB(); at != 0; at = at->m_bfmeNext)
		at->bfmeTellRB(what);
}

// ?bfmeNotifyCondition4Modules@Drawable@@QAEXPAVObject@@@Z
// Retail 0x0041A290, 54 bytes. Only bit 4 of the object's first model
// condition word gates the notification; every draw module then hears it
// through the last slot of its vtable.
void Drawable::bfmeNotifyCondition4Modules(Object *object)
{
	if (object == 0 || !(object->m_modelConditionWord0 & 0x10))
		return;

	for (DrawModule **module = m_drawModules; *module; ++module)
		(*module)->bfmeCondition4Callback();
}

// ?bfmeRegionDispatch@Drawable@@QAEXHH@Z
// Retail 0x0041AA00, 114 bytes. Three renderers for the region at this+0x3C4,
// chosen by a status bit on the object and then by whether it is a structure.
void Drawable::bfmeRegionDispatch( int first, int second )
{
	Thing *object = (Thing *)m_object;
	if( object == 0 )
		return;

	if( (*(unsigned char *)((unsigned char *)object + 0x90) & 4) != 0 )
	{
		bfmeRegionRenderA( (unsigned char *)this + 0x3C4, first, second );
		return;
	}

	if( object->isKindOf( KINDOF_STRUCTURE ) )
	{
		bfmeRegionRenderB( (unsigned char *)this + 0x3C4, first, second );
		return;
	}

	bfmeRegionRenderC( (unsigned char *)this + 0x3C4, first, second );
}

// ?bfmeVisibilityGate@Drawable@@QAEHXZ
// Retail 0x0041B8B0, 128 bytes. Five conditions in a row, each falling to the
// same zero: the object exists, its final template carries the kind-of bit,
// it has a target gate that is not letting attacks through, the local player
// is at war with its team, and the gate's own object is still alive.
int Drawable::bfmeVisibilityGate()
{
	Object *object = m_object;
	Object *gateObject;
	BfmeTargetGateModule *module;
	Team *team;
	if (object == 0)
		goto failure;

	ThingTemplate *thingTemplate = object->getFinalTemplate();
	if ((thingTemplate->m_kindOf[ 4 ] & 0x00200000) == 0)
		goto failure;

	module = bfmeFindTargetGate( object );
	if (module == 0 || module->m_gate.bfmeAllowsAttack())
		goto failure;

	team = object->m_team;
	if (ThePlayerList->m_localPlayer->getRelationship( team ) != ENEMIES)
		goto failure;

	gateObject = TheGameLogic->findObjectByID( module->m_objectID );
	if (gateObject == 0)
		goto failure;

	return gateObject->bfmeVisibilityResult();

failure:
	return 0;
}
