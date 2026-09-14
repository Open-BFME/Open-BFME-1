// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: NamedTimerInfo's complete destructor at retail RVA 0x0043DB30
// (83 bytes) and scalar-deleting destructor at 0x0043DB00 (30 bytes).
// The exact constructor at 0x0043DAE0 installs vtable 0x010F5758. Its two
// members at +4 and +8 are the retail AsciiString and UnicodeString objects
// destroyed here in reverse order. Vtable slot zero routes through ILT
// 0x0003B42B to the deleting wrapper, which calls the complete destructor
// through ILT 0x000198A3. The protected destructor matches the pool-glue
// declaration used by the original NamedTimerInfo class.

class BfmeNamedTimerAsciiString
{
public:
	~BfmeNamedTimerAsciiString();

private:
	int m_data;
};

class BfmeNamedTimerUnicodeString
{
public:
	~BfmeNamedTimerUnicodeString();

private:
	int m_data;
};

class NamedTimerInfo
{
protected:
	virtual ~NamedTimerInfo();

private:
	friend void forceNamedTimerInfoDeletingDestructor();
	BfmeNamedTimerAsciiString m_timerName;
	BfmeNamedTimerUnicodeString m_timerText;
};

NamedTimerInfo::~NamedTimerInfo()
{
}

void forceNamedTimerInfoDeletingDestructor()
{
	NamedTimerInfo value;
}
