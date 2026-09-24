// ?Rva00941C60_Method@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z
// partial score=0.076 date=2026-09-24
// ?Rva00941C60_Method@Render2DSentenceClass@@AAE?AVVector2@@PBGPAH1_N@Z
// The matched caller at 0x00942430 passes this object, text, two hotkey pointers, and the flag.
// That caller proves the ABI, but it does not prove a semantic method name.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

typedef unsigned short WCHAR;
typedef unsigned short uint16;
#define NULL 0

void __cdecl operator delete[](void *) throw();
void __cdecl Gen0082E5F0(void *, unsigned int);
extern "C" __declspec(dllimport) unsigned int __cdecl bfmeLenVGI(const unsigned short *);

class Vector2 { public: float X, Y; void Set(float x, float y) { X=x; Y=y; } };
struct Vector2i { int I, J; void Set(int i, int j) { I=i; J=j; } };
struct FontCharsClassCharDataStruct { unsigned short Value; short Width; short ExtraSpacing; };

class FontCharsClass
{
public:
    virtual ~FontCharsClass();
    unsigned int references;
    int Get_Char_Height() const { return char_height; }
    const FontCharsClassCharDataStruct *Get_Char_Data(unsigned short);
    int Get_Char_Spacing(unsigned short ch) {
        const FontCharsClassCharDataStruct *data = Get_Char_Data(ch);
        return data ? data->Width + data->ExtraSpacing : 0;
    }
    int Get_Extra_Overlap() const { return pixel_overlap; }
    void Blit_Char(unsigned short, unsigned int *, int, int, int);
    FontCharsClass *AlternateUnicodeFont;
private:
    char fields0c[0x20];
    int char_height;
    char fields30[0x08];
    int pixel_overlap;
    char fields3c[4];
};

class Rva0093C4A0Target
{
public:
    bool Check(const unsigned short *, unsigned short *, int);
private:
    char fields00[0x48];
    void *font;
};

class Rva00941700Owner
{
public:
    void Rva00941700_Method(FontCharsClass *, const unsigned short *, unsigned short *, bool);
};

namespace _STL
{
template <class T> class allocator {};
template <class T, class A> class vector
{
public:
    vector() : _M_start(0), _M_finish(0), _M_end_of_storage(0) {}
    ~vector()
    {
        if (_M_start != 0) {
            unsigned int bytes = (unsigned int)((char *)_M_end_of_storage - (char *)_M_start);
            if (bytes > 0x80)
                ::operator delete[](_M_start);
            else
                Gen0082E5F0(_M_start, bytes);
        }
    }
    T *begin() { return _M_start; }
    unsigned int size() const { return (unsigned int)(_M_finish - _M_start); }
    void resize(unsigned int, T);
private:
    T *_M_start;
    T *_M_finish;
    T *_M_end_of_storage;
};
}

struct SentenceData
{
    void *surface;
    float screen_left, screen_top, screen_right, screen_bottom;
    float uv_left, uv_top, uv_right, uv_bottom;
};

template <class T> class DynamicVector
{
public:
    virtual void dummy();
    T *Vector;
    int VectorMax;
    bool IsValid;
    bool IsAllocated;
    char pad[2];
    int ActiveCount;
    int GrowthStep;
};
struct Rect { float left, top, right, bottom; };
class SurfaceClass { public: unsigned int *Lock(int *, bool = false); };

class Render2DSentenceClass
{
public:
    virtual void reset();
private:
    Vector2 Rva00941C60_Method(const unsigned short *, int *, int *, bool);
public:
    void Record_Sentence_Chunk();
    void Rva0093F980_Method(FontCharsClass *);
    DynamicVector<SentenceData> sentence_data;
    DynamicVector<char> pending_surfaces;
    DynamicVector<char> renderers;
    FontCharsClass *Font;
    Vector2 BaseLocation, Location, Cursor;
    Vector2i TextureOffset;
    int TextureStartX, CurrTextureSize, TextureSizeHint;
    SurfaceClass *CurSurface;
    bool MonoSpaced;
    float WrapWidth;
    bool Centered;
    Rect ClipRect, DrawExtents;
    bool IsClippedEnabled, ParseHotKey, useHardWordWrap;
    char pad[1];
    unsigned int *LockedPtr;
    int LockedStride;
};

