// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB

class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
	virtual ~Rva899F00Base();

private:
	char m_base[0x1c];
};

class Rva008B4630Callback
{
public:
	virtual void invoke();

	unsigned int m_flags;
};

class Rva008B4630 : public Rva899F00Base
{
public:
	Rva008B4630(Rva008B4630Callback *callback);

private:
	Rva008B4630Callback *m_callback;
};

Rva008B4630::Rva008B4630(Rva008B4630Callback *callback) :
	Rva899F00Base(reinterpret_cast<const char *>(0x1a), 8)
{
	*reinterpret_cast<void **>(this) = reinterpret_cast<void *>(0x01136A90);

	unsigned int flags = callback->m_flags;
	int kind = flags & 0x3f;
	unsigned char shifted = (unsigned char)(flags >> 15);
	if (kind >= 0x0c && kind <= 0x13 &&
		(((unsigned char)~shifted) & 1) == 0)
	{
		if (kind == 0x0d || kind == 0x12 || kind == 0x0f)
		{
			m_callback = callback;
			callback->invoke();
		}
	}
	else
	{
		m_callback = 0;
	}
}
