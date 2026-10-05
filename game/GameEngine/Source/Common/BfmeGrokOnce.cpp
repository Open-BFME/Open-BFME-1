// cl: /O2

int g_bfmeCountWE;
namespace _STL
{
class _Locale_impl;
_Locale_impl *_Bfme_classic_locale;
}

void bfmeAssignSlotsVA();
void *bfmeTwoTB();

void bfmeOnceWE()
{
	if (g_bfmeCountWE <= 0)
	{
		bfmeAssignSlotsVA();
		_STL::_Bfme_classic_locale = (_STL::_Locale_impl *)bfmeTwoTB();
		++g_bfmeCountWE;
	}
}
