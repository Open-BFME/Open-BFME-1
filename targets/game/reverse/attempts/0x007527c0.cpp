// ?method@Rva007527C0@@QBE_NABU1@@Z
// partial score=0.7155 date=2026-10-03
// Retail 0x007527C0..0x007529A4, ret 4, followed by INT3.
// Address-derived comparator; no original owner/name is claimed.
// Q4Sort00751F50Record declaration follows its existing matched 128-byte TU.
// The barrier is a measured source-shaping aid that preserves retail reloads;
// it does not establish original source spelling. This candidate is NOT exact.
// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Drawable;
class Rva00765AC0;
struct Q4Sort00751F50Record {
 char m_pad00[8]; Drawable *m_drawable; char m_pad0c[8]; Rva00765AC0 *m_state;
 bool compare(const Q4Sort00751F50Record &, int *, int *) const;
};
struct Rva007527C0Sub {
 void *m_00; float m_04; char m_08[8]; int m_10; int m_14; char m_18;
};
struct Rva007527C0Data {
 char m_00[8]; struct Rva007527C0Float *m_08; char m_0c[8]; Rva00765AC0 *m_14;
 char m_18[0xc4]; Rva007527C0Sub m_dc[2];
};
struct Rva007527C0Float { char m_00[0x1f8]; float m_1f8; };
extern const float BfmeZeroRange;
struct Rva007527C0 {
 void *m_00; Rva007527C0Data *m_04; int m_08;
 bool method(const Rva007527C0 &) const;
};
bool Rva007527C0::method(const Rva007527C0 &o) const {
 if(m_00 != o.m_00) return o.m_00 < m_00;
 if(!m_00) return m_04 < o.m_04;
 if(m_08 != o.m_08) return m_08 < o.m_08;
 if(m_04->m_08->m_1f8 != o.m_04->m_08->m_1f8) return m_04->m_08->m_1f8 < o.m_04->m_08->m_1f8;
 if(o.m_04->m_14 != m_04->m_14) return m_04->m_14 < o.m_04->m_14;
 int a,b;
 if(((Q4Sort00751F50Record *)m_04)->compare(*(Q4Sort00751F50Record *)o.m_04,&a,&b)) {
  if(a!=b) return a<b;
  return m_04 < o.m_04;
 }
 for(int i=0;i<=1;++i) {
  const Rva007527C0Sub &left=m_04->m_dc[i];
  const Rva007527C0Sub &right=o.m_04->m_dc[i];
  if(left.m_00 != right.m_00) return left.m_00 < right.m_00;
  if(left.m_00) {
   if(left.m_14 != right.m_14) return left.m_14 < right.m_14;
   if(left.m_10 != right.m_10) return left.m_10 < right.m_10;
   if(left.m_18 != right.m_18) return left.m_18 ? true : false;
  }
 }
 _ReadWriteBarrier();
 float x=(m_04->m_dc[1].m_00 ? m_04->m_dc[1].m_04 : BfmeZeroRange)+m_04->m_dc[0].m_04;
 float y=(o.m_04->m_dc[1].m_00 ? o.m_04->m_dc[1].m_04 : BfmeZeroRange)+o.m_04->m_dc[0].m_04;
 if(x!=y) return x<y;
 return m_04<o.m_04;
}
