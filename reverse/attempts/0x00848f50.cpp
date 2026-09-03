// ?_Stl_put_inf_nan@_STL@@YAXPADNH@Z
// partial score=0.95 date=2026-09-03
// cl: /O2 /EHsc /MD
// STLport 4.5.3 num_put inf/nan writer (_fpclass + _Stl_is_neg_nan).
// Near miss: 155B==155B; inf/nan middle blocks swapped vs retail
// (ours lays nan first). Tail from +0x65 and prologue through cmp eax,4 match.

extern "C" {
	__declspec(dllimport) int __cdecl _fpclass(double);
}

namespace _STL {

bool _Stl_is_neg_nan(double x);

static const char *nan_name[2] = { "nan", "NaN" };
static const char *inf_name[2] = { "inf", "Inf" };

void _Stl_put_inf_nan(char *buf, double x, int flags)
{
	const char **table;
	int klass = _fpclass(x);
	if (klass == 4 || klass == 0x200)
	{
		table = inf_name;
		if (_fpclass(x) == 4)
		{
			*buf = '-';
			++buf;
			goto copy;
		}
	}
	else
	{
		table = nan_name;
		if (_Stl_is_neg_nan(x))
		{
			*buf = '-';
			++buf;
			goto copy;
		}
	}
	if (flags & 0x0800)
	{
		*buf = '+';
		++buf;
	}
copy:
	{
		const char *src = (flags & 0x4000) ? table[1] : table[0];
		char c;
		do
		{
			c = *src++;
			*buf++ = c;
		} while (c);
	}
}

} // namespace _STL
