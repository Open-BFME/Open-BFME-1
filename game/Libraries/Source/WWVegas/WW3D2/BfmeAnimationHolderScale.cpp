// cl: /DNDEBUG /MD /EHsc /I game/Libraries/Source/WWVegas/WWLib /I game/Libraries/Source/WWVegas/WWMath /I game/Libraries/Source/WWVegas/WWDebug /I game/Libraries/Source/WWVegas/WWSaveLoad /I game/Libraries/Source/WWVegas/WW3D2 /I game/Libraries/Include

#include "rendobj.h"

class BfmeAnimationHolder
{
public:
	void applyScalePayload(float scale);

private:
	unsigned char m_beforeReceivers[8];
	RenderObjClass *m_primary;
	RenderObjClass *m_secondary;
	unsigned char m_beforeScale[0x60];
	float m_scale;
};

// ?applyScalePayload@BfmeAnimationHolder@@QAEXM@Z
void BfmeAnimationHolder::applyScalePayload(float scale)
{
	RenderObjClass *primary = m_primary;
	if (primary == 0)
		return;

	m_scale = scale;
	Matrix3D transform(primary->Get_Transform());
	const float factor = scale / m_primary->Get_ObjectScale();
	transform.Scale(factor);

	m_primary->Set_ObjectScale(scale);
	m_primary->Set_Transform(transform);
	if (m_secondary != 0)
	{
		m_secondary->Set_ObjectScale(scale);
		m_secondary->Set_Transform(transform);
	}
}
