// The carved body at 0x00681D60 reads an unsigned dword at this plus 0x2c.
// No caller or class table proves the owning type, so the address-derived
// class name preserves the only identity this four-byte body proves.
class Rva00681D60DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x2c];
	unsigned int m_value;
};

unsigned int Rva00681D60DwordGetter::get() const
{
	return m_value;
}
