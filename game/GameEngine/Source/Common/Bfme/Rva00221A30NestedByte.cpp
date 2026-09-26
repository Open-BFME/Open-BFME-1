// cl: /DNDEBUG /MD /EHsc

struct Rva00221A30Nested
{
	unsigned char m_padding[0x156];
	unsigned char m_flag;
};

class Rva00221A30
{
public:
	signed char hasNestedFlag() const;

};

signed char Rva00221A30::hasNestedFlag() const
{
	Rva00221A30Nested *nested = *reinterpret_cast<Rva00221A30Nested **>(
		reinterpret_cast<unsigned char *>(const_cast<Rva00221A30 *>(this)) - 0x1C);
	return nested->m_flag != 0;
}
