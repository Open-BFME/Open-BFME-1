// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00383B40
{
	char m_pad[0x1C0];
	struct Slot
	{
		char flag;
		int value;
		Rva0036CA00Str str;
		char rest[0x10];
	} m_slots[8];

public:
	void set(int index, Rva0036CA00Str *str, int value);
};

void Rva00383B40::set(int index, Rva0036CA00Str *str, int value)
{
	if (index < 0 || index >= 8)
		return;
	m_slots[index].flag = 0;
	reinterpret_cast<StringBase<char> &>(m_slots[index].str).set(
		reinterpret_cast<const StringBase<char> &>(*str));
	m_slots[index].value = value;
}
