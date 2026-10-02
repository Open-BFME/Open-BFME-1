// cl: /DNDEBUG /MD /EHsc
// Address-derived Apt handler at 0x008CD210. The top stack value supplies
// a name; an empty name clears context +8, otherwise it resolves the name.
struct Rva8CD130StringBlock { unsigned short m_refs; unsigned short m_length; };
// The shared empty EA string block at 0x012D5298 is defined once, with its
// proven type, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp.  It is
// named here through a file-local view cast at each use so the DIR32 target is
// the one retail address.
class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;
static inline Rva8CD130StringBlock *rva012D5298Block() { return (Rva8CD130StringBlock *)&g_rva012D5298Empty; }
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
class Rva8CD130String {
public:
 Rva8CD130String() { m_block=rva012D5298Block(); ++rva012D5298Block()->m_refs; }
 ~Rva8CD130String() { Rva8CD130StringBlock *block=m_block; --block->m_refs; if(block->m_refs==0) Rva01337A30ReleaseTable[1](block); }
 Rva8CD130StringBlock *m_block;
};
class Rva8CD130Value {
public:
 virtual void addRef(); virtual void release();
 void getName(Rva8CD130String *);
 unsigned m_flags;
};
class Rva8CCCE0Value { public: virtual void addRef(); virtual void release(); };
Rva8CCCE0Value *rva8CC570Resolve(void *, void *, void *);
struct Rva008CD210State { int m_00; int m_04; Rva8CD130Value **m_08; };
struct Rva008CD210Context { unsigned m_00; void *m_04; Rva8CCCE0Value *m_08; unsigned m_0C; };
void resolveTopName008CD210(Rva008CD210State *state, Rva008CD210Context *context) {
 Rva8CD130Value *top=state->m_08[state->m_00-1];
 Rva8CD130String name;
 top->getName(&name);
 if(name.m_block->m_length==0) {
  if(context->m_08) context->m_08->release();
  context->m_08=0;
 } else {
  Rva8CCCE0Value *value=rva8CC570Resolve(context->m_04,context->m_08,&name);
  context->m_0C=0;
  context->m_08=value;
  value->addRef();
 }
 Rva8CD130Value *value=state->m_08[state->m_00-1];
 if(!((unsigned char)(value->m_flags>>30)&1)) value->release();
 --state->m_00;
}
