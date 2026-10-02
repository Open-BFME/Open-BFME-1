extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes) { TheBfmeFree(p, bytes); }

private:
	char m_bfmePad[0x18];
};

// Retail caller 0x00896AF0 constructs this four-byte incoming reference by
// copying the pointer, incrementing its count, and registering its stack slot
// for exception cleanup. The callee retains its member then releases this
// by-value parameter; a raw pointer declaration hides the caller lifetime.
class BfmeRefVGO
{
public:
 BfmeRefVGO(const BfmeRefVGO &other) : m_bfmeP(other.m_bfmeP)
 {
  if(m_bfmeP) ++*(int*)m_bfmeP;
 }
 ~BfmeRefVGO()
 {
  if(m_bfmeP && --*(int*)m_bfmeP==0) delete m_bfmeP;
 }
 BfmeDropObjectA *m_bfmeP;
};

class Gen_00895670
{
public:
 Gen_00895670(BfmeRefVGO obj, void *extra);
private:
 void *m_zero;
 BfmeDropObjectA *m_obj;
 void *m_extra;
 char m_flag;
};

Gen_00895670::Gen_00895670(BfmeRefVGO obj, void *extra)
{
 m_zero=0;
 m_obj=obj.m_bfmeP;
 if(obj.m_bfmeP) ++*(int*)obj.m_bfmeP;
 m_extra=extra;
 m_flag=0;
}
