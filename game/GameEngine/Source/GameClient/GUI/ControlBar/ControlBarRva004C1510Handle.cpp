// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Caller 4C15D0 steals clone's pointer into a by-value stack argument.
// EH cleanup C29060 destroys that argument through 499F30 if deletion throws.
class Rva004C1150AdapterBase { public: virtual ~Rva004C1150AdapterBase(); };
class Rva004C1510Handle {
public:
 Rva004C1510Handle(Rva004C1150AdapterBase *p):m_ptr(p) {}
 Rva004C1510Handle(Rva004C1510Handle &other):m_ptr(other.release()) {}
 ~Rva004C1510Handle() { delete m_ptr; }
 Rva004C1150AdapterBase *release() { Rva004C1150AdapterBase *p=m_ptr;m_ptr=0;return p; }
 Rva004C1510Handle &operator=(Rva004C1510Handle other);
private:
 Rva004C1150AdapterBase *m_ptr;
};
Rva004C1510Handle &Rva004C1510Handle::operator=(Rva004C1510Handle other)
{
 delete m_ptr;
 m_ptr=other.release();
 return *this;
}
