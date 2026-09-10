// ?Rva009B46E0ReadBits@@YAIPAUVp6RawBits@@H@Z
// partial score=0.65 date=2026-09-10
// cl: /O2 /Ob0 /DNDEBUG /MD
// Full retail reader [0x009B47B0,0x009B47FA), ret9B47F9 thenCC.
struct Vp6RawBits { unsigned bits; unsigned value; const unsigned char *next; };
static int Rva009B47B0ReadBit(Vp6RawBits *state)
{
 if(state->bits) { --state->bits; return (state->value>>state->bits)&1; }
 const unsigned char *next=state->next;
 unsigned value=next[0];
 value=(value<<8)+next[1];
 value=(value<<8)+next[2];
 value=(value<<8)+next[3];
 state->value=value;
 state->next=next+4;
 state->bits=31;
 return state->value>>31;
}
// C++ integration entry, absent from retail. Keeping the reader static gives
// MSVC its private EAX argument convention, proven by caller9B4A10 at
// call sites9B4BBE/9B4C20/9B4FB9/9B5034. Only the74B reader is claimed.
int ReadVp6RawBit(Vp6RawBits *state) { return Rva009B47B0ReadBit(state); }

extern unsigned g_rva01142BE0[];
static unsigned Rva009B46E0ReadBits(Vp6RawBits *state, int count)
{
 unsigned value=*(volatile unsigned *)&state->value;
 unsigned bits=*(volatile unsigned *)&state->bits;
 value &= g_rva01142BE0[bits];
 state->value=value;
 count -= bits;
 unsigned result=0;
 value=state->value;
 if(count>0) {
  result=value<<count;
  const unsigned char *next=state->next;
  unsigned first=next[0];
  unsigned word=next[1];
  word += first<<8;
  word=(word<<8)+next[2];
  word=(word<<8)+next[3];
  state->value=word;
  state->next=next+4;
  count-=32;
 }
 count=-count;
 state->bits=count;
 return (state->value>>count)|result;
}
unsigned ReadVp6RawBits(Vp6RawBits *state,int count) {return Rva009B46E0ReadBits(state,count);}
