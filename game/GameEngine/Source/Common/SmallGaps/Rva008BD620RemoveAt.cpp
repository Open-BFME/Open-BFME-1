// ?removeAt@Rva008BD620List@@QAEXH@Z
struct Rva008BD620List {
	int m_items[0x20];
	int m_count;
	void removeAt(int index);
};
void Rva008BD620List::removeAt(int index)
{
	for (; index < m_count - 1; ++index)
		m_items[index] = m_items[index + 1];
	m_count--;
}
