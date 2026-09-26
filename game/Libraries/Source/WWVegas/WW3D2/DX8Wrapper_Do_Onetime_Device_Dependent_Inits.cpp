// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: DX8Wrapper's one-time device-dependent initialisation at
// 0x0090ADC0 (157 B; Zero Hour's Do_Onetime_Device_Dependent_Inits with
// BFME's heap-allocated mesh renderer): the caps computation on the device
// (0x00906E70 with the pointer at VA 0x01340510) the texture filter table
// from the mode at VA 0x012D6D98 then TheDX8MeshRenderer = new
// DX8MeshRendererClass (EH state around the allocation) followed by its Init
// and the empty member at 0x00944C40 the material initialisers and the two
// unlabelled inits at 0x00917280 / 0x0090F760 the routine at 0x0091DA30 and
// the default global render states.  Address-derived names where identity is
// not recovered.

enum TextureFilterMode
{
	TEXTURE_FILTER_BILINEAR = 0
};

class TextureFilterClass
{
public:
	static void _Init_Filters( TextureFilterMode mode );
};

class DX8MeshRendererClass
{
public:
	DX8MeshRendererClass();
	void Init( void );
	void Rva00944C40Empty( void );

private:
	char m_body[ 0x4C ];
};

class VertexMaterialClass
{
public:
	static void Init( void );
};

class DX8Wrapper
{
public:
	static void Do_Onetime_Device_Dependent_Inits( void );

protected:
	static void Rva00906E70ComputeCaps( void *device );
	static void Set_Default_Global_Render_States( void );
};

void bfmeInitMaterialXP( void );
void Rva00917280Init( void );
void Rva0090F760Init( void );
void Rva0091DA30Init( void );

extern void *Rva01340510Device;
extern TextureFilterMode Rva012D6D98FilterMode;
extern DX8MeshRendererClass *TheDX8MeshRenderer;

// ?Do_Onetime_Device_Dependent_Inits@DX8Wrapper@@SAXXZ
void DX8Wrapper::Do_Onetime_Device_Dependent_Inits( void )
{
	Rva00906E70ComputeCaps( Rva01340510Device );
	TextureFilterClass::_Init_Filters( Rva012D6D98FilterMode );
	TheDX8MeshRenderer = new DX8MeshRendererClass;
	TheDX8MeshRenderer->Init();
	TheDX8MeshRenderer->Rva00944C40Empty();
	bfmeInitMaterialXP();
	VertexMaterialClass::Init();
	Rva00917280Init();
	Rva0090F760Init();
	Rva0091DA30Init();
	Set_Default_Global_Render_States();
}
