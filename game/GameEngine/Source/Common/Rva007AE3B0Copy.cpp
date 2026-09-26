// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva007AE3B0Vec
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

class Rva007AE3B0Copy
{
public:
	void copyTo(Rva007AE3B0Vec *out);

	char m_pad[8];
	Rva007AE3B0Vec m_vec;
};

void Rva007AE3B0Copy::copyTo(Rva007AE3B0Vec *out)
{
	*out = m_vec;
}

class Rva007AF2E0Copy
{
public:
	void copyTo(Rva007AE3B0Vec *out);

	char m_pad[8];
	Rva007AE3B0Vec m_vec;
};

void Rva007AF2E0Copy::copyTo(Rva007AE3B0Vec *out)
{
	*out = m_vec;
}
