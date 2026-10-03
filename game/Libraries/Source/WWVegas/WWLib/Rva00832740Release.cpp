// cl: /O2 /Ob0 /DNDEBUG /MD

extern void *g_bfmeObjWE;
extern int g_bfmeCountWE;

namespace _STL
{

class _Locale_impl
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_incr(void) = 0;
	virtual void _bfme_decr(void) = 0;
};

void rva00832740Release(void)
{
	if (::g_bfmeCountWE > 0)
	{
		static_cast<_Locale_impl *>(::g_bfmeObjWE)->_bfme_decr();
		--::g_bfmeCountWE;
	}
}

}
