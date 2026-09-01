// Two float accessors over the game's recursive Overridable chain.
//
// The held object is already the final value in the common case.  When it has
// an override, retail enters the existing out-of-line recursive chain walker
// through ILT 0x000022BB and reads the requested float from the final object.

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
	char m_middle[0x28];
	float m_firstFloat;
	float m_secondFloat;
};

class Rva001B59FloatView
{
public:
	float getFirstFloat(void) const;
	float getSecondFloat(void) const;

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
