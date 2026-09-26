// cl: /O2 /Ob0

class Rva008FC250CellDispatch
{
	unsigned char m_prefix[0x24];
	unsigned m_width;
	unsigned char m_gap1[4];
	int m_origin;
	unsigned char m_gap2[0x64 - 0x30];
	unsigned m_type;
	unsigned char m_gap3[4];
	void (__cdecl *m_callback)(unsigned column, unsigned row, unsigned player);
public:
	void dispatch(unsigned type, unsigned player, int coordinate);
};
void Rva008FC250CellDispatch::dispatch(unsigned type, unsigned player, int coordinate)
{
	if (type == m_type) {
		unsigned position = (coordinate - m_origin) / 104;
		m_callback(position % m_width, position / m_width, player);
	}
}
