// cl: /DNDEBUG /MD /EHsc

// The two calls identify this as a thin derived destructor over the matched
// Gen_0060B470 counted container: clear its elements, then destroy the base.
class Gen_0060B470
{
public:
	~Gen_0060B470();
	void bfmeClear();
};

class Rva0060B6B0 : public Gen_0060B470
{
public:
	~Rva0060B6B0();
};

// ??1Rva0060B6B0@@QAE@XZ
Rva0060B6B0::~Rva0060B6B0()
{
	bfmeClear();
}
