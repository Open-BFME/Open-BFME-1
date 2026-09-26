// cl: /DNDEBUG /MD /EHsc
//
// WW3D FontCharsClass scalar-deleting destructor.  The matched constructor
// at 0x00940610 installs vtable 0x0113CE8C; after RefCountClass::Delete_This,
// its second slot is the deleting wrapper at 0x00940770.

class FontCharsClass
{
public:
	virtual ~FontCharsClass();
};

__declspec(noinline) FontCharsClass::~FontCharsClass()
{
}

void Force_FontCharsClass_Deleting_Destructor(FontCharsClass *font)
{
	delete font;
}
