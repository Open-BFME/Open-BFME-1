// BFME-specific Drawable reconstructions whose upstream bodies differ from Zero Hour.
// readable body of ?clearAndSetModelConditionFlags@Drawable@@QAEXABV?$BitFlags@$0HF@@@0@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?enableAmbientSoundFromScript@Drawable@@QAEX_N@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?friend_clearSelected@Drawable@@QAEXXZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?friend_setSelected@Drawable@@QAEXXZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?getBarrelCount@Drawable@@QBEHW4WeaponSlotType@@@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?getProjectileLaunchOffset@Drawable@@QBE_NW4WeaponSlotType@@HPAVMatrix3D@@W4WhichTurretType@@PAUCoord3D@@3@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
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

private:
	void applyPendingModelConditionFlags(bool immediate);
	void startAmbientSound(bool onlyIfPermanent);
	void refreshAmbientSound();
	unsigned char m_bfmeHead[0x140];
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
	virtual ObjectDrawInterface *getObjectDrawInterface();
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
