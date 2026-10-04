// cl: /DNDEBUG /MD /EHs-c-
// Two small constructors recovered from the retail image. Their identities
// remain address-derived; the two attach callees are independently pinned.

typedef int Int;

class Rva00071B90Holder
{
public:
	Rva00071B90Holder(void *target);
	virtual void slot00(void);

private:
	void *m_target;
};

// ??0Rva00071B90Holder@@QAE@PAX@Z
Rva00071B90Holder::Rva00071B90Holder(void *target)
{
	m_target = target;
}

class Rva00065C50Owner
{
public:
	Rva00065C50Owner(void *source);

private:
	void attach(void *source);
	Int m_value00;
};

