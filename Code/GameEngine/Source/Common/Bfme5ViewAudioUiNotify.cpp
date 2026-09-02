#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

class View
{
public:
	BFME_TEN_VIRTUALS(v00);
	BFME_TEN_VIRTUALS(v10);
	BFME_TEN_VIRTUALS(v20);
	BFME_TEN_VIRTUALS(v30);
	BFME_TEN_VIRTUALS(v40);
	BFME_TEN_VIRTUALS(v50);
	BFME_TEN_VIRTUALS(v60);
	BFME_TEN_VIRTUALS(v70);
	BFME_TEN_VIRTUALS(v80);
	BFME_TEN_VIRTUALS(v90);
	virtual void vTail100(void);
	virtual void vTail101(void);
	virtual void vTail102(void);
	virtual void bfmeNotify(void);
};

class AudioManager
{
public:
	BFME_TEN_VIRTUALS(v00);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void bfmeAdd(void *event);
	BFME_TEN_VIRTUALS(v20);
	BFME_TEN_VIRTUALS(v30);
	BFME_TEN_VIRTUALS(v40);
	BFME_TEN_VIRTUALS(v50);
	BFME_TEN_VIRTUALS(v60);
	virtual void v70(void);
	virtual void v71(void);
	virtual void v72(void);
	virtual void v73(void);
	virtual void v74(void);
	virtual void *bfmeCurrent(void);
};

class InGameUI
{
public:
	void bfmeNotify(void);
};

extern View *TheTacticalView;
extern AudioManager *TheAudio;
extern InGameUI *TheInGameUI;

class Gen_00589940
{
public:
	void bfmeNotify(void);

private:
	char m_bfme00[0x48];
	bool m_bfme48;
};

// ?bfmeNotify@Gen_00589940@@QAEXXZ
void Gen_00589940::bfmeNotify(void)
{
	m_bfme48 = false;
	TheTacticalView->bfmeNotify();

	if (TheAudio != 0 && TheAudio->bfmeCurrent() != 0)
	{
		TheAudio->bfmeAdd(
			reinterpret_cast<char *>(TheAudio->bfmeCurrent()) + 0xBD0);
	}

	TheInGameUI->bfmeNotify();
}

#undef BFME_TEN_VIRTUALS
