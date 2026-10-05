// cl: /O2 /Ob0 /DNDEBUG /MD

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

extern _Locale_impl *_Bfme_classic_locale;

void rva00832100Release(void)
{
	if (::g_bfmeCountWE)
	{
		_Bfme_classic_locale->_bfme_decr();
		--::g_bfmeCountWE;
	}
}

}
