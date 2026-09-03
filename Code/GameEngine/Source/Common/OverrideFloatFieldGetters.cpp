// Two float accessors over the game's recursive Overridable chain.
//
// The held object is already the final value in the common case.  When it has
// an override, retail enters the existing out-of-line recursive chain walker
// through ILT 0x000022BB and reads the requested float from the final object.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const
	{
		if (this == 0)
			return this;
		if (m_override != 0)
			return m_override->getFinalOverride();
		return this;
	}

	char m_head[4];
	const Overridable *m_override;
	char m_middle0[0x1C];
	float m_firstScale;
	char m_middle1[8];
	float m_firstFloat;
	float m_secondFloat;
	char m_middle2[0x18];
	float m_secondScale;
};

extern volatile float g_rva001B59ScaleConstant;

struct Rva001B59ScaleInfo
{
	char m_head[0x1D4];
	float m_scale;
};

struct Rva001B59ScaleContext
{
	char m_head[0x204];
	const Rva001B59ScaleInfo *m_info;
};

class Rva001B59FloatView
{
public:
	float getFirstFloat(void) const;
	float getSecondFloat(void) const;
	float getScaledFirst(const Rva001B59ScaleContext *context) const;
	float getScaledSecond(const Rva001B59ScaleContext *context) const;

private:
	char m_head[4];
	const Overridable *m_value;
};

float Rva001B59FloatView::getFirstFloat(void) const
{
	return m_value->getFinalOverride()->m_firstFloat;
}

float Rva001B59FloatView::getSecondFloat(void) const
{
	return m_value->getFinalOverride()->m_secondFloat;
}

float Rva001B59FloatView::getScaledFirst(const Rva001B59ScaleContext *context) const
{
	float scale = context->m_info->m_scale;
	const Overridable *value = m_value->getFinalOverride();
	return g_rva001B59ScaleConstant * value->m_firstScale * scale;
}

float Rva001B59FloatView::getScaledSecond(const Rva001B59ScaleContext *context) const
{
	float scale = context->m_info->m_scale;
	const Overridable *value = m_value->getFinalOverride();
	return g_rva001B59ScaleConstant * value->m_secondScale * scale;
}
