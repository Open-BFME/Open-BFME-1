// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: clean C++ lift of retail FUN_004c7bf0 at 0x000C7BF0.
// The one callee-cleaned argument is not used; identity is not recovered.
class Rva000C7BF0Holder
{
public:
	int get(int unused) const;

private:
	char m_padding[8];
	int m_value;
};

int Rva000C7BF0Holder::get(int unused) const
{
	return m_value;
}
