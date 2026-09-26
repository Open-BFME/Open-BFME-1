// BFME 1.03 Object::updatePendingDamage at RVA 0x001C7B80.
// cl: /O2 /Ob1 /DNDEBUG /MD
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Snapshot
{
protected:
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class DamageInfoInput
{
public:
	unsigned char m_beforeDelay[0x20];
	float m_delay;
	unsigned char m_afterDelay[0x28];
};

class DamageInfoOutputTail
{
public:
	DamageInfoOutputTail &operator=(const DamageInfoOutputTail &other)
	{
		m_actualDamageClipped = other.m_actualDamageClipped;
		m_noEffect = other.m_noEffect;
		return *this;
	}

	float m_actualDamageClipped;
	bool m_noEffect;
	unsigned char m_padding[3];
};

class DamageInfoOutput
{
public:
	float m_actualDamageDealt;
	DamageInfoOutputTail m_tail;
};

class DamageInfo : public Snapshot
{
public:
	DamageInfoInput in;
	DamageInfoOutput out;
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual void updatePendingDamage(void);

private:
	unsigned char m_beforePendingDamage[0x348];
	_STL::vector<DamageInfo> m_pendingDamage;
};

void Object::updatePendingDamage(void)
{
	for (_STL::vector<DamageInfo>::iterator it = m_pendingDamage.begin();
		it != m_pendingDamage.end(); )
	{
		it->in.m_delay -= 1.0f;
		if (it->in.m_delay < 0.0f)
		{
			attemptDamage(&*it);
			it = m_pendingDamage.erase(it);
		}
		else
		{
			++it;
		}
	}
}
