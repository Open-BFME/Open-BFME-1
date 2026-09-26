// cl: /DNDEBUG /MD /EHsc

class BfmeDtorMemberD
{
public:
	~BfmeDtorMemberD();

private:
	int m_handle;
};

class FXNugget
{
public:
	virtual ~FXNugget();

private:
	int m_flags;
	BfmeDtorMemberD m_sourceAttribute;
	BfmeDtorMemberD m_victimAttribute;
};

FXNugget::~FXNugget()
{
}
