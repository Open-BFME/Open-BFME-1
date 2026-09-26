// cl: /O2 /Ob0

struct Rva0090C6A0Interface;
struct Rva0090C6A0Vtable
{
	void *m_prior[10];
	bool (__fastcall *m_getFlag)(Rva0090C6A0Interface *);
};
struct Rva0090C6A0Interface
{
	Rva0090C6A0Vtable *m_vtable;
};
class Rva0090C6A0VirtualFlag
{
	Rva0090C6A0Interface *m_inner;
public:
	bool get() const;
};
bool Rva0090C6A0VirtualFlag::get() const
{
	return m_inner ? m_inner->m_vtable->m_getFlag(m_inner) : false;
}
