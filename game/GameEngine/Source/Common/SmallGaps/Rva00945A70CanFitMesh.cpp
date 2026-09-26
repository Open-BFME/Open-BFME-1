// ?canFit@Rva00945A70Owner@@QAE_NPBURva00945A70Mesh@@@Z
struct Rva00945A70Counts { int m_0; };
struct Rva00945A70Mesh { char m_pad[0x24]; int m_polyCount; unsigned int m_vertexCount; char m_pad2[0x9c - 0x2c]; Rva00945A70Counts* m_counts; };
struct Rva00945A70Buffer { char m_pad[0xc]; int m_size; };
struct Rva00945A70Table { char m_pad[0xc]; unsigned short m_capacity; };
struct Rva00945A70Owner {
	char m_pad[0xd8];
	Rva00945A70Buffer* m_indexBuffer;
	int m_indexUsed;
	char m_pad2[0xf0 - 0xe0];
	Rva00945A70Table* m_vertexTable;
	int m_vertexUsed;
	bool canFit(const Rva00945A70Mesh* mesh);
};
bool Rva00945A70Owner::canFit(const Rva00945A70Mesh* mesh)
{
	if (!m_vertexTable)
		return true;
	if (mesh->m_vertexCount > (unsigned int)(m_vertexTable->m_capacity - m_vertexUsed) ||
		(unsigned int)(mesh->m_counts->m_0 * mesh->m_polyCount * 3) > (unsigned int)(m_indexBuffer->m_size - m_indexUsed))
		return false;
	return true;
}
