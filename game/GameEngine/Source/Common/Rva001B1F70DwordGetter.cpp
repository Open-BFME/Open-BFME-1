// cl: /DNDEBUG /MD /EHsc

// The carved body reads one dword at this+0x0c and returns it. The caller and
// ILT thunk prove the address, but no evidence proves the owning class.
class Rva001B1F70DwordGetter
{
public:
	int get() const;

private:
	char m_padding[0x0c];
	int m_value;
};

int Rva001B1F70DwordGetter::get() const
{
	return m_value;
}
