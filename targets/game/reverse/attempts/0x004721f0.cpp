// ?d_004721f0@@YAXXZ
// partial score=0.699659 date=2026-09-28
// cl: /O2 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "unicode_string.h"
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }

struct Point004721F0 { int x, y; };
class Text004721F0 {
public:
 virtual void slot00();
 virtual void slot04();
 virtual UnicodeString getText();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void colors(unsigned, unsigned);
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void draw(int,int,int,int);
 virtual void size(int*,int*);
};
class Anim2D { public: void setCurrentFrame(unsigned short); };
struct Template004721F0 { char field00[16]; unsigned short field10; };
class Rva005BA9E0Anim2D { public:
 void draw(int,int,int,int);
 char field00[12]; Template004721F0* field0c; char field10[12]; float field1c;
};
class TextEffect004721F0 { public:
 void draw(Text004721F0*, const Point004721F0*, unsigned);
 char field00[8]; int field08, field0c, field10, field14;
 unsigned field18; Rva005BA9E0Anim2D* field1c;
 char field20[8]; unsigned field28; char field2c[8];
 unsigned field34[3], field40[3]; int field4c, field50;
};
// RVA 004721F0: three timed text/animation phases; semantic owner unknown.
void TextEffect004721F0::draw(Text004721F0* text, const Point004721F0* pos, unsigned frame) {
 int w, h;
 text->size(&w, &h);
 UnicodeString s = text->getText();
 int y = pos->y - (field50-h)/2;
 int x = pos->x;
 int width = 0;
 text->size(&width, 0);
 int bottom = y + field50;
 int right = x + width;
 if(field08 > x) field08=x;
 if(field10 < right) field10=right;
 if(field0c > y) field0c=y;
 if(field14 < bottom) field14=bottom;
 for(int i=0;i<3;++i) {
  unsigned start=field34[i], end=field40[i];
  if(frame>=start && frame<=end) {
   float progress=float(frame-start)/float(end-start);
   switch(i) {
   case 0: {
    unsigned frames=field1c->field0c->field10;
    if(frames) {
     ((Anim2D*)field1c)->setCurrentFrame(((frame-start)/4)%frames);
     field1c->field1c=float(field18>>24)*(1.0f/255.0f);
     field1c->draw(x-width/2,y,width*2,field50);
     field1c->draw(x-width/2,y,width*2,field50);
    }
    break;
   }
   case 1: {
    unsigned alpha=(unsigned)(int)((1.0f<progress ? 1.0f:progress)*255.0f)<<24;
    text->colors((field28&0xffffff)|alpha,alpha);
    text->draw(pos->x,pos->y,1,1);
    break;
   }
   case 2:
    text->colors(field28|field18,field18);
    text->draw(pos->x,pos->y,1,1);
    break;
   }
  }
 }
}
