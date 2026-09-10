// ?bfmeCheckALT@BfmeHolderLT@@QAEDMMH@Z
// partial score=0.95 date=2026-09-09
#include <math.h>

typedef float Real;

extern Real normalizeAngle(Real angle);
extern const Real BfmeZeroRange;

class Object
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void update(void *, Real, int) = 0;
	void notifyModelConditionChanged(void);

	unsigned char m_bfmeHead[0x110];
	unsigned int m_modelConditionFlags;
};

class BfmeHolderLT
{
public:
	char bfmeCheckALT(Real value, Real ratio, int unused);

	unsigned char m_bfmeHead[8];
	Real *m_bfmeScale;
	void *m_bfmeCallbackArgument;
	Object *m_bfmeObject;
	unsigned char m_bfmeGap[4];
	Real m_bfmeCurrent;
	int m_bfmeUpdateArgument;
	unsigned char m_bfmeGap2[0x84];
	unsigned char m_bfmeChanged;
};

char BfmeHolderLT::bfmeCheckALT(Real value, Real ratio, int)
{
	Real current;
	value = normalizeAngle(value);
	ratio *= *m_bfmeScale;
	current = m_bfmeCurrent;
	Real difference = normalizeAngle(value - current);

	if (fabs(difference) < ratio)
	{
		ratio = value;
		if ((m_bfmeObject->m_modelConditionFlags & 0x02000000) != 0)
		{
			m_bfmeObject->m_modelConditionFlags &= 0xfdffffff;
			m_bfmeObject->notifyModelConditionChanged();
		}
	}
	else
	{
		if (difference > BfmeZeroRange)
			ratio = ratio + m_bfmeCurrent;
		else
			ratio = m_bfmeCurrent - ratio;

		if ((m_bfmeObject->m_modelConditionFlags & 0x02000000) == 0)
		{
			m_bfmeObject->m_modelConditionFlags |= 0x02000000;
			m_bfmeObject->notifyModelConditionChanged();
		}
	}
	m_bfmeChanged = 1;
	m_bfmeCurrent = normalizeAngle(ratio);
	if (m_bfmeCurrent != current)
		m_bfmeObject->update(m_bfmeCallbackArgument, current, m_bfmeUpdateArgument);

	if (fabs(m_bfmeCurrent - value) < ratio)
		return 1;

	return 0;
}
