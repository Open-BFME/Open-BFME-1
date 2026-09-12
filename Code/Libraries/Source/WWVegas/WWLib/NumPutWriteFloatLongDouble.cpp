// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.6.2 long-double floating-point writer for BFME's string ABI.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>

#define BFME_MAX_ECVT 35
#define BFME_MAX_FCVT 36

_STLP_BEGIN_NAMESPACE

extern "C" __declspec(dllimport) char *__cdecl _ecvt(
	double, int, int *, int *);
extern "C" __declspec(dllimport) char *__cdecl _fcvt(
	double, int, int *, int *);

extern "C" __declspec(dllimport) int __cdecl _finite(double);

void __cdecl _Stl_put_inf_nan(char *, double, int);

void __cdecl BfmeFormatFloatScientific(char *, const char *, int, int,
	double, ios_base::fmtflags, int, bool);

void __cdecl BfmeFormatFloatFixed(string &, const char *, int, int, bool,
	ios_base::fmtflags, int, bool);

template <class Float>
static inline void bfmeFormatFloat(string &buffer, const char *digits,
	int decimal, int negative, Float value, ios_base::fmtflags flags,
	int precision, bool isLong)
{
	char staticBuffer[128];

	if (!_finite((double)value))
	{
		_Stl_put_inf_nan(staticBuffer, (double)value, flags);
		buffer = staticBuffer;
	}
	else
	{
		switch (flags & ios_base::floatfield)
		{
		case ios_base::scientific:
			BfmeFormatFloatScientific(staticBuffer, digits, decimal, negative,
				(double)value, flags, precision, isLong);
			buffer = staticBuffer;
			break;
		case ios_base::fixed:
			BfmeFormatFloatFixed(buffer, digits, decimal, negative, true,
				flags, precision, isLong);
			break;
		default:
			if ((flags & ios_base::showpoint) || precision > 0)
			{
				if (precision == 0)
					precision = 1;
			}
			else
				precision = 6;

			if (value == 0)
				decimal = 1;

			int significant = precision;
			if (!(flags & ios_base::showpoint))
			{
				unsigned int count = (unsigned int)strlen(digits);
				if (count < (unsigned int)significant)
					significant = (int)count;
				while (significant >= 1 && digits[significant - 1] == '0')
					--significant;
			}

			if (decimal < -3 || decimal > precision)
			{
				precision = significant - 1;
				BfmeFormatFloatScientific(staticBuffer, digits, decimal,
					negative, (double)value, flags, precision, isLong);
				buffer = staticBuffer;
			}
			else
			{
				precision = significant - decimal;
				BfmeFormatFloatFixed(buffer, digits, decimal, negative, true,
					flags, precision, isLong);
			}
			break;
		}
	}
}

static char *bfmeEcvt(long double value, int digits,
	int *decimal, int *negative, char *)
{
	return _ecvt((double)value, digits, decimal, negative);
}

static char *bfmeFcvt(long double value, int digits,
	int *decimal, int *negative, char *)
{
	return _fcvt((double)value, digits, decimal, negative);
}

void _STLP_CALL __write_float(string &buffer, ios_base::fmtflags flags,
	int precision, long double value)
{
	char conversion[84];
	char *digits;
	int decimal;
	int negative;

	switch (flags & ios_base::floatfield)
	{
	case ios_base::fixed:
		digits = bfmeFcvt(value, (min)(precision, BFME_MAX_FCVT),
			&decimal, &negative, conversion);
		break;
	case ios_base::scientific:
		digits = bfmeEcvt(value, (min)(precision + 1, BFME_MAX_ECVT),
			&decimal, &negative, conversion);
		break;
	default:
		digits = bfmeEcvt(value, (min)(precision, BFME_MAX_ECVT),
			&decimal, &negative, conversion);
		break;
	}

	bfmeFormatFloat(buffer, digits, decimal, negative, value,
		flags, precision, true);
}

_STLP_END_NAMESPACE
