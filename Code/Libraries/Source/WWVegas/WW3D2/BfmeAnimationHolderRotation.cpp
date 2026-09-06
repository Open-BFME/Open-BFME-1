// cl: /DNDEBUG /MD /EHsc /I Code/Libraries/Source/WWVegas/WWLib /I Code/Libraries/Source/WWVegas/WWMath /I Code/Libraries/Source/WWVegas/WWDebug /I Code/Libraries/Source/WWVegas/WWSaveLoad /I Code/Libraries/Include

#include "matrix3.h"
#include "matrix3d.h"

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
	virtual void updatePayload(void);
	virtual void applyPayload(const Matrix3D *payload);

	unsigned char m_beforePayload[0x14];
	Matrix3D m_payload;
};

class BfmeAnimationHolder
{
public:
	void applyRotationPayload(float angle);

private:
	unsigned char m_beforeReceivers[8];
	BfmeAnimationReceiver *m_primary;
	BfmeAnimationReceiver *m_secondary;
};

// ?applyRotationPayload@BfmeAnimationHolder@@QAEXM@Z
void BfmeAnimationHolder::applyRotationPayload(float angle)
{
	BfmeAnimationReceiver *primary = m_primary;
	if (primary == 0)
		return;

	Matrix3 rotation(true);
	rotation.Rotate_Z(angle);
	primary->updatePayload();
	Matrix3D payload(primary->m_payload);
	payload.Set_Rotation(rotation);
	m_primary->applyPayload(&payload);
	if (m_secondary != 0)
		m_secondary->applyPayload(&payload);
}
