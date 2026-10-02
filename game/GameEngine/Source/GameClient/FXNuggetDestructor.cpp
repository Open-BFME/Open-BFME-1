// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();

private:
	UnsignedInt m_bfmeHandle;
};

class FXNugget
{
public:
	virtual ~FXNugget();

private:
	int m_flags;
	AttributeHandleStandIn m_sourceAttribute;
	AttributeHandleStandIn m_victimAttribute;
};

FXNugget::~FXNugget()
{
}
