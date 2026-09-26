// cl: /O1
// Both absolute stores are present in the archive body: changing the allocator
// invalidates the associated cached state before publishing the new pointer.

namespace D3DXCore
{
class CAlloc;
}

namespace D3DXShader {
extern int D3DXData01351400;
extern D3DXCore::CAlloc * D3DXData01351404;
extern int D3DXData01351408;
extern D3DXCore::CAlloc * D3DXData0135140C;

class CInstruction
{
public:
	static void __stdcall SetAlloc( D3DXCore::CAlloc * allocator );
};

class CArgument
{
public:
	static void __stdcall SetAlloc( D3DXCore::CAlloc * allocator );
};

void __stdcall CInstruction::SetAlloc( D3DXCore::CAlloc * allocator )
{
	D3DXData01351400 = 0;
	D3DXData01351404 = allocator;
}

void __stdcall CArgument::SetAlloc( D3DXCore::CAlloc * allocator )
{
	D3DXData01351408 = 0;
	D3DXData0135140C = allocator;
}
}
