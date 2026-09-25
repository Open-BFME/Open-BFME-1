// ?d_00895790@@YAXXZ
// partial score=0.181185 date=2026-09-25
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
extern "C" int memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)
struct BfmeStringData3AF0
{
 unsigned short m_refCount, m_length, m_capacity, m_flags;
 char m_data[1];
};
struct BfmeStringPool3AF0
{
 void *m_slot0;
 void (__cdecl *m_release)(BfmeStringData3AF0 *);
};
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class BfmeStrVKI
{
public:
 BfmeStrVKI(const BfmeStrVKI &other):m_data(other.m_data){++m_data->m_refCount;}
 ~BfmeStrVKI(){if(--m_data->m_refCount==0)g_bfmeStringPool1284->m_release(m_data);}
 BfmeStringData3AF0 *m_data;
};
struct Rva00895790Item
{
 Rva00895790Item(const BfmeStrVKI &key,unsigned value):m_key(key),m_value(value){}
 BfmeStrVKI m_key;
 unsigned m_value;
};
class Rva00894120Vector
{
public:
 void rva00895790(const BfmeStrVKI &key,unsigned expected,unsigned replacement,unsigned fallback);
 void helper(void *,void *,void *);
 unsigned m_count;
 char m_pad04[4];
 Rva00895790Item *m_items;
};
void Rva00894120Vector::rva00895790(const BfmeStrVKI &key,unsigned expected,unsigned replacement,unsigned fallback)
{
 unsigned count=m_count;
 Rva00895790Item *item=m_items;
 if(item!=m_items+count){
  BfmeStringData3AF0 *k=key.m_data;
  int length=k->m_length;
  do{
   BfmeStringData3AF0 *s=item->m_key.m_data;
   if(s->m_length==length && (s==k || memcmp(s->m_data,k->m_data,length)==0)){
    if(item->m_value==expected)item->m_value=replacement;
    return;
   }
   ++item;
  }while(item!=m_items+count);
 }
 Rva00895790Item value(key,fallback);
 Rva00895790Item *position=m_items+m_count;
 Rva00895790Item *last=&value+1;
 Rva00895790Item *first=&value;
 helper(&first,&last,&position);
}
