// cl: /DNDEBUG /MD /EHsc
// Opaque complete bodies from the adjacent carved tiny-body batch.

class Rva000B21C0Owner
{
public:
	float body() const;

private:
	char m_padding[0x4C];
	float m_value;
};

// ?body@Rva000B21C0Owner@@QBEMXZ
float Rva000B21C0Owner::body() const
{
	return m_value;
}

class Rva000B9A60Owner
{
public:
	const char *body() const;

private:
	char m_padding[0x14];
	char m_value;
};

// ?body@Rva000B9A60Owner@@QBEPBDXZ
const char *Rva000B9A60Owner::body() const
{
	return &m_value;
}

class Rva00102330InputStream
{
public:
	Rva00102330InputStream();
	virtual int read(void *buffer, int count) = 0;
};

// ??0Rva00102330InputStream@@QAE@XZ
Rva00102330InputStream::Rva00102330InputStream()
{
}
