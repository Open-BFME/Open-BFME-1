// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Three-entry lazy callback dispatch at RVA 008B5940; INT3 start and RET8 end.
// Incoming ECX is unused; two stack arguments and RET 8.
struct R4Word { const char *name; int value; };
const R4Word *Rva008B5610(const char *, unsigned);
void *Rva00897640(unsigned);
class Rva00897670HeaderedDelete {
public:
    static void operator delete(void *, unsigned);
};
class Rva00899FC0 : public Rva00897670HeaderedDelete {
public:
    static void *operator new(unsigned n) { return Rva00897640(n); }
    __declspec(noinline) Rva00899FC0(int callback);
    void *vtable;
    unsigned flags;
    char gap08[0x18];
    int callback;
};
class BfmeS1083 {
public:
    virtual void unused0();
    virtual void release();
};
struct StringBuffer008B5940 { unsigned short refs, length; };
struct String008B5940 { StringBuffer008B5940 *data; };
extern BfmeS1083 *g_bfmeS1083_0;
extern BfmeS1083 *g_bfmeS1083_1;
extern BfmeS1083 *g_bfmeS1083_2;
extern char Callback00CB5770[];
extern char Callback00CB5720[];
extern char Callback00CB5760[];
BfmeS1083* __stdcall Rva008B5940Lookup(void* owner,const String008B5940* key)
{
 if(owner) {
 const R4Word* word=Rva008B5610((const char*)key->data+8,key->data->length);
 if(word) {
 switch(word->value) {
 case 1:
  if(!g_bfmeS1083_0) {
   g_bfmeS1083_0=(BfmeS1083*)new Rva00899FC0((int)Callback00CB5770);
   Rva00899FC0* value=(Rva00899FC0*)g_bfmeS1083_0;
   value->flags=(value->flags&0xffffc07f)|0x40;
   g_bfmeS1083_0->unused0();
  }
  return g_bfmeS1083_0;
 case 2:
  if(!g_bfmeS1083_2) {
   g_bfmeS1083_2=(BfmeS1083*)new Rva00899FC0((int)Callback00CB5720);
   Rva00899FC0* value=(Rva00899FC0*)g_bfmeS1083_2;
   value->flags=(value->flags&0xffffc07f)|0x40;
   g_bfmeS1083_2->unused0();
  }
  return g_bfmeS1083_2;
 case 3:
  if(!g_bfmeS1083_1) {
   g_bfmeS1083_1=(BfmeS1083*)new Rva00899FC0((int)Callback00CB5760);
   Rva00899FC0* value=(Rva00899FC0*)g_bfmeS1083_1;
   value->flags=(value->flags&0xffffc07f)|0x40;
   g_bfmeS1083_1->unused0();
  }
  return g_bfmeS1083_1;
 }
 }
 }
 return 0;
}
