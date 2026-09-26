// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame

struct Rva00785FD0D3DVertexBuffer
{
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void __stdcall lock(unsigned offset, unsigned size, unsigned char **data, unsigned flags) = 0;
};

struct Rva00785FD0FvfInfo
{
	unsigned fvf;
	unsigned vertexSize;
};

struct Rva00785FD0VertexBuffer
{
	unsigned char prefix[0x14];
	Rva00785FD0FvfInfo *fvfInfo;
	unsigned char padding18[4];
	Rva00785FD0D3DVertexBuffer *d3dBuffer;
};

struct Rva00785FD0Vertex
{
	unsigned char bytes[32];
};

struct Rva00785FD0Renderer
{
	unsigned char changed;
	unsigned char pending;
	unsigned char padding02[2];
	unsigned char body04[0xcc];
	Rva00785FD0VertexBuffer *vertexBuffer;
	int vertexOffset;
	int vertexCount;
	Rva00785FD0Vertex *reserved;
};

void __fastcall j_0001569f(void *renderer);

void * __fastcall rva0078C300RendererAppend(Rva00785FD0Renderer *renderer, int count)
{
	int vertexCount = count * 3;
	if (vertexCount > 0x4e20 || renderer->vertexBuffer == 0)
		return 0;

	if (renderer->pending || renderer->changed)
		j_0001569f(renderer);

	if (renderer->vertexOffset + renderer->vertexCount + vertexCount > 0x4e20)
	{
		j_0001569f(renderer);
		renderer->vertexOffset = 0;
	}

	Rva00785FD0VertexBuffer *vertexBuffer = renderer->vertexBuffer;
	unsigned vertexSize = vertexBuffer->fvfInfo->vertexSize;
	unsigned char *data;
	if (renderer->vertexOffset == 0 && renderer->vertexCount == 0)
		vertexBuffer->d3dBuffer->lock(0, vertexSize * vertexCount, &data, 0x2000);
	else
		vertexBuffer->d3dBuffer->lock(vertexSize * (renderer->vertexOffset + renderer->vertexCount),
			vertexSize * vertexCount, &data, 0x1000);

	renderer->reserved = (Rva00785FD0Vertex *)data + vertexCount;
	renderer->vertexCount += vertexCount;
	return data;
}
