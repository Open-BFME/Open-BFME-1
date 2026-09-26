// cl: /DNDEBUG /MD /EHsc /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WWMath /I game/Libraries/Source/WWVegas/WWDebug /I game/Libraries/Source/WWVegas/WWSaveLoad /I game/Libraries/Source/WWVegas/WW3D2 /I game/Libraries/Include

#include "rendobj.h"

class BfmeAnimationHolder
{
public:
	void rva0061D5A0(float value);

private:
	unsigned char m_beforeReceivers[8];
	RenderObjClass *m_primary;
	RenderObjClass *m_secondary;
};

// ?rva0061D5A0@BfmeAnimationHolder@@QAEXM@Z
void BfmeAnimationHolder::rva0061D5A0(float value)
{
	RenderObjClass *primary = m_primary;
	if (primary == 0)
		return;

	Matrix3D transform(primary->Get_Transform());
	transform.Set_Translation(Vector3(value, value, value));
	m_primary->Set_Transform(transform);
	if (m_secondary != 0)
		m_secondary->Set_Transform(transform);
}
