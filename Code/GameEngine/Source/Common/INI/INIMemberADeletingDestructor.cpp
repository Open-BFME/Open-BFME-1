// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x009CC200 is the compiler scalar-deleting wrapper around the matched
// INIMemberA destructor at 0x009CBFE0.

class INIMemberA
{
public:
	~INIMemberA();
};

void DeleteINIMemberA(INIMemberA *member)
{
	delete member;
}
