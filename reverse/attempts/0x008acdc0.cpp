// ?d_008acdc0@@YAXXZ
// partial score=0.939252 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class BfmeStrVKI;
extern void bfmeResetEVF(void *context, BfmeStrVKI *text);

class BfmeStrVKI
{
public:
 BfmeStrVKI():m_data(&g_bfmeDefaultString1284) { ++m_data->m_refCount; }
 BfmeStrVKI(const BfmeStrVKI &other):m_data(other.m_data) { ++m_data->m_refCount; }
 BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
 void bfmeSetVKI(const char *);
 ~BfmeStrVKI() {
  BfmeStringData3AF0 *data=m_data;
  if(--data->m_refCount==0)g_bfmeStringPool1284->free(data);
 }
 BfmeStringData3AF0 *m_data;
};
class Rva8CD130String:public BfmeStrVKI {
public:
 Rva8CD130String() {}
 Rva8CD130String(const Rva8CD130String &other):BfmeStrVKI(other){}
 Rva8CD130String(const char *text):BfmeStrVKI(text){}
};
class Rva00896AF0Tracker
{
public:
	void rva00896AF0(Rva8CD130String *input, Rva8CD130String text);
};

extern Rva00896AF0Tracker *Rva013377F8;
class AptValue;
extern AptValue *g_bfmeFallbackDB;
AptValue *Rva008ACDC0(void *context)
{
 Rva8CD130String input;
 bfmeResetEVF(context,&input);
 Rva013377F8->rva00896AF0(&Rva8CD130String(""),input);
 return g_bfmeFallbackDB;
}
