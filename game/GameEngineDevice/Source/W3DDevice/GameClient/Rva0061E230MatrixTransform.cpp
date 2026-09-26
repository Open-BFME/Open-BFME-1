// 0x0061E230: matrix transform body reached through ILT 0x00005B78.
// The owning class and virtual methods have no proved semantic names; the
// address-qualified facades keep the identity and field offsets explicit.
// The early exits and final path leave no defined return value, so this is
// modelled as a void no-argument thiscall. The body matches retail exactly.
// cl: /DNDEBUG /MD /EHsc /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WWMath /I game/Libraries/Source/WWVegas/WWDebug /I game/Libraries/Source/WWVegas/WWSaveLoad /I game/Libraries/Include

#include "matrix3.h"
#include "matrix3d.h"

extern const float BfmeZeroRange;
extern const float g_rva001B5860TwoPi;

class Rva0061E230Receiver
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
	virtual void slot20(void);
	virtual void slot21(const Matrix3D *payload);

	unsigned char m_beforeMatrix18[0x14];
	Matrix3D m_matrix18;
};

class Rva0061E230Owner
{
public:
	void Rva0061E230(void);

private:
	unsigned char m_beforeReceivers[8];
	Rva0061E230Receiver *m_primary;
	Rva0061E230Receiver *m_secondary;
	unsigned char m_beforeRotationState[0x6c];
	unsigned char m_rotationEnabled;
	unsigned char m_gap7d[3];
	float m_angle80;
	unsigned char m_gap84[4];
	float m_angle88;
};

// ?Rva0061E230@Rva0061E230Owner@@QAEXXZ
void Rva0061E230Owner::Rva0061E230(void)
{
	Rva0061E230Receiver *primary = m_primary;
	if (primary == 0)
		return;
	if (m_rotationEnabled == 0)
		return;

	float angle = m_angle88 + m_angle80;
	if (angle < BfmeZeroRange)
		angle += g_rva001B5860TwoPi;
	else if (angle > g_rva001B5860TwoPi)
		angle -= g_rva001B5860TwoPi;

	Matrix3 rotation(true);
	rotation.Rotate_Z(angle);
	primary->slot20();
	Matrix3D payload(primary->m_matrix18);
	payload.Set_Rotation(rotation);
	m_primary->slot21(&payload);
	if (m_secondary != 0)
		m_secondary->slot21(&payload);
}
