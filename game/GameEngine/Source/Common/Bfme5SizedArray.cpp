// An array of variable-width dword records indexed by its live count.
class Gen_008C5E10
{
public:
	int *bfmeAppendSlot(void);

private:
	int m_count;
	int m_reserved;
	int m_stride;
	int *m_items;
};

int *Gen_008C5E10::bfmeAppendSlot(void)
{
	int *slot = m_items + m_count * m_stride;
	++m_count;
	return slot;
}
