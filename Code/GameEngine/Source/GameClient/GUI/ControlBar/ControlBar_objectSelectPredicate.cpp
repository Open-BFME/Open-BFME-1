// cl: /DNDEBUG /MD /EHsc

// retail 0x004A6570, 71 bytes. Object* predicate: non-null, bfmeTailJB,
// isMassSelectable, then a third thiscall; on success fires InGameUI vslot
// +0x160 and returns true.

class BfmeTargetJB
{
public:
	bool bfmeTailJB(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeTargetJB
{
public:
	bool isMassSelectable(void) const;
	bool bfmeCheckC80F0(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual void slot000(void);
	virtual void slot004(void);
	virtual void slot008(void);
	virtual void slot00c(void);
	virtual void slot010(void);
	virtual void slot014(void);
	virtual void slot018(void);
	virtual void slot01c(void);
	virtual void slot020(void);
	virtual void slot024(void);
	virtual void slot028(void);
	virtual void slot02c(void);
	virtual void slot030(void);
	virtual void slot034(void);
	virtual void slot038(void);
	virtual void slot03c(void);
	virtual void slot040(void);
	virtual void slot044(void);
	virtual void slot048(void);
	virtual void slot04c(void);
	virtual void slot050(void);
	virtual void slot054(void);
	virtual void slot058(void);
	virtual void slot05c(void);
	virtual void slot060(void);
	virtual void slot064(void);
	virtual void slot068(void);
	virtual void slot06c(void);
	virtual void slot070(void);
	virtual void slot074(void);
	virtual void slot078(void);
	virtual void slot07c(void);
	virtual void slot080(void);
	virtual void slot084(void);
	virtual void slot088(void);
	virtual void slot08c(void);
	virtual void slot090(void);
	virtual void slot094(void);
	virtual void slot098(void);
	virtual void slot09c(void);
	virtual void slot0a0(void);
	virtual void slot0a4(void);
	virtual void slot0a8(void);
	virtual void slot0ac(void);
	virtual void slot0b0(void);
	virtual void slot0b4(void);
	virtual void slot0b8(void);
	virtual void slot0bc(void);
	virtual void slot0c0(void);
	virtual void slot0c4(void);
	virtual void slot0c8(void);
	virtual void slot0cc(void);
	virtual void slot0d0(void);
	virtual void slot0d4(void);
	virtual void slot0d8(void);
	virtual void slot0dc(void);
	virtual void slot0e0(void);
	virtual void slot0e4(void);
	virtual void slot0e8(void);
	virtual void slot0ec(void);
	virtual void slot0f0(void);
	virtual void slot0f4(void);
	virtual void slot0f8(void);
	virtual void slot0fc(void);
	virtual void slot100(void);
	virtual void slot104(void);
	virtual void slot108(void);
	virtual void slot10c(void);
	virtual void slot110(void);
	virtual void slot114(void);
	virtual void slot118(void);
	virtual void slot11c(void);
	virtual void slot120(void);
	virtual void slot124(void);
	virtual void slot128(void);
	virtual void slot12c(void);
	virtual void slot130(void);
	virtual void slot134(void);
	virtual void slot138(void);
	virtual void slot13c(void);
	virtual void slot140(void);
	virtual void slot144(void);
	virtual void slot148(void);
	virtual void slot14c(void);
	virtual void slot150(void);
	virtual void slot154(void);
	virtual void slot158(void);
	virtual void slot15c(void);
	virtual void slot160(void);
};

extern InGameUI *TheInGameUI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	int objectSelectPredicate(Object *obj);
};

int ControlBar::objectSelectPredicate(Object *obj)
{
	if (obj)
	{
		if (obj->bfmeTailJB())
		{
			if (obj->isMassSelectable())
			{
				if (!obj->bfmeCheckC80F0())
				{
					TheInGameUI->slot160();
					return 1;
				}
			}
		}
	}
	return 0;
}
