// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Rva0029BBF0FloatGetter
{
public:
	float get() const;

private:
	char m_padding[0x14];
	float m_value;
};

// @?get@Rva0029BBF0FloatGetter@@QBEMXZ 0x0029BBF0
float Rva0029BBF0FloatGetter::get() const
{
	return m_value;
}
