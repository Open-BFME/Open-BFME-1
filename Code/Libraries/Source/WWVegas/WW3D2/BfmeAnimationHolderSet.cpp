// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class HAnimClass
{
public:
	virtual void release(void);
	int m_refCount;
};

HAnimClass *Get_HAnim(const char *name);

class BfmeAnimationReceiver
{
public:
	virtual void slot00(void); virtual void slot01(void);
	virtual void slot02(void); virtual void slot03(void);
	virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void);
	virtual void slot08(void); virtual void slot09(void);
	virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void);
	virtual void slot14(void); virtual void slot15(void);
	virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void);
	virtual void slot20(void); virtual void slot21(void);
	virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void);
	virtual void slot26(void); virtual void slot27(void);
	virtual void slot28(void); virtual void slot29(void);
	virtual void slot30(void); virtual void slot31(void);
	virtual void slot32(void); virtual void slot33(void);
	virtual void slot34(void); virtual void slot35(void);
	virtual void slot36(void); virtual void slot37(void);
	virtual void slot38(void); virtual void slot39(void);
	virtual void slot40(void); virtual void slot41(void);
	virtual void slot42(void); virtual void slot43(void);
	virtual void setAnimation(HAnimClass *animation, int zero, int one);
};

class BfmeAnimationHolder
{
public:
	HAnimClass *setAnimationByName(AsciiString name);

private:
	unsigned char m_beforeReceiver[8];
	BfmeAnimationReceiver *m_receiver;
	unsigned char m_beforeAnimation[4];
	HAnimClass *m_animation;
};

HAnimClass *BfmeAnimationHolder::setAnimationByName(AsciiString name)
{
	HAnimClass *oldAnimation = m_animation;
	if (oldAnimation)
	{
		if (--oldAnimation->m_refCount == 0)
			oldAnimation->release();
		m_animation = 0;
	}

	void *data = *reinterpret_cast<void **>(&name);
	m_animation = Get_HAnim(data ? static_cast<const char *>(data) + 8 : "");

	if (m_receiver && m_animation)
		m_receiver->setAnimation(m_animation, 0, 1);

	return m_animation;
}
