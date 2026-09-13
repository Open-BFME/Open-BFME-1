// cl: /O2 /Ob0 /DNDEBUG /MD

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
extern int _Bfme_classic_locale_refs;

void rva00832740Release(void)
{
	if (_Bfme_classic_locale_refs > 0)
	{
		_Bfme_classic_locale->_bfme_decr();
		--_Bfme_classic_locale_refs;
	}
}

}
