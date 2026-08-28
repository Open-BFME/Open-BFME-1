// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// readable body of ?renderBibs@W3DBibBuffer@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBibBuffer.cpp

class IndexBufferClass;
class ShaderClass;
class TextureBaseClass;
class VertexBufferClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass *buffer, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const VertexBufferClass *buffer, unsigned stream = 0);
	static void Set_Shader(const ShaderClass &shader);
	static void Draw_Triangles(unsigned short start_index, unsigned short polygon_count, unsigned short min_vertex_index, unsigned short vertex_count);
};

void __cdecl BoxSetTexture(unsigned stage, TextureBaseClass *&texture);
extern ShaderClass detailAlphaShader;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBibBuffer.h
class W3DBibBuffer
{
public:
	void renderBibs();

protected:
	void loadBibsInVertexAndIndexBuffers();

private:
	VertexBufferClass *m_vertexBib;
	int m_vertexBibSize;
	IndexBufferClass *m_indexBib;
	int m_indexBibSize;
	TextureBaseClass *m_bibTexture;
	TextureBaseClass *m_highlightBibTexture;
	unsigned short m_curNumBibVertices;
	int m_curNumBibIndices;
	int m_curNumNormalBibIndices;
	unsigned short m_curNumNormalBibVertex;
};

void W3DBibBuffer::renderBibs()
{
	loadBibsInVertexAndIndexBuffers();
	if (m_curNumBibIndices == 0)
		return;

	DX8Wrapper::Set_Index_Buffer(m_indexBib, 0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexBib);
	DX8Wrapper::Set_Shader(detailAlphaShader);

	if (m_curNumNormalBibIndices != 0)
	{
		BoxSetTexture(0, m_bibTexture);
		DX8Wrapper::Draw_Triangles(0, m_curNumNormalBibIndices / 3, 0, m_curNumNormalBibVertex);
	}

	if (m_curNumBibIndices > m_curNumNormalBibIndices)
	{
		BoxSetTexture(0, m_highlightBibTexture);
		DX8Wrapper::Draw_Triangles(m_curNumNormalBibIndices, (m_curNumBibIndices - m_curNumNormalBibIndices) / 3, m_curNumNormalBibVertex, m_curNumBibVertices - m_curNumNormalBibVertex);
	}
}
