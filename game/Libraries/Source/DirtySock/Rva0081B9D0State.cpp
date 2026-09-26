// cl: /Od
// DirtySock transport state query at retail RVA 0x0081B9D0.
// The transport state at +0xcc is read afresh for each comparison.

struct Rva0081B9D0StateView
{
	unsigned char m_bfmeHead[0xcc];		// 0x000
	int m_state;				// 0x0cc
};

extern "C" int Rva0081B9D0(void *comm)
{
	if (((Rva0081B9D0StateView *)comm)->m_state == 2 || ((Rva0081B9D0StateView *)comm)->m_state == 3)
		return 2;

	if (((Rva0081B9D0StateView *)comm)->m_state == 1 || ((Rva0081B9D0StateView *)comm)->m_state == 7)
		return 1;

	if (((Rva0081B9D0StateView *)comm)->m_state == 4 || ((Rva0081B9D0StateView *)comm)->m_state == 5)
		return 3;

	return 4;
}
