// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: clean C++ lift of retail FUN_004c7c30 at 0x000C7C30.
// The one callee-cleaned argument is not used; identity is not recovered.
class Rva000C7C30Holder
{
public:
	int get(int unused) const;

private:
	char m_padding[4];
	int m_left;
	int m_right;
};

int Rva000C7C30Holder::get(int unused) const
{
	return m_left - m_right;
}
