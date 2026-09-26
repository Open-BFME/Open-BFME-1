// cl: /DNDEBUG /MD /EHsc
// BFME chunk 0x29 selects table slot 1 at 0x0096FD00 -> arm 0x0096FCAE,
// calling the shader-array reader at 0x0096EA60 (16-byte W3dShaderStructs
// and Convert_Shader). Chunk 0x2A selects slot 2 -> arm 0x0096FCA3, calling
// the vertex-material reader at 0x0096EB30 (constructor and Load_W3D).
// Keep this case ordering to preserve retail arm layout without swapping
// the two callee identities. Both cases retain the original W3D chunk IDs.

class ChunkLoadClass
{
public:
	unsigned long Cur_Chunk_ID();
	bool Open_Chunk();
	bool Close_Chunk();
	unsigned long Read(void *buffer, unsigned long bytes);
};

class MeshLoadContextClass
{
public:
	unsigned char m_padding[0x78];
	unsigned char m_materialInfo[0x10];
	unsigned long m_prelitChunkID;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.h
class MeshModelClass
{
protected:
	bool read_prelit_material(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_vertex_materials(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_shaders(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_textures(ChunkLoadClass &cload, MeshLoadContextClass *context);
	bool read_material_pass(ChunkLoadClass &cload, MeshLoadContextClass *context);

private:
	unsigned char m_padding[0x9c];
	unsigned long *m_materialInfo;
};

bool MeshModelClass::read_prelit_material(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	if (cload.Cur_Chunk_ID() == context->m_prelitChunkID)
	{
		while (cload.Open_Chunk())
		{
			unsigned char error = 1;
			switch (cload.Cur_Chunk_ID())
			{
			case 0x28:
				if (cload.Read(context->m_materialInfo, sizeof(context->m_materialInfo)) != sizeof(context->m_materialInfo))
				{
					error = false;
				}
				else
				{
					*m_materialInfo = *reinterpret_cast<unsigned long *>(context->m_materialInfo);
					error = true;
				}
				break;
			case 0x2a:
				error = read_vertex_materials(cload, context);
				break;
			case 0x29:
				error = read_shaders(cload, context);
				break;
			case 0x30:
				error = read_textures(cload, context);
				break;
			case 0x38:
				error = read_material_pass(cload, context);
				break;
			}

			cload.Close_Chunk();
			if (error != 1)
				// BFME keeps this normalized status byte live through the return.
				return *reinterpret_cast<bool *>(&error);
		}
	}

	return true;
}
