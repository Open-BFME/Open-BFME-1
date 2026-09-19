// The carved boundary at 0x003F7A90 loads the first dword from its receiver.
// No caller or class table proves the owning type.
class Rva003F7A90DwordGetter
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

unsigned int Rva003F7A90DwordGetter::get() const
{
	return m_value;
}
