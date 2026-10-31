// stlport
// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00940D40, 1355 bytes, RET 4: the BFME Thai glyph loader that
// rasterizes one glyph index through the shared GDI DIB in 64x64 tiles, widens
// the cell by the ABC widths and caches every record (the empty 0xffff one
// too) in the glyph map. Ported from the BFME 2 donor
// Code/Libraries/Source/WWVegas/WW3D2/FontCharsClassStoreThaiGdiGlyph.cpp
// (open-bfme-2 b5a7b8290); the method keeps BFME 1's pinned loadCharacterData
// name. BFME 1 facts from the retail body: the FontCharsClass offsets shared
// with Store_GDI_Char 0x0093F440, GetTextExtentPointI/GetCharABCWidthsI, the
// glyph map at +0x450 whose operator[] is the 0x00940B40 instantiation
// (comparator Gen_lt_00940b40), Update_Current_Buffer 0x0093DFB0 and the sole
// caller FontCharsClass::Get_Char_Data 0x00941290.
#include <windows.h>
#include <map>
#include <string.h>

struct ABC { int abcA; unsigned int abcB; int abcC; };
extern "C" __declspec(dllimport) int __stdcall GetTextExtentPointI(HDC, const unsigned short *, int, SIZE *);
extern "C" __declspec(dllimport) int __stdcall GetCharABCWidthsI(HDC, unsigned int, unsigned int, const unsigned short *, ABC *);

struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	unsigned short Width;
	short Bearing;
	unsigned short unused;
	unsigned short *Buffer;
};

class FontCharsClassGdiState
{
public:
	int refs;
	HBITMAP oldBitmap, bitmap;
	unsigned char *bits;
	HDC dc;
};
extern FontCharsClassGdiState *g_fontCharsGdiState0134AEAC;

class FontGlyphDCSelection
{
	HDC dc;
	HGDIOBJ old;

public:
	FontGlyphDCSelection(HDC dc_, HFONT font) : dc(dc_), old(::SelectObject(dc_, font)) {}
	~FontGlyphDCSelection() { ::SelectObject(dc, old); }
};

class FontCharsBuffer
{
public:
	unsigned short *Buffer;
};

template <class T> class Rva00940D40Vector
{
public:
	int vptr;
	T *items;
	int capacity;
	bool valid, allocated;
	unsigned short padding;
	int activeCount;
	int growth;
	T &operator[](int i) { return items[i]; }
	int Count() const { return activeCount; }
};

// The glyph map's subscript is the shared out-of-line instantiation 0x00940B40.
struct Gen_lt_00940b40 : public _STL::less<unsigned short> {};
typedef _STL::map<unsigned short, int, Gen_lt_00940b40> Rva00940D40GlyphMap;
namespace _STL {
template <> Rva00940D40GlyphMap::mapped_type &Rva00940D40GlyphMap::operator[](const key_type &);
}

class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *loadCharacterData(unsigned short glyph);

private:
	void Update_Current_Buffer(int width);

	void *unused00, *unused04;
	FontCharsClass *alternate;
	int unused0c;
	Rva00940D40Vector<FontCharsBuffer *> BufferList;
	int CurrPixelOffset, CharHeight, ExtraHeight;
	int unknown34, overlap, unknown3c;
	int Scale;
	int unknown44;
	HFONT font;
	const FontCharsClassCharDataStruct *directChars[256];
	const FontCharsClassCharDataStruct **pages;
	Rva00940D40GlyphMap glyphs;
	unsigned short first, last;
};

typedef char Rva00940D40Layout[(sizeof(FontCharsClass) == 0x460) ? 1 : -1];

