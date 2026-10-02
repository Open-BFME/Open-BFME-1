// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00958A80 validates its argument through _com_issue_error: a
// non-null argument raises 0x80004003 first, then the held pointer is tested
// and, when non-null, cleared and released through its vtable slot 2 before
// returning this. The braced-null spelling is what emits retail's
// `mov eax,[esp+4] / test eax,eax / push esi / mov esi,ecx / je +0xA /
// push 0x80004003 / call / mov eax,[esi] / test eax,eax / je +0xC /
// mov [esi],0 / mov ecx,[eax] / push eax / call [ecx+8] / mov eax,esi /
// pop esi / ret 4` form; the early-return spelling merges the null tails and
// drifts. The callee is the real comutil.h declaration
// `void __stdcall _com_issue_error(HRESULT)` at the 0x00AFD540 pin; the sweep
// comutil.h shim does not declare it, so it is repeated here under its exact
// defining spelling (?_com_issue_error@@YGXJ@Z).
// IDENTITY IS NOT RECOVERED: the owner keeps its address token.
extern void __stdcall _com_issue_error(long);

class Rva00958A80Box
{
public:
	void *release(void *arg);
	void *m_ptr;
};

void *Rva00958A80Box::release(void *arg)
{
	void *heldArg = arg;
	if (heldArg != 0)
		_com_issue_error((long)0x80004003);
	void *held = m_ptr;
	if (held != 0)
	{
		m_ptr = 0;
		void *vt = *(void **)held;
		((void (__stdcall *)(void *))*(void **)((char *)vt + 8))(held);
	}
	return this;
}
