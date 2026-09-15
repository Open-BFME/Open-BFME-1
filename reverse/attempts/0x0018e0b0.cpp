// ?friend_turnTowardsAngle@TurretAI@@QAE_NMMM@Z
// partial score=0.956 date=2026-09-15
// Full274B 0018E0B0..0018E1C2: named TurretAI recenter/idle-scan callers
// prove friend_turnTowardsAngle(float,float,float) via ILT0004198E.
// Corrected old bank: third float tolerance; <= final comparison; sound
// flag only on turning branch; saved angle and float callback pitch.
// Address-labelled scratch layout pending canonical TurretAI header adoption.
// cl: /DNDEBUG /MD /EHsc
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
	virtual void update(int, Real, Real) = 0;
	void notifyModelConditionChanged(void);
	void clearRotate() {
		if (m_modelConditionFlags & 0x02000000) {
			m_modelConditionFlags &= 0xfdffffff;
			notifyModelConditionChanged();
		}
	}
	void setRotate(unsigned int mask) {
		unsigned int before = m_modelConditionFlags;
		unsigned int after = before | mask;
		if (before != after) {
			m_modelConditionFlags = after;
			notifyModelConditionChanged();
		}
	}

	unsigned char m_bfmeHead[0x110];
	unsigned int m_modelConditionFlags;
};

class Rva0018E0B0Owner
{
public:
	bool bfmeCheckALT(Real value, Real ratio, Real tolerance);

	unsigned char m_bfmeHead[8];
	Real *m_bfmeScale;
	int m_bfmeCallbackArgument;
	Object *m_bfmeObject;
	unsigned char m_bfmeGap[4];
	Real m_bfmeCurrent;
	Real m_bfmeUpdateArgument;
	unsigned char m_bfmeGap2[0x84];
	unsigned char m_bfmeChanged;
};

bool Rva0018E0B0Owner::bfmeCheckALT(Real value, Real ratio, Real tolerance)
{
	Real current;
	value = normalizeAngle(value);
	current = m_bfmeCurrent;
	Real actual = current;
	Real turnRate = *m_bfmeScale * ratio;
	Real difference = normalizeAngle(value - current);

	if (fabs(difference) < turnRate)
	{
		actual = value;
		m_bfmeObject->clearRotate();
	}
	else
	{
		if (difference > 0)
			actual += turnRate;
		else
			actual -= turnRate;

		m_bfmeObject->setRotate(0x02000000);
		m_bfmeChanged = 1;
	}
	m_bfmeCurrent = normalizeAngle(actual);
	if (m_bfmeCurrent != current)
		m_bfmeObject->update(m_bfmeCallbackArgument, current, m_bfmeUpdateArgument);

	if (fabs(m_bfmeCurrent - value) <= tolerance)
		return 1;

	return 0;
}
