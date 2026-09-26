// cl: /DNDEBUG /MD /EHsc

struct Rva002DA450Nested
{
	unsigned char m_padding[0x2A0];
	unsigned m_flags;
};

class Rva002DA450
{
public:
	void setNestedFlag();
};

void Rva002DA450::setNestedFlag()
{
	Rva002DA450Nested *nested = *reinterpret_cast<Rva002DA450Nested **>(
		reinterpret_cast<unsigned char *>(this) - 8);
	nested->m_flags |= 0x20;
}
