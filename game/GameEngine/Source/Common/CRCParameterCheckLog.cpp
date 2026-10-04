// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <stdarg.h>
#include <vector>

extern "C" __declspec(dllimport) int __cdecl _vsnprintf(
	char *, unsigned int, const char *, va_list);

#include "string_base.h"

#include "ascii_string.h"

// The overflow call at retail RVA 0x00065D28 goes through 0x0003827B
// to 0x00063700, not the canonical vector<AsciiString> copy at 0x00757C70.
// Reuse the existing address-qualified provider without instantiating another
// copy of its helpers. Its ECX receiver is a three-pointer range; the five
// stack arguments are position, value, tag, count and at-end (ret 0x14).
// The element stays incomplete: its generated name is only the existing
// provider's COFF identity, not a recovered EA type. The helper's construct
// path at 0x000620B0 calls the same StringBase<char> copy constructor as here.
class Open2Elem063700;
namespace _STL
{
template <> void vector<Open2Elem063700>::_M_insert_overflow(
	Open2Elem063700 *, const Open2Elem063700 &, const __false_type &,
	unsigned int, bool);
}

class Rva00063700VectorView : public _STL::vector<Open2Elem063700>
{
public:
	using _STL::vector<Open2Elem063700>::_M_insert_overflow;
};

struct Rva00065C80Range
{
	AsciiString *first;
	AsciiString *finish;
	AsciiString *endOfStorage;
};

static __forceinline void rva00065C80Construct(
	AsciiString *where, const AsciiString &value)
{
	// Preserve the inlined _Construct boundary and its placement-new EH state.
	new (where) AsciiString(value);
}

class CRCParameterCheck
{
public:
	Rva00065C80Range m_parameters;

private:
	virtual ~CRCParameterCheck();
};

extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...)
{
	if (format == 0)
		return;

	char buffer[1000];
	va_list args;

	va_start(args, format);
	_vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	AsciiString value(buffer);
	Rva00065C80Range &parameters = check->m_parameters;
	if (parameters.finish != parameters.endOfStorage)
	{
		rva00065C80Construct(parameters.finish, value);
		++parameters.finish;
	}
	else
	{
		_STL::__false_type tag;
		reinterpret_cast<Rva00063700VectorView *>(&parameters)->_M_insert_overflow(
			reinterpret_cast<Open2Elem063700 *>(parameters.finish),
			reinterpret_cast<const Open2Elem063700 &>(value),
			tag, 1, true);
	}
}
