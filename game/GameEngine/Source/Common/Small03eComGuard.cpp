// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00958730 validates its argument through _com_issue_error and
// reports whether the held pointer is null: a null argument returns the
// null-test directly, otherwise the 0x80004003 failure is raised first and
// the same null-test follows. The callee is the real comutil.h declaration
// (void __stdcall _com_issue_error(HRESULT) at the 0x00AFD540 pin), so the
// reference carries its defining name and links.
// IDENTITY IS NOT RECOVERED: the owner keeps its address token.
// comutil.h declares `void __stdcall _com_issue_error(HRESULT)`; the sweep
// comutil.h shim does not, so the declaration is repeated here under its
// exact defining spelling (?_com_issue_error@@YGXJ@Z).
extern void __stdcall _com_issue_error(long);

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
	_com_issue_error((long)0x80004003);
	return m_ptr == 0;
}
