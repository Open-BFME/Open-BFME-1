// cl: /DNDEBUG /MD /EHsc

class BfmeFloatVectorView
{
public:
	float *m_begin;
	float *m_end;

	__forceinline int size() const { return m_end - m_begin; }
	__forceinline const float &operator[](int index) const
	{
		return m_begin[index];
	}
};

class BfmeThingEFE
{
public:
	float bfmeAt(int value) const;

private:
	__forceinline int indexFor(int value) const
	{
		int index = value - m_baseValue;
		if (index <= 0)
			return 0;

		if (index >= m_values->size())
			return m_values->size() - 1;

		return index;
	}

	void *m_vtable;
	void *m_owner;
	float m_scalar;
	int m_baseValue;
	BfmeFloatVectorView *m_values;
};

float BfmeThingEFE::bfmeAt(int value) const
{
	if (m_values->size() == 0)
		return 1.0f;

	return (*m_values)[indexFor(value)];
}
