// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: BFME animation prototype register, retail 0x0090C000, 124 bytes.
// Unless a render object of that name already exists, build the 0x24-byte
// animation prototype and hand it to the asset manager's prototype list.

class Rva0090BD60Proto
{
public:
	Rva0090BD60Proto(const char *name, int first, int second);

	unsigned char m_bfmePad[0x24];
};

bool __cdecl Render_Obj_Exists(const char *name);
void __cdecl Add_Prototype(void *prototype);

// ?Register_Animation_Prototype@@YAXPBDHH@Z
void __cdecl Register_Animation_Prototype(const char *name, int first, int second)
{
	if (name != 0 && !Render_Obj_Exists(name))
		Add_Prototype(new Rva0090BD60Proto(name, first, second));
}
