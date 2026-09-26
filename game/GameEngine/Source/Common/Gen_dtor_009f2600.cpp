// cl: /DNDEBUG /MD /EHsc

// Retail 0x009F5970 is the complete destructor for the generated class
// Gen_dtor_009f2600. It first calls the object's cleanup operation, then
// destroys seventeen twelve-byte elements at +0x18 through the MSVC EH vector
// destructor iterator. The cleanup body is the already-bound retail routine
// at 0x009F4ED0; its internal layout is independent of this destructor's
// trailing array.

struct Gen_uw_009f5690
{
	~Gen_uw_009f5690();
	int m_head;
	char m_body[0xC - sizeof(int)];
};

class __declspec(novtable) Gen_dtor_009f2600
{
public:
	virtual ~Gen_dtor_009f2600();
	void cleanup();

private:
	char m_pad[0x14];
	Gen_uw_009f5690 m_items[17];
};

Gen_dtor_009f2600::~Gen_dtor_009f2600()
{
	cleanup();
}
