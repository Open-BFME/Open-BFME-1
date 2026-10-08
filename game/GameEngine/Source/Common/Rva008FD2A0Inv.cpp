// cl: /O2 /Ob0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8MeshRendererClass
{
public:
	void Invalidate(bool);
};

DX8MeshRendererClass *TheDX8MeshRenderer;

void rva008fd2a0()
{
	TheDX8MeshRenderer->Invalidate(false);
}
