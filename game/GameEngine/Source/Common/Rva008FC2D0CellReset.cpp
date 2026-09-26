// cl: /O2 /Ob0

struct Rva008FC2D0Cells
{
	unsigned char m_unused[0x24];
	unsigned m_slots[1];
};
struct Rva008FC2D0Node
{
	void *m_previous;
	Rva008FC2D0Cells *m_cells;
	void *m_owner;
	Rva008FC2D0Node *m_next;
};
class Rva008FC2D0CellReset
{
	Rva008FC2D0Node *m_first;
public:
	void clear(unsigned index);
};
void Rva008FC2D0CellReset::clear(unsigned index)
{
	for (Rva008FC2D0Node *node = m_first; node != 0; node = node->m_next)
		node->m_cells->m_slots[index] = 0;
}
