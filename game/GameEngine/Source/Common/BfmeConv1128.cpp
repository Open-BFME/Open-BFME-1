// Open-BFME5 conversions.

namespace _STL
{
double __cdecl _Stl_string_to_double(const char *text);
long double __cdecl _Stl_string_to_long_double(const char *text);
}

struct BfmeS1128
{
	const char *m_text;
};

void bfmeGo1128A(BfmeS1128 *a, float *out)
{
	const char *text = a->m_text;

	*out = (float)_STL::_Stl_string_to_double(text);
}

void bfmeGo1128B(BfmeS1128 *a, double *out)
{
	const char *text = a->m_text;

	*out = _STL::_Stl_string_to_double(text);
}

void bfmeGo1128C(BfmeS1128 *a, double *out)
{
	const char *text = a->m_text;

	*out = _STL::_Stl_string_to_long_double(text);
}
