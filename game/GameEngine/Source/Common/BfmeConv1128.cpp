// Open-BFME5 conversions.

namespace _STL
{
double __cdecl _Stl_string_to_double(const char *text);
long double __cdecl _Stl_string_to_long_double(const char *text);
}

struct BfmeS1128
{
	const char *m_bfme00;
};

void bfmeGo1128A(BfmeS1128 *a, float *out)
{
	const char *v = a->m_bfme00;

	*out = (float)_STL::_Stl_string_to_double(v);
}

void bfmeGo1128B(BfmeS1128 *a, double *out)
{
	const char *v = a->m_bfme00;

	*out = _STL::_Stl_string_to_double(v);
}

void bfmeGo1128C(BfmeS1128 *a, double *out)
{
	const char *v = a->m_bfme00;

	*out = _STL::_Stl_string_to_long_double(v);
}
