// A reverse-indexed lookup over a small pointer array.
class Gen_008C5E60
{
public:
	void *bfmeAtFromEnd(int index) const;

private:
	int m_count;
	int m_unused;
	void **m_items;
};

void *Gen_008C5E60::bfmeAtFromEnd(int index) const
{
	return m_items[m_count - index - 1];
}
