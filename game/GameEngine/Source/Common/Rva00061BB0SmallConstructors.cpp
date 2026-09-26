// cl: /DNDEBUG /MD /EHs-c-
// Three small constructors recovered from the retail image. Their identities
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

class Rva00061BB0Owner
{
public:
	Rva00061BB0Owner(void *source);

private:
	void attach(void *source);
	Int m_value00;
};

// ??0Rva00061BB0Owner@@QAE@PAX@Z
Rva00061BB0Owner::Rva00061BB0Owner(void *source)
{
	m_value00 = 0;
	attach(source);
}

class Rva00065C50Owner
{
public:
	Rva00065C50Owner(void *source);

private:
	void attach(void *source);
	Int m_value00;
};

