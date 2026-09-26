// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Standalone BFME layout shim for VertexMaterialClass::Get_Shininess.
// Retail body 0x00921100 is exactly 7 bytes:
//   mov eax,[ecx+8]; fld dword ptr [eax+40h]; ret
struct D3DMATERIAL8_SHIM
{
	unsigned char Reserved[0x40];
	float Power;
};

class VertexMaterialClass
{
	unsigned char BaseAndFlags[8];
	D3DMATERIAL8_SHIM *Material;
public:
	__declspec(noinline) float Get_Shininess(void) const;
};

// ?Get_Shininess@VertexMaterialClass@@QBEMXZ
float VertexMaterialClass::Get_Shininess(void) const
{
	return Material->Power;
}
