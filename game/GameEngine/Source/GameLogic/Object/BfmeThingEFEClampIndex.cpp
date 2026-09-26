// cl: /DNDEBUG /MD /EHsc

typedef float Real;

class BfmeFloatVectorView
{
public:
	Real *m_begin;
	Real *m_end;

	__forceinline int size() const
	{
		return m_end - m_begin;
	}
};

class BfmeThingEFE
{
public:
	int bfmeClampIndex(int value);

private:
	void *m_vtable;
	void *m_tracker;
	Real m_scalar;
	int m_baseCount;
	BfmeFloatVectorView *m_values;
};

int BfmeThingEFE::bfmeClampIndex(int value)
{
	int index = value - m_baseCount;
	if (index <= 0)
		return 0;

	if (index >= m_values->size())
		return m_values->size() - 1;

	return index;
}
