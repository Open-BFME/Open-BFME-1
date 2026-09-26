// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeS1238
{
public:
	BfmeS1238 *bfmeAt1238B(int index);

private:
	void *m_vtable;
	unsigned *m_entries;
	unsigned m_zero;
	unsigned m_one;
};

BfmeS1238 *BfmeS1238::bfmeAt1238B(int index)
{
	unsigned tagged;
	if (index == 0)
		tagged = m_zero;
	else if (index == 1)
		tagged = m_one;
	else {
		if (!m_entries)
			return 0;
		tagged = m_entries[index * 2 - 3];
	}

	BfmeS1238 *value = (BfmeS1238 *)(tagged & ~1u);
	if (value && !(tagged & 1))
		value = 0;
	return value;
}
