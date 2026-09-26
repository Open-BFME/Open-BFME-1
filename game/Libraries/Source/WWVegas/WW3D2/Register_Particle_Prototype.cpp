// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: BFME particle prototype register, retail 0x00971440, 124 bytes.
// Unless a render object of that name already exists, build the 0x24-byte
// particle prototype and hand it to the asset manager's prototype list.

class Rva009712A0Proto
{
public:
	Rva009712A0Proto(const char *name, int first, int second);

	unsigned char m_bfmePad[0x24];
};

bool __cdecl Render_Obj_Exists(const char *name);
void __cdecl Add_Prototype(void *prototype);

// ?Register_Particle_Prototype@@YAXPBDHH@Z
void __cdecl Register_Particle_Prototype(const char *name, int first, int second)
{
	if (name != 0 && !Render_Obj_Exists(name))
		Add_Prototype(new Rva009712A0Proto(name, first, second));
}
