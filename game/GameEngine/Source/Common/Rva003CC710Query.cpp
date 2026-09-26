// cl: /O2 /Ob0

class Object;

class BFMEObjectStealthQuery
{
public:
	bool isStealthedAndUndetected(const Object *) const;
};

class Rva003CC710
{
	char m_lead[8];
	BFMEObjectStealthQuery *m_query;

public:
	bool query() const;
};

bool Rva003CC710::query() const
{
	return m_query->isStealthedAndUndetected(0);
}
