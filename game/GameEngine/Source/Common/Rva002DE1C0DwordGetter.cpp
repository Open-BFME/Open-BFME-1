// cl: /DNDEBUG /MD /EHsc

// The carved body reads one dword at this+0x38 and returns it. The caller and
// ILT thunk prove the address, but no evidence proves the owning class.
class Rva002DE1C0DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[ 0x38 ];
	unsigned int m_value;
};

unsigned int Rva002DE1C0DwordGetter::get() const
{
	return m_value;
}
