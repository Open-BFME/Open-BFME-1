// cl: /DNDEBUG /MD /EHsc /I Code/Libraries/Source/WWVegas/WWLib /I Code/Libraries/Source/WWVegas/WWMath /I Code/Libraries/Source/WWVegas/WWDebug /I Code/Libraries/Source/WWVegas/WWSaveLoad /I Code/Libraries/Source/WWVegas/WW3D2 /I Code/Libraries/Include

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
