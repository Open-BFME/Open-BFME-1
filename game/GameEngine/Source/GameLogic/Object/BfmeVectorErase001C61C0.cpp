// cl: /O2 /Ob1 /DNDEBUG /MD
// stlport
// BFME retail 0x001C61C0: STLport vector erase for a 0x5c-byte POD.

#include <vector>

class DamageInfoInput
{
	char m_unreconstructed[0x4c];
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
	char m_padding[3];
};

class DamageInfoOutput
{
public:
	float m_actualDamageDealt;
	DamageInfoOutputTail m_tail;
};

class Snapshot
{
protected:
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class DamageInfo : public Snapshot
{
private:
	DamageInfoInput in;
	DamageInfoOutput out;
};

class BfmeVectorOwner001C61C0 : public _STL::vector<DamageInfo>
{
public:
	DamageInfo *remove(DamageInfo *position);
};

DamageInfo *BfmeVectorOwner001C61C0::remove(DamageInfo *position)
{
	return erase(position);
}