const FontCharsClassCharDataStruct *FontCharsClass::loadCharacterData(unsigned short glyph)
{
 if(glyph==0xffff) {
  FontCharsClassCharDataStruct *data=new FontCharsClassCharDataStruct;
  data->Value=glyph;data->Width=0;data->Bearing=0;data->Buffer=0;
  glyphs[glyph]=reinterpret_cast<int>(data);
  return data;
 }
 FontGlyphDCSelection selection(g_fontCharsGdiState0134AEAC->dc,font);
 int area=Scale*Scale;
 int halfArea=area>>1;
 int tileX=64/Scale;
 int tileY=64/Scale;
 SIZE tile_size={Scale*tileX,Scale*tileY};
 SIZE charSize;
 if(!::GetTextExtentPointI(g_fontCharsGdiState0134AEAC->dc,&glyph,1,&charSize))
  charSize.cx=charSize.cy=1;
 ABC abc;
 int origin=0;
 if(!::GetCharABCWidthsI(g_fontCharsGdiState0134AEAC->dc,glyph,1,0,&abc)) {
  abc.abcA=0;abc.abcB=1;abc.abcC=0;
 } else {
  unsigned int width=abc.abcB;
  if(abc.abcC>0) width+=abc.abcC;
  if(abc.abcA>0) width+=abc.abcA;
  else origin=-abc.abcA;
  charSize.cx=width;
 }
 SIZE cell_size;
 cell_size.cx=(Scale+charSize.cx-1)/Scale;
 cell_size.cy=(Scale+charSize.cy-1)/Scale;
 // Get a pointer to the surface that this character should use
 Update_Current_Buffer(cell_size.cx);
 unsigned short *pixels=BufferList[BufferList.Count()-1]->Buffer+CurrPixelOffset;
 int top=ExtraHeight/2;
 int bottom=ExtraHeight-top;
 unsigned short *start=pixels;
 pixels+=top*cell_size.cx;
 memset(start,0,top*cell_size.cx*2);
 memset(pixels+cell_size.cx*cell_size.cy,0,bottom*cell_size.cx*2);
 SIZE tile_count;
 tile_count.cx=(cell_size.cx+tileX-1)/tileX;
 tile_count.cy=(cell_size.cy+tileY-1)/tileY;
 // Copy the BMP contents to the buffer
 POINT tile_pos;
 for(tile_pos.y=0;tile_pos.y<tile_count.cy;++tile_pos.y) {
  for(tile_pos.x=0;tile_pos.x<tile_count.cx;++tile_pos.x) {
   // Draw the character into the memory DC
   RECT rect={0,0,tile_size.cx,tile_size.cy};
   POINT tile_origin;
   tile_origin.x=tile_size.cx*tile_pos.x;
   tile_origin.y=tile_size.cy*tile_pos.y;
   ::ExtTextOutW(g_fontCharsGdiState0134AEAC->dc,origin-tile_origin.x,-tile_origin.y,0x12,&rect,&glyph,1,0);
   POINT cell_start;
   cell_start.x=tileX*tile_pos.x;
   cell_start.y=tileY*tile_pos.y;
   POINT cell_end;
   cell_end.x=cell_start.x+tileX;
   if(cell_end.x>cell_size.cx) cell_end.x=cell_size.cx;
   cell_end.y=cell_start.y+tileY;
   if(cell_end.y>cell_size.cy) cell_end.y=cell_size.cy;
   for(int y=cell_start.y;y<cell_end.y;++y) {
    unsigned short *dest=pixels+y*cell_size.cx+cell_start.x;
    int y0=Scale*y;
    int y1=y0+Scale;
    if(y1>charSize.cy) y1=charSize.cy;
    for(int x=cell_start.x;x<cell_end.x;++x) {
     unsigned int intensity=0;
     int x0=Scale*x;
     int x1=x0+Scale;
     if(x1>charSize.cx) x1=charSize.cx;
     for(int row=y0;row<y1;++row) {
      // Compute the indices into the BMP and surface
      int index=(row-tile_origin.y)*192+(x0-tile_origin.x)*3;
      // Loop over each column
      for(int col=x0;col<x1;++col) {
       // Get the pixel color at this location
       unsigned char sample=g_fontCharsGdiState0134AEAC->bits[index];
       index+=3;
       intensity+=(sample>>4)&15;
      }
     }
     // Convert the pixel intensity from 8bit to 4bit and store it in our buffer
     unsigned short alpha=(intensity+halfArea)/area;
     *dest++=0xfff|(alpha<<12);
    }
   }
  }
 }
 // Save information about this character in our list
 FontCharsClassCharDataStruct *data=new FontCharsClassCharDataStruct;
 data->Value=glyph;
 data->Width=cell_size.cx;
 data->Bearing=(1-Scale-origin)/Scale;
 data->Buffer=BufferList[BufferList.Count()-1]->Buffer+CurrPixelOffset;
 glyphs[glyph]=reinterpret_cast<int>(data);
 // Advance the character position
 CurrPixelOffset+=CharHeight*cell_size.cx;
 return data;
}
