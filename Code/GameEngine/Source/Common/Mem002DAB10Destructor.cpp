// Focused reconstruction of the pinned subobject destructor at 0x002DAB10.
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc

class BfmeDtorMemberD
{
public:
	~BfmeDtorMemberD();

private:
	unsigned int m_words[3];
};

class Rva00026AB2Vec12
{
public:
	~Rva00026AB2Vec12();

private:
	unsigned int m_words[3];
};

class Mem002DAB10
{
public:
	virtual void anchor();
	~Mem002DAB10();

private:
	unsigned char m_pad04[0x34];
	Rva00026AB2Vec12 m_38;
	Rva00026AB2Vec12 m_44;
	BfmeDtorMemberD m_50;
};

Mem002DAB10::~Mem002DAB10()
{
}
