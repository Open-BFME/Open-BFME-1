// ?bfmeDo1235@BfmeN1235@@QAEXPAX0@Z
// cl: /DNDEBUG /MD /EHsc
// Retail 008AE180, 303 bytes. Named exact callers establish the existing
// address-derived method. Layout matches BfmeConv1235.cpp; six callees retain
// their verified identities and thiscall contracts.
class Gen_008D2C80 { public: void bfmePush(); };
class BfmeThingDXH { public: void bfmeGoDXH(void *); };
class BfmeH1235 { public: void bfmeWalk1235(void *, void *); };
class BfmeA1210 { public: void bfmePop1210(); };
class AssetManagerImpl { public: void bfmeApplyXS(void *, void *); };
class Rva008A0F20Header { public: int isKind11() const; };
class BfmeQ1235 { public: int m_bfme00, m_bfme04; };
struct Rva008AE180Record { int m_at00, m_at04; char m_at08[16]; };
struct Rva008AE180Owner { char m_padding00[12]; Rva008AE180Record *m_at0C; };
class BfmeN1235
{
public:
 void bfmeDo1235(void *a, void *b);
 unsigned m_bfme00, m_bfme04;
 char m_bfmePad08[0x50-8];
 BfmeQ1235 *m_bfme50;
 char m_bfmePad54[4];
 BfmeN1235 *m_bfme58;
 __forceinline int kind008AE180(unsigned kind) const {
  return (m_bfme04 & 63) == kind && !((unsigned char)~(m_bfme04 >> 15) & 1);
 }
};
void BfmeN1235::bfmeDo1235(void *a, void *b)
{
 if (kind008AE180(0x13)) return;
 Rva008AE180Owner *owner = (Rva008AE180Owner *)m_bfme50;
 ((Gen_008D2C80 *)a)->bfmePush();
 ((BfmeThingDXH *)a)->bfmeGoDXH((char *)this+0x10);
 if (kind008AE180(13)) {
  ((BfmeH1235 *)((char *)m_bfme50+0x24))->bfmeWalk1235(a,b);
  ((BfmeA1210 *)a)->bfmePop1210(); return;
 }
 if (kind008AE180(18)) {
  ((BfmeH1235 *)((char *)m_bfme50+0x24))->bfmeWalk1235(a,b);
  ((BfmeA1210 *)a)->bfmePop1210(); return;
 }
 if (kind008AE180(14)) {
  ((BfmeH1235 *)((char *)m_bfme50+0x20))->bfmeWalk1235(a,b);
  ((BfmeA1210 *)a)->bfmePop1210(); return;
 }
 if (kind008AE180(15)) {
  ((AssetManagerImpl *)a)->bfmeApplyXS(b,(char *)m_bfme50+0x50);
  ((BfmeA1210 *)a)->bfmePop1210(); return;
 }
 if (!(unsigned char)((Rva008A0F20Header *)this)->isKind11()) {
  Rva008AE180Record *record = owner->m_at0C;
  switch (record->m_at00) {
  case 10:
   ((AssetManagerImpl *)a)->bfmeApplyXS(b,record->m_at08);
   ((BfmeA1210 *)a)->bfmePop1210(); return;
  case 1:
   ((AssetManagerImpl *)a)->bfmeApplyXS(b,record->m_at08);
  }
 }
 ((BfmeA1210 *)a)->bfmePop1210();
}
