// ?bfmeMirror1281@BfmeSlotDispatcher1281@@QAEXHHI@Z
// partial score=0.6636 date=2026-10-03
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// EA Apt integer factory.  Its callers are the named integer-producing Apt
// handlers, and the body is the pooled Apt value constructor at 0x008A11E0.



struct Rva008D2A30Node
{
	void *m_vtable;
	unsigned int m_flags;
	union
	{
		Rva008D2A30Node *m_next;
		int m_value;
	};
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	Rva008D2A30Node **m_items;

	__forceinline void addPooled(Rva008D2A30Node *node)
	{
		int count = m_count;
		if (count >= m_capacity)
		{
			node->m_flags &= 0xbfffffff;
		}
		else
		{
			m_items[count] = node;
			m_count=count+1;
		}
	}
};

// Retail AptInteger::Create reads the adjacent pool head at 0x013387D0;
// AptBoolean and the Rva008D2A30 chain use the distinct 0x013387D4 head.
class Rva008D2A10;
extern Rva008D2A10 *g_rva008D2A10;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);

struct Rva00899560Value {
 virtual ~Rva00899560Value();
 unsigned m_flags;
 __forceinline Rva00899560Value(int type) {
  unsigned flags=(((m_flags&~63)|type)&0xf000803f)|0x8000;
  m_flags=flags|0x40000000;
  g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)this);
 }
};
struct Rva008A1110Value : Rva00899560Value {
 union {Rva008A1110Value *m_next; int m_value;};
 __forceinline Rva008A1110Value(int value):Rva00899560Value(7),m_value(value) {}
 void *operator new(unsigned n) {return Rva008C5D70Alloc(n);}
};
class AptInteger {public:
 static __forceinline Rva008A1110Value *Create(int value) {
  Rva008A1110Value *object=(Rva008A1110Value *)g_rva008D2A10;
  if(object) {
   g_rva008D2A10=(Rva008D2A10 *)object->m_next;
   g_rva8CD130IdleHook->addPooled((Rva008D2A30Node *)object);
   object->m_value=value;
  } else object=new Rva008A1110Value(value);
  return object;
 }
};

struct BfmeHdrVKI {unsigned short m_bfme00; unsigned short m_bfme02,m_bfme04,m_bfme06;};
struct BfmeStringPool3AF0 {void *field00; void (__cdecl *free)(void *);};
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class BfmeStrVKI {public:
 void bfmeSetVKI(const char *);
 BfmeHdrVKI *m_bfme00;
 BfmeStrVKI(const char *s) {bfmeSetVKI(s);}
 __forceinline ~BfmeStrVKI() {BfmeHdrVKI *p=m_bfme00; --p->m_bfme00; if(p->m_bfme00==0) g_bfmeStringPool1284->free(p);}
};
class Rva008A0F20Header {public: int isKind0F() const; void *vptr; unsigned flags;};
class Rva008AF650Object; class AptValue;
bool rva008AF650Implementation(Rva008AF650Object *,BfmeStrVKI *,AptValue *);
class BfmeSlotDispatcher1281 {public:
 char field000[0x924]; int field924; Rva008A0F20Header *field928[64]; char fielda28[0x1268-0xa28]; Rva008A0F20Header *field1268;
 void bfmeMirror1281(int,int,unsigned);
 void bfmeApplySlot1281(void *,int,void *);
};
void BfmeSlotDispatcher1281::bfmeMirror1281(int group,int slot,unsigned encoded)
{
 int visited=0;
 for(int index=0;index<64;++index) {
  if(visited==field924) break;
  Rva008A0F20Header *entry=field928[index];
  if(entry) {
   switch(slot) {
    case 0: if(group==0) bfmeApplySlot1281(entry,0x10,(void *)encoded); break;
    case 1: if(group==0) bfmeApplySlot1281(entry,0x20,(void *)encoded); break;
    case 3: case 4: {
     unsigned flags=entry->flags;
     int kind=flags&63;
     if(kind>=12 && kind<=19 && !((unsigned char)~(flags>>15)&1) && (unsigned char)entry->isKind0F()) {
      if(field1268==entry) {
       int amount=group;
       if(slot==4) amount=-amount;
       Rva008A1110Value *integer=AptInteger::Create(amount);
       BfmeStrVKI name("scroll");
       rva008AF650Implementation((Rva008AF650Object *)entry,&name,(AptValue *)integer);
      }
     } else bfmeApplySlot1281(entry,0x40000,(void *)encoded);
     break;
    }
   }
   ++visited;
  }
 }
}

