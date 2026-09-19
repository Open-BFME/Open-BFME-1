// The carved body at 0x00471F70 reads the dword at this+0x2C.
// No caller or class table proves a semantic owner, so the address remains in the name.
class Rva00471F70
{
public:
	int getAt2C() const;

private:
	int m_field;
};

int Rva00471F70::getAt2C() const
{
	return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0x2C);
}
