// cl: /DNDEBUG /MD /EHsc

typedef unsigned long uint32;

class ChunkLoadClass
{
public:
	bool Open_Chunk();
	bool Close_Chunk();
	uint32 Cur_Chunk_ID();
	uint32 Read(void *buffer, uint32 bytes);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/WW3D/pluglib/w3d_file.h
struct W3dVectorStruct
{
	float x, y, z;
};

struct W3dHierarchyStruct
{
	uint32 Version;
	char Name[16];
	uint32 NumPivots;
	W3dVectorStruct Center;
};

// Retail allocates exactly count * 0xB4 bytes and therefore has no array
// cookie. The empty destructor in the later reference header is not part of
// this BFME-era ABI shape.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pivot.h
class PivotClass
{
public:
	PivotClass();

private:
	unsigned char m_data[0xB4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
class HTreeClass
{
public:
	enum { OK, LOAD_ERROR };

	int Load_W3D(ChunkLoadClass &cload);

private:
	void Free();
	bool read_pivots(ChunkLoadClass &cload, bool pre30);

	char Name[16];
	int NumPivots;
	PivotClass *Pivot;
	float ScaleFactor;
};

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);

int HTreeClass::Load_W3D(ChunkLoadClass &cload)
{
	if (Pivot != 0)
	{
		delete[] Pivot;
		Pivot = 0;
	}
	NumPivots = 0;
	ScaleFactor = 1.0f;

	if (!cload.Open_Chunk())
		return LOAD_ERROR;

	if (cload.Cur_Chunk_ID() != 0x101)
		return LOAD_ERROR;

	W3dHierarchyStruct header;
	if (cload.Read(&header, sizeof(header)) != sizeof(header))
		return LOAD_ERROR;

	cload.Close_Chunk();

	bool pre30 = false;
	if (header.Version < 0x30000)
	{
		header.NumPivots++;
		pre30 = true;
	}

	memcpy(Name, header.Name, sizeof(Name));
	NumPivots = header.NumPivots;
	if (NumPivots > 0)
		Pivot = new PivotClass[NumPivots];

	while (cload.Open_Chunk())
	{
		if (cload.Cur_Chunk_ID() == 0x102)
		{
			if (!read_pivots(cload, pre30))
			{
				Free();
				return LOAD_ERROR;
			}
		}
		cload.Close_Chunk();
	}

	return OK;
}
