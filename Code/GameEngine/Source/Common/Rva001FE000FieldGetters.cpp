// Each ILT thunk establishes a member-call entry, but no caller, vtable, or
// string evidence identifies the owning type. Keep each address in its name.
class DwordAccessor001FE000
{
public:
	int getDword001FE000() const;

private:
	char m_lead[0x7C];
	int m_field7C;
};

int DwordAccessor001FE000::getDword001FE000() const
{
	return m_field7C;
}

class ByteAccessor001FE020
{
public:
	unsigned char getByte001FE020() const;

private:
	char m_lead[0x24];
	unsigned char m_field24;
};

unsigned char ByteAccessor001FE020::getByte001FE020() const
{
	return m_field24;
}

class DwordAccessor001FE180
{
public:
	int getDword001FE180() const;

private:
	int m_field00;
	int m_field04;
};

int DwordAccessor001FE180::getDword001FE180() const
{
	return m_field04;
}
