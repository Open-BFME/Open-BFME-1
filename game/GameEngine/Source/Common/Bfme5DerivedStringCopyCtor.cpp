class Rva0057D2D0Base
{
public:
	Rva0057D2D0Base(const Rva0057D2D0Base &other);
	virtual ~Rva0057D2D0Base(void);

private:
	int m_bfmeFields[4];
};

class Rva0009F820String
{
public:
	Rva0009F820String(const Rva0009F820String &other);
	~Rva0009F820String(void);

private:
	char *m_bfmeText;
};

class Gen_0057ECF0 : public Rva0057D2D0Base
{
public:
	Gen_0057ECF0(const Gen_0057ECF0 &other);
	virtual ~Gen_0057ECF0(void);

private:
	Rva0009F820String m_bfmeString;
};

// ??0Gen_0057ECF0@@QAE@ABV0@@Z
Gen_0057ECF0::Gen_0057ECF0(const Gen_0057ECF0 &other) :
	Rva0057D2D0Base(other),
	m_bfmeString(other.m_bfmeString)
{
}
