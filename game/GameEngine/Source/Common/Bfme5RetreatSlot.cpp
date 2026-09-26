// Retreat the count before returning the preceding record.
class Gen_008C5E30
{
public:
	int *bfmeRetreatSlot(void);

private:
	int m_count;
	int m_reserved;
	int m_stride;
	int *m_items;
};

int *Gen_008C5E30::bfmeRetreatSlot(void)
{
	if (m_count == 0)
		return m_items;
	return m_items + (--m_count - 1) * m_stride;
}
