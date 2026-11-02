// cl: /DNDEBUG /MD /EHsc
//
// WW3D FontCharsClass scalar-deleting destructor.  The matched constructor
// at 0x00940610 installs vtable 0x0113CE8C; after RefCountClass::Delete_This,
// its second slot is the deleting wrapper at 0x00940770.

class FontCharsClass
{
	friend void forceFontCharsClassDeletingDestructorCopy(const FontCharsClass &that);
public:
	virtual ~FontCharsClass();
};


void Force_FontCharsClass_Deleting_Destructor(FontCharsClass *font)
{
	delete font;
}

// ~FontCharsClass is matched out of line (FontCharsClassDestructorBFME.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceFontCharsClassDeletingDestructorCopy(const FontCharsClass &that)
{
	FontCharsClass value(that);
}
