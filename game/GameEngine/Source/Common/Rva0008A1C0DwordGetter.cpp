// cl: /DNDEBUG /MD /EHsc

// The carved body reads one dword at this+0x14 and returns it. The ILT thunk
// at 0x00009B83 reaches the body, but no evidence proves its owning class.
class Rva0008A1C0DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x14];
	unsigned int m_value;
};

unsigned int Rva0008A1C0DwordGetter::get() const
{
	return m_value;
}
