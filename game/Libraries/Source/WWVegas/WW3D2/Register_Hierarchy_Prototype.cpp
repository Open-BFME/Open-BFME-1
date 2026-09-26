// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: BFME hierarchy prototype register, retail 0x00971910, 124 bytes.
// Unless a render object of that name already exists, build the 0x24-byte
// hierarchy prototype and hand it to the asset manager's prototype list.

class Rva00971670Proto
{
public:
	Rva00971670Proto(const char *name, int first, int second);

	unsigned char m_bfmePad[0x24];
};

bool __cdecl Render_Obj_Exists(const char *name);
void __cdecl Add_Prototype(void *prototype);

// ?Register_Hierarchy_Prototype@@YAXPBDHH@Z
void __cdecl Register_Hierarchy_Prototype(const char *name, int first, int second)
{
	if (name != 0 && !Render_Obj_Exists(name))
		Add_Prototype(new Rva00971670Proto(name, first, second));
}
