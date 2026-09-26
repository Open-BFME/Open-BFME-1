// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
class S4Sink004135C0
{
public:
	void invoke(const AsciiString &, int, int, int, int);
};
class Rva001F6960
{
public:
	void apply(S4Sink004135C0 *, int);
private:
	void *m_vtable;
	struct Data *m_data;
};
struct Data
{
	char m_padding[0x18];
	AsciiString *m_begin;
	AsciiString *m_end;
};
void Rva001F6960::apply(S4Sink004135C0 *sink, int flag)
{
	if (!sink)
		return;
	register Data *const data = m_data;
	for (AsciiString *name = data->m_begin; name != data->m_end;)
	{
		AsciiString old(*name);
		{
			AsciiString value(*(char **)&old ? *(char **)&old + 8 : "");
			sink->invoke(value, flag, 1, 0, 0);
		}
		++name;
	}
}
