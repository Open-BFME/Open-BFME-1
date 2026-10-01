// Retail 0x00409E20: six 0x44-byte records; caller Drawable 0x00412530.
// Descriptive address-derived identity; class ownership remains unproved.
class DebugStream00409E20
{
public:
	virtual DebugStream00409E20 *Put_Unsigned(unsigned value);
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual DebugStream00409E20 *Put_String(const char *text);
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual DebugStream00409E20 *Finish(int report);
};

struct Rva00889690Obj
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual DebugStream00409E20 *Get_Stream(void *owner, void *context);
};

extern Rva00889690Obj *g_rva00889690;
extern void _bfme_debugRecordCallsite(int kind);
bool __cdecl _bfme_debugReportingEnabled(void);


struct EffectHandle00409E20 { char bytes00[8]; int field08; };
struct BuffEntry00409E20 {
 int field00; bool field04; char bytes05[7]; int field0c;
 char bytes10[8]; EffectHandle00409E20 *field18; char bytes1c[0x28];
 bool transition00409610(int type,int mode,void *arg,void *owner,int count);
};
struct BuffRules00409E20 { int entries[6]; int mode; };
extern BuffRules00409E20 Rules00409E20[];
struct BuffState00409E20 {
 int field00; void *field04; BuffEntry00409E20 entries[6];
 void apply(int type,void *arg,int count,const void *color,float extrusion);
};
void BuffState00409E20::apply(int type,void *arg,int count,const void *color,float extrusion) {
 if(type<6 && type>=1) {
  for(int i=0;i<6;++i) {
   int k=Rules00409E20[type].entries[i];
   if(!k) break;
   if(k<6 && k>=1) {
    BuffEntry00409E20 *e=&entries[k];
    if(e->field04) { switch(e->field0c) { case 1:
     if(e->field18) e->field18->field08=2;
     e->field04=false; break;
    } }
   }
  }
  switch(Rules00409E20[type].mode) {
  case 1: entries[type].transition00409610(type,1,arg,field04,count); break;
  case 2:
   if(_bfme_debugReportingEnabled()) {
    _bfme_debugRecordCallsite(1);
    g_rva00889690->Begin_Report();
    g_rva00889690->Get_Stream(0,0)->Put_String("GlowOutline buffs are no longer supported. They need to be removed from an INI file.")->Finish(2);
   }
   break;
  }
 }
}
