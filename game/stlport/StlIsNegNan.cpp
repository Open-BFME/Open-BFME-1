// cl: /O2 /EHsc /MD
// STLport 4.5.3 _Stl_is_neg_nan from src/num_put.cpp.

extern "C" {
	__declspec(dllimport) int __cdecl _isnan(double);
	__declspec(dllimport) double __cdecl _copysign(double, double);
}

namespace _STL {

bool _Stl_is_neg_nan(double x)
{
	return _isnan(x) && _copysign(1.0, x) < 0.0;
}

} // namespace _STL
