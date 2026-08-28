// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8MeshRendererClass
{
public:
	void Invalidate(bool);
};

DX8MeshRendererClass *g_rva008fd2a0;

void rva008fd2a0()
{
	g_rva008fd2a0->Invalidate(false);
}
