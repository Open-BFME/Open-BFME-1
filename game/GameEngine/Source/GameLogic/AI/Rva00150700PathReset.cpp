// ?reset@Rva00150700Owner@@QAEXXZ
// Open-BFME: retail 0x00150700, 59 bytes.
// Path::~Path is the callee reached through ILT 0x0000CA68.
// The fields from +0x18 through +0x30 match the BFME AIGroup path reset.
// No caller names this owner or method, so the class keeps the retail RVA.

void __cdecl operator delete(void *) throw();

class __declspec(novtable) Path
{
protected:
	virtual ~Path(void) throw();
};

class BFMEDeletablePath : public Path
{
public:
	void destroy(void) { Path::~Path(); }
};

class Rva00150700Owner;

class PathDeleteArgument
{
public:
	PathDeleteArgument(Path *path, Rva00150700Owner *owner) :
		m_path(path), m_owner(owner) { }
	operator void *(void) const { return m_path; }
	~PathDeleteArgument();

private:
	Path *m_path;
	Rva00150700Owner *m_owner;
};

class Rva00150700Owner
{
public:
	void reset(void);
	friend class PathDeleteArgument;

private:
	unsigned char m_head[0x18];
	Path *m_groundPath;
	void *m_pathState1C;
	void *m_pathState20;
	void *m_pathState24;
	float m_pathState28;
	void *m_pathState2C;
	void *m_pathState30;
};

PathDeleteArgument::~PathDeleteArgument()
{
	m_owner->m_groundPath = 0;
	m_owner->m_pathState1C = 0;
	m_owner->m_pathState20 = 0;
	m_owner->m_pathState24 = 0;
}

void Rva00150700Owner::reset(void)
{
	if (m_groundPath)
	{
		Path *p = m_groundPath;
		reinterpret_cast<BFMEDeletablePath *>(p)->destroy();
		operator delete(PathDeleteArgument(p, this));
		m_pathState28 = 10.0f;
		m_pathState2C = 0;
		m_pathState30 = 0;
	}
}
