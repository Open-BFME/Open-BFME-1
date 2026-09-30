// ?Rva003C5270Find@@YGHPAVRva003C5820Owner@@PAVRva003C5820Key@@@Z
// partial score=0.9834 date=2026-09-30
// Bankable near match: retail RVA 0x003C5270, 181 bytes.
// Complete ret 8 at RVA 0x003C5322 ends at 0x003C5325.
// Caller Rva003C5820Owner::appendMatch at 0x003C5820 proves the two-stack-
// argument stdcall ABI through its FindFunction declaration.
// Probe: ours181 retail181, exactly3 differing non-relocation bytes.
// Retail loads initial owner into EDX; ours uses EAX for that same initial
// load and its two dereferences. Every later instruction matches exactly.
// Borrowed-view comparator and unsigned count replace the old 0.29 draft.
// Declare count before index to preserve the retail's later register map.
// Tested definition-order permutations, pointer/reference/const parameters,
// inline size helper, inline core wrapper, count arithmetic spellings and
// /G5 /G6 /G7 /O1 /Os /Ot /Ob2 /Og /Oy- /Og- shaping flags.
// Both DIR32 references independently decode to empty-string VA0x0107388B,
// already mapped to Rva006A16B0Empty. There are no calls.
// blocker=regalloc/initial-owner-register model=gpt-6
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

extern char Rva006A16B0Empty[];

struct Rva003C5270Blob
{
	void *m_00;
	unsigned short m_len;
	unsigned short m_pad;
	char m_data[ 1 ];
};

class Rva003C5820Item
{
public:
	Rva003C5270Blob *m_blob;
};

class Rva003C5820Key
{
public:
	Rva003C5270Blob *m_blob;
};

class Rva003C5820Owner
{
public:
	Rva003C5820Item **m_begin;
	Rva003C5820Item **m_end;
};

extern "C" int memcmp( const void *, const void *, unsigned int );
#pragma intrinsic( memcmp )

class Rva003C5270BorrowedView
{
public:
 Rva003C5270Blob *m_blob;
 int compare(const Rva003C5820Item &that) const
 {
  int thatLength = that.m_blob ? that.m_blob->m_len : 0;
  const char *thatText = that.m_blob ? that.m_blob->m_data : Rva006A16B0Empty;
  int thisLength = m_blob ? m_blob->m_len : 0;
  const char *thisText = m_blob ? m_blob->m_data : Rva006A16B0Empty;
  int length = thisLength < thatLength ? thisLength : thatLength;
  int difference = memcmp(thisText, thatText, length);
  if (difference != 0) return difference;
  return thisLength - thatLength;
 }
};
int __stdcall Rva003C5270Find(Rva003C5820Owner *owner,Rva003C5820Key *key)
{
 Rva003C5820Item **begin=owner->m_begin;
 unsigned int count=(unsigned int)(owner->m_end-owner->m_begin);
 unsigned int index=0;
 if(count>0)
 {
  Rva003C5270BorrowedView query={key->m_blob};
  Rva003C5820Item **cursor=begin;
  while(index<count)
  {
   if(query.compare(**cursor)==0) return index;
   ++index;
   ++cursor;
  }
 }
 return -1;
}
