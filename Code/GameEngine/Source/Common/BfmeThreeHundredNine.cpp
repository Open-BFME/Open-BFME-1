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

class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &state, bool dirty, unsigned int effect);
	void bfmeClearAndSetModelConditionFlags(const ModelConditionFlags &clear, const ModelConditionFlags &set);
	int bfmeGetBarrelCount(int slot) const;
	void bfmeEnableAmbientSoundFromScript(bool enable);

private:
	void bfmeApplyModelConditionFlags(bool immediate);
	void bfmeStartAmbientSound(bool onlyIfPermanent);
	void refreshAmbientSound();
	unsigned char m_bfmeHead[0x140];
	bool m_bfmeAmbientSoundEnabled;
	bool m_bfmeAmbientSoundEnabledFromScript;
	unsigned char m_bfmeGap142[2];
	class DynamicAudioEventRTS *m_bfmeAmbientSoundA;
	class DynamicAudioEventRTS *m_bfmeAmbientSoundB;
	class DynamicAudioEventRTS *m_bfmeAmbientSoundC;
	class DrawModule **m_bfmeDrawModules;
	unsigned char m_bfmeGap154[0xfc];
	mutable ModelConditionFlags m_bfmeConditionState;
	mutable ModelConditionFlags m_bfmeClearMask;
	mutable ModelConditionFlags m_bfmeSetMask;
	unsigned char m_bfmeGap2c8[0xeb];
	mutable bool m_bfmeIsModelDirty;
};

void Drawable::bfmeClearAndSetModelConditionFlags(const ModelConditionFlags &clear, const ModelConditionFlags &set)
{
	m_bfmeClearMask = clear;
	m_bfmeSetMask = set;
	bfmeApplyModelConditionFlags(true);
}

class ObjectDrawInterface
{
public:
	virtual void anchor00(); virtual void anchor04(); virtual void anchor08(); virtual void anchor0c();
	virtual void anchor10(); virtual void anchor14(); virtual void anchor18(); virtual void anchor1c();
	virtual void anchor20(); virtual void anchor24(); virtual void anchor28(); virtual void anchor2c();
	virtual void anchor30(); virtual void anchor34(); virtual void anchor38(); virtual void anchor3c();
	virtual void anchor40(); virtual void anchor44(); virtual void anchor48();
	virtual void replaceModelConditionState(const ModelConditionFlags &state, bool immediate, unsigned int effect);
	virtual void anchor50(); virtual void anchor54();
	virtual int getBarrelCount(int slot);
};

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

class DynamicAudioEventRTS
{
public:
	unsigned char m_bfmeHead[0x10];
	unsigned int m_bfmePlayingHandle;
};

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

void Drawable::bfmeEnableAmbientSoundFromScript(bool enable)
{
	m_bfmeAmbientSoundEnabledFromScript = enable;
	if (enable)
	{
		bfmeStartAmbientSound(false);
		refreshAmbientSound();
		return;
	}

	if (m_bfmeAmbientSoundA)
		TheAudio->removeAudioEvent(m_bfmeAmbientSoundA->m_bfmePlayingHandle);
	if (m_bfmeAmbientSoundB)
		TheAudio->removeAudioEvent(m_bfmeAmbientSoundB->m_bfmePlayingHandle);
	if (m_bfmeAmbientSoundC)
		TheAudio->removeAudioEvent(m_bfmeAmbientSoundC->m_bfmePlayingHandle);
}

void Drawable::bfmeApplyModelConditionFlags(bool immediate)
{
	if (!m_bfmeIsModelDirty && !immediate)
		return;

	m_bfmeConditionState.clearAndSet(m_bfmeClearMask, m_bfmeSetMask);
	for (DrawModule **module = m_bfmeDrawModules; *module; ++module)
	{
		ObjectDrawInterface *interface = (*module)->getObjectDrawInterface();
		if (interface)
			interface->replaceModelConditionState(m_bfmeConditionState, immediate, 0);
	}
	m_bfmeIsModelDirty = false;
}

int Drawable::bfmeGetBarrelCount(int slot) const
{
	if (m_bfmeIsModelDirty)
	{
		m_bfmeConditionState.clearAndSet(m_bfmeClearMask, m_bfmeSetMask);
		for (DrawModule **module = m_bfmeDrawModules; *module; ++module)
		{
			ObjectDrawInterface *interface = (*module)->getObjectDrawInterface();
			if (interface)
				interface->replaceModelConditionState(m_bfmeConditionState, false, 0);
		}
		m_bfmeIsModelDirty = false;
	}

	for (DrawModule **module = m_bfmeDrawModules; *module; ++module)
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
