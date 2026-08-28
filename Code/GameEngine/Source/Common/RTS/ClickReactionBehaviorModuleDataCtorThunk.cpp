// cl: /DNDEBUG /MD /EHsc

// The interleaved stores at 8/0x14, 0xc/0x18 and 0x10/0x1c are one unrolled
// loop over two parallel three-element float arrays, not six separate members:
// retail alternates between them, which is what a single loop body produces.
// 0x7f7fffff is FLT_MAX.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void moduleDataAnchor();		///< vptr at 0x00

	int m_04;
};

class ClickReactionBehaviorModuleData : public ModuleData
{
public:
	ClickReactionBehaviorModuleData();

	virtual void moduleDataAnchor();

	float m_min[3];							///< 0x08
	float m_max[3];							///< 0x14
	bool m_flag20;							///< 0x20
	bool m_flag21;							///< 0x21
};

// ??0ClickReactionBehaviorModuleData@@QAE@XZ
ClickReactionBehaviorModuleData::ClickReactionBehaviorModuleData()
{
	m_flag20 = false;
	m_flag21 = false;

	for (int i = 0; i < 3; i++)
	{
		m_min[i] = 0.0f;
		m_max[i] = 3.402823466e+38F;
	}
}