inline float max(float left, float right) { return left > right ? left : right; }
#define TEXTURE_OFFSET 2
Vector2 Render2DSentenceClass::Rva00941C60_Method (const WCHAR *text, int *hkX, int *hkY, bool justCalcExtents)
{
		int hotKeyPosX = 0;
	int hotKeyPosY = 0;
	bool calcHotKeyX = false;
	bool dontBlit = false;
	float maxX = 0;

	int length = (int)bfmeLenVGI(text);
	_STL::vector<unsigned short, _STL::allocator<unsigned short> > glyphVector;
	glyphVector.resize(length + 1, 0);
	unsigned short *glyphs = glyphVector.begin();
	FontCharsClass *drawFont = Font;
	if (!reinterpret_cast<Rva0093C4A0Target *>(drawFont)->Check(text, glyphs, length)) {
		if (drawFont->AlternateUnicodeFont != NULL) {
			reinterpret_cast<Rva0093C4A0Target *>(drawFont->AlternateUnicodeFont)->Check(text, glyphs, length);
			drawFont = drawFont->AlternateUnicodeFont;
		}
	}
	glyphs[length] = 0xffff;
	reinterpret_cast<Rva00941700Owner *>(this)->Rva00941700_Method(drawFont, text, glyphs, justCalcExtents);




	TextureOffset.Set (TEXTURE_OFFSET, 0);
	TextureStartX = TEXTURE_OFFSET;	

	float char_height = drawFont->Get_Char_Height ();

	//
	//	Loop over all the characters in the string
	//
	const WCHAR *glyphText = glyphs;
	while (text != NULL) {
		WCHAR ch = *text++;
		WCHAR glyph = *glyphText++;
		dontBlit = false;
		//
		//	Determine how much horizontal space this character requires
		//
		if(ParseHotKey && (ch == L'&') && (*text != 0) && (*text > L' ') && (*text != L'\n'))
		{
				hotKeyPosY = Cursor.Y;
			if (calcHotKeyX)
				hotKeyPosX = 0;
			else
				hotKeyPosX = Cursor.X + TextureOffset.I -TextureStartX;//TextureOffset.I;

			ch = *text++;
			glyph = *glyphText++;
			dontBlit = true;
		}
		float char_spacing = drawFont->Get_Char_Spacing(glyph);

		bool exceeded_texture_width	= ((TextureOffset.I + char_spacing) >= CurrTextureSize);
		bool encountered_break_char	= (ch == L' ' || ch == L'\n' || ch == 0);
		bool wordBiggerThenLine = ((useHardWordWrap) && ( WrapWidth != 0 ) &&((Cursor.X + TextureOffset.I -TextureStartX + char_spacing) >= WrapWidth));
		//
		//	Do we need to record this portion of the sentence to its own chunk?
		//
		if (exceeded_texture_width || encountered_break_char|| wordBiggerThenLine) {
			if (!justCalcExtents)
			{
				Rva0093F980_Method(drawFont);
			}

			//
			//	Adjust the positions
			//
			Cursor.X			+= (TextureOffset.I - TextureStartX);
			maxX = max(maxX, Cursor.X);
			TextureStartX	= TextureOffset.I;

			//
			//	Adjust the output coordinates
			//
			if (ch == L' ') {
				//Cursor.X += char_spacing;
				//maxX = max(maxX, Cursor.X);

				//
				// Check to see if we need to wrap on this word-break
				//
				if (WrapWidth > 0) {
					
					//
					//	Find the length of the next word
					//
					const WCHAR *word	= text;
					const WCHAR *wordGlyph = glyphText;
					float word_width	= char_spacing;
					while ((*word != 0) && (*word > L' ')) {
						if(ParseHotKey && (*word == L'&') && (*word+1 != 0) && (*word+1 > L' ') && (*word+1 != L'\n')) {
							word++;
							wordGlyph++;
						}
						word_width += drawFont->Get_Char_Spacing (*wordGlyph++);
					}

					//
					//	Should we wrap the next word?
					//
					if ((Cursor.X + word_width) >= WrapWidth) {
						Cursor.X = 0;
						Cursor.Y += char_height;
						calcHotKeyX = true;
					}
				}

			} else if (ch == L'\n') {
				Cursor.X = 0;
				Cursor.Y += char_height;
			} else if (ch == 0) {
				break;
			} else if (wordBiggerThenLine){ // we've entered this loop because we're greater then the wordwrap so we need to force a wordwrap
				Cursor.X = 0;
				Cursor.Y += char_height;
			}

			
			//
			//	Did the text extend past the edge of the texture?
			//
			if (exceeded_texture_width) {
				TextureStartX		= TEXTURE_OFFSET;
				TextureOffset.I	= TextureStartX;
				TextureOffset.J	+= char_height;

				//
				//	Did the text extent completely off the texture?
				//
				if ((TextureOffset.J + char_height) >= CurrTextureSize) {
					reinterpret_cast<Rva00941700Owner *>(this)->Rva00941700_Method(drawFont, text, glyphs, justCalcExtents);
				}
			}
		}
		
		if (ch != L'\n' ) {

			//
			//	Ensure the surface is locked	
			//
			if (!justCalcExtents)
			{
				if (LockedPtr == NULL) {
					LockedPtr = (unsigned int *)CurSurface->Lock (&LockedStride);

				}
			}



			//
			//	Blit the character to the surface
			//
			if (!justCalcExtents && !dontBlit )
			{
				drawFont->Blit_Char (ch, LockedPtr, LockedStride, TextureOffset.I, TextureOffset.J);
			}
			TextureOffset.I += char_spacing;
		} 
	}

	Vector2 extent;
	extent.X = maxX + drawFont->Get_Extra_Overlap();
	extent.Y = Cursor.Y + char_height;

	
	if(hkX)						
		*hkX = hotKeyPosX;
	if(hkX)
		*hkY = hotKeyPosY;

	return extent;
}
