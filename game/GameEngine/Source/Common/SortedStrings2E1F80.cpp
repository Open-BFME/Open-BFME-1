// cl: /DNDEBUG /MD /EHsc /Igame /D_STLP_USE_STATIC_LIB
// Retail 0x002E1F80 returns the string in a 12-byte keyed record and exposes
// its flag. No semantic class identity is claimed. Vector begins at +8.
// Retail passes an empty comparator by value (only its low byte is written).
// The lower-bound callee has no throwing operations; its throw() declaration
// reproduces the absence of an EH state store across that call.
// stlport
#include <vector>
#include "Libraries/Source/WWVegas/WWLib/ascii_string.h"
struct S4SortElem12 { int a,b,c; };
struct S4Cmp002E1690 {};
void Rva002E1F10(S4SortElem12 *,S4SortElem12 *,S4Cmp002E1690);
struct Gen002DFFD0Elem { int key; char pad[8]; };
struct Gen002DFFD0Less {};
Gen002DFFD0Elem *Gen002DFFD0(Gen002DFFD0Elem *,Gen002DFFD0Elem *,const int &,Gen002DFFD0Less,int *) throw();
struct StringEntry2E1F80 { int key; AsciiString value; bool flag; };
extern AsciiString emptyString2E1F80;
class SortedStrings2E1F80 {
 unsigned field00; bool sorted; char pad05[3];
 _STL::vector<StringEntry2E1F80> entries;
 bool empty() const { return entries.empty(); }
 void sort() { if (!sorted) Rva002E1F10((S4SortElem12 *)entries.begin(),(S4SortElem12 *)entries.end(),S4Cmp002E1690()); sorted=true; }
public:
 const AsciiString &find(int key,bool *flag);
};
const AsciiString &SortedStrings2E1F80::find(int key,bool *flag)
{
 *flag=false;
 if (empty()) return emptyString2E1F80;
 sort();
 StringEntry2E1F80 search;
 search.key=key;
 StringEntry2E1F80 *end=entries.end();
 StringEntry2E1F80 *begin=entries.begin();
 StringEntry2E1F80 *found=(StringEntry2E1F80 *)Gen002DFFD0((Gen002DFFD0Elem *)begin,(Gen002DFFD0Elem *)end,search.key,Gen002DFFD0Less(),0);
 if (found!=end && found->key==key) {
  *flag=found->flag;
  return found->value;
 }
 return emptyString2E1F80;
}
