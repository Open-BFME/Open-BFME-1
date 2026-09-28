// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00958730 validates its argument through _com_issue_error and
// reports whether the held pointer is null: a null argument returns the
// null-test directly, otherwise the 0x80004003 failure is raised first and
// the same null-test follows. The callee declaration matches the proven
// BfmeConv793.cpp spelling (void __stdcall at the 0x00AFD540 pin).
// IDENTITY IS NOT RECOVERED: the owner keeps its address token.
void __stdcall bfmeFailDXE(int code);

class Rva00958730Box
{
public:
	int check(void *arg);
	void *m_ptr;
};

int Rva00958730Box::check(void *arg)
{
	if (arg == 0)
		return m_ptr == 0;
	bfmeFailDXE((int)0x80004003);
	return m_ptr == 0;
}
