// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: BFME mesh prototype register, retail 0x00971060, 124 bytes.
// Unless a render object of that name already exists, build the 0x24-byte
// mesh prototype and hand it to the asset manager's prototype list.

class Rva00970EC0Proto
{
public:
	Rva00970EC0Proto(const char *name, int first, int second);

	unsigned char m_bfmePad[0x24];
};

bool __cdecl Render_Obj_Exists(const char *name);
void __cdecl Add_Prototype(void *prototype);

// ?Register_Mesh_Prototype@@YAXPBDHH@Z
void __cdecl Register_Mesh_Prototype(const char *name, int first, int second)
{
	if (name != 0 && !Render_Obj_Exists(name))
		Add_Prototype(new Rva00970EC0Proto(name, first, second));
}
