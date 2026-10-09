// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"

class Display { public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1c(); virtual void slot20();
 virtual void slot24(); virtual void slot28(); virtual unsigned getWidth();
};
extern Display* TheDisplay;
// Retail VA 010F7540 contains float 0.75 (0000403f); distinct constant pool.
static const float ElvenTextScale010F7540[] = { 0.75f };
class GameFont;
class FontLibrary;
// Retail ILT 0xABC3 -> matched FontLibraryBFMERetail::getFont at 0x004772D0.
class FontLibraryBFMERetail { public: GameFont* getFont(AsciiString*,float,unsigned char); };
extern FontLibrary* TheFontLibrary;
struct ImageSize00471900 { int x,y; };
class Image { public: char field00[0x24]; ImageSize00471900 m_imageSize; };
class ImageCollection { public: const Image* findImageByName(const AsciiString&); };
extern ImageCollection* TheMappedImageCollection;
class Anim2DTemplate;
class Anim2DCollection { public: Anim2DTemplate* findTemplate(const AsciiString&); };
extern Anim2DCollection* TheAnim2DCollection;
class Anim2D { public:
 Anim2D(Anim2DTemplate*,Anim2DCollection*);
 char field00[0x34];
};
class ElvenTextAssets00471900 { public:
 void initialize();
 void* field00; GameFont* field04; char field08[0x14];
 std::vector<const Image*> field1c;
 std::vector<Anim2D*> field28;
 Anim2D* field34; float field38; AsciiString field3c; char field40[8];
 unsigned field48; int field4c,field50,field54,field58,field5c;
 int field60,field64,field68,field6c,field70,field74,field78;
};
// Address-qualified owner; retail strings prove elven text resource initialization.
// Image+0x24 is the witnessed m_imageSize pair. Anim2D allocation is 0x34
// bytes and calls the independently landed Anim2D constructor at RVA 005BA4D0.
// The three animation-vector overflow calls encode ILT 00001852 -> 00471700.
// That body has thiscall ret 20, 4-byte elements, begin/end/capacity at 0/4/8,
// max(size,count) growth, prefix/suffix memmoves, repeated pointer insertion,
// and the STLport 128-byte small-allocation split. The inserted values come
// directly from the Anim2D constructor, establishing the pointer element type.
void ElvenTextAssets00471900::initialize() {
 float scale=float(TheDisplay->getWidth())/800.0f;
 scale *= ElvenTextScale010F7540[0];
 if(scale!=field38) { field04=0; field38=scale; }
 if(!field04) field04=((FontLibraryBFMERetail*)TheFontLibrary)->getFont(&field3c,float(field48)*scale,0);
 if(!field34) {
  field1c.push_back(TheMappedImageCollection->findImageByName(AsciiString("elv_text_A")));
  field1c.push_back(TheMappedImageCollection->findImageByName(AsciiString("elv_text_B")));
  field1c.push_back(TheMappedImageCollection->findImageByName(AsciiString("elv_text_C")));
  field28.push_back(new Anim2D(TheAnim2DCollection->findTemplate(AsciiString("TextElvenFlameA")),TheAnim2DCollection));
  field28.push_back(new Anim2D(TheAnim2DCollection->findTemplate(AsciiString("TextElvenFlameB")),TheAnim2DCollection));
  field28.push_back(new Anim2D(TheAnim2DCollection->findTemplate(AsciiString("TextElvenFlameC")),TheAnim2DCollection));
  field34=new Anim2D(TheAnim2DCollection->findTemplate(AsciiString("TextElvenClouds")),TheAnim2DCollection);
  field68=-1; field60=-1; field5c=0; field70=15; field58=1;
  field6c=15; field50=15; field64=75; field54=76; field4c=15;
 }
 const Image* image=field1c[0];
 field74=int(image->m_imageSize.x*scale*0.5f);
 field78=int(image->m_imageSize.y*scale);
}
