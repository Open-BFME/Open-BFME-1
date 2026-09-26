// The carved body at 0x00097160 loads a dword at receiver offset 4.
// The thunk caller proves a member ABI but no semantic owner.

class Rva00097160Owner
{
public:
	__declspec(noinline) int get() const;

	char m_prefix[4];
	int m_value;
};

__declspec(noinline) int Rva00097160Owner::get() const
{
	return m_value;
}
