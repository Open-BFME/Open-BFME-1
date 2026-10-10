// ?method@Rva008BDBB0@@QAEXHH@Z
// partial score=1.0 date=2026-10-10
// cl: /DNDEBUG /MD
class BfmeZero1236 { public: __declspec(noinline) BfmeZero1236(); void *items[32]; int count; };
struct Rva008BDBB0Pending { void *volatile items[32]; int count; };
struct Rva008BD5B0Key { int unused; int value; };
struct Rva008BD5B0Item { char pad[0x50]; Rva008BD5B0Key *key; };
class Rva008BD5B0 { public: __declspec(noinline) void insert(Rva008BD5B0Item *); Rva008BD5B0Item *items[32]; int count; };
class BfmeA1236;
class BfmeB1236;
void bfmeGo1236(BfmeA1236 *,BfmeB1236 *,void *);
void bfmeTransform1236(void *,BfmeB1236 *,void *);
extern unsigned char g_bfmeExtra1282Flags;
struct Rva008BDBB0Child { int m_00; int m_04; };
struct Rva008BDBB0Node {
 void *m_00; unsigned m_04; int m_08; char m_0c[0x44];
 Rva008BDBB0Child *m_50; int m_54; Rva008BDBB0Node *m_58;
};
struct Rva008BDBB0List { Rva008BDBB0Node *m_00; };
class Rva008BDBB0 { public: void method(int a,int b); Rva008BDBB0List *m_00; };
void Rva008BDBB0::method(int a,int b) {
 void *context=(void *)a;
 Rva008BDBB0Node *node=m_00->m_00->m_58;
 BfmeZero1236 storage;
 Rva008BDBB0Pending &pending=(Rva008BDBB0Pending &)storage;
 void (__cdecl *emit)(void *,BfmeB1236 *,void *);
 if (g_bfmeExtra1282Flags & 4) emit=bfmeTransform1236;
 else emit=(void (__cdecl *)(void *,BfmeB1236 *,void *))bfmeGo1236;
 while (node) {
  if (!((unsigned char)(~(node->m_04 >> 15)) & 1) && (node->m_04 & 0x3f) != 0x13) {
   if (node->m_50->m_04 >= 0) {
    ((Rva008BD5B0 *)&pending)->insert((Rva008BD5B0Item *)node);
    emit(context,(BfmeB1236 *)node,(void *)1);
   } else {
    while (pending.count > 0 && ((Rva008BDBB0Node *)pending.items[pending.count-1])->m_50->m_04 < node->m_08) {
     emit(context,(BfmeB1236 *)pending.items[pending.count-1],(void *)-1);
     --pending.count;
    }
    emit(context,(BfmeB1236 *)node,(void *)b);
   }
  }
  node=node->m_58;
 }
 while (pending.count > 0) {
  emit(context,(BfmeB1236 *)pending.items[0],(void *)-1);
  for (int i=0;i < pending.count-1;++i) pending.items[i]=pending.items[i+1];
  --pending.count;
 }
}

BfmeZero1236::BfmeZero1236() { count=0; for(int i=0;i<32;++i) items[i]=0; }

void Rva008BD5B0::insert(Rva008BD5B0Item *item)
{
	int index = 0;
	if (count > 0)
	{
		int value = item->key->value;
		while (index < count && items[index]->key->value >= value)
			++index;
	}
	for (int i = count; i > index; --i)
		items[i] = items[i - 1];
	items[index] = item;
	++count;
}

