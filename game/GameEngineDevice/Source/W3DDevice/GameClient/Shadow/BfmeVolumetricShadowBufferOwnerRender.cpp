// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

struct BfmeShadowMeshData
{
	unsigned char m_unreconstructed_000[0x24];
	int m_vertexCount;
	int m_otherCount;
};

struct BfmeShadowMesh
{
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual int Is_Alpha();

	unsigned char m_unreconstructed_00[0xc4];
	BfmeShadowMeshData *m_meshData;
};

struct BfmeShadowBufferEntry
{
	BfmeShadowMesh *mesh;
	void *allocation0;
	void *allocation1;
	void *allocation2;
	unsigned int reserved10;
	unsigned char reserved14;
	void update();
	void fill(unsigned char *value);
	void render(void *vertex, unsigned short vertexCount, void *index,
		unsigned short *scratch);
};

struct BfmeShadowVector3
{
	float x;
	float y;
	float z;
};

struct BfmeShadowVertexLock
{
	void *m_buffer;
	BfmeShadowVector3 *m_vertices;
};

struct BfmeShadowIndexLock
{
	void *m_buffer;
	unsigned short *m_indices;
};

struct BfmeShadowBufferManager
{
	void *m_vertexBuffer;
	void *m_indexBuffer;
	void *m_unused08;
	BfmeShadowVertexLock *m_vertexLock;
	BfmeShadowIndexLock *m_indexLock;
	unsigned int m_vertexCapacity;
	unsigned int m_indexCapacity;
};

struct BfmeShadowCall1Int
{
	void Call(int value);
};

typedef void (BfmeShadowCall1Int::*BfmeShadowCall1IntFn)(int);

class Rva007B12F0Base
{
public:
	virtual void handle();

private:
	char m_padding[0x54];
};

extern void j_00021030();
extern void j_00034be9();
extern void j_000494fe();
extern void j_00045b83();
extern void j_00028baa();
extern void j_0003d253();

struct BfmeVolumetricShadowBufferOwner : public Rva007B12F0Base
{
	unsigned char m_prefix[0x20];
	int m_entryCount;
	BfmeShadowBufferEntry *m_entries;
	unsigned char m_padding80[0x10];
	unsigned short m_scratch[6];
	unsigned char m_mode;

	void renderBuffer();
};

void BfmeVolumetricShadowBufferOwner::renderBuffer()
{
	BfmeVolumetricShadowBufferOwner *owner = this;
	BfmeShadowBufferEntry *entry = owner->m_entries + owner->m_entryCount;
	while (entry != owner->m_entries)
	{
		unsigned char hasShadow = (entry - 1)->reserved14;
		--entry;
		if (hasShadow == 0 && entry->mesh->Is_Alpha() && owner->m_mode == 0)
			continue;

		entry->update();
		unsigned short *scratch = owner->m_scratch;
		entry->fill((unsigned char *)scratch);
		j_000494fe();

		int vertexCount = entry->mesh->m_meshData->m_vertexCount;
		int vertexTotal = (vertexCount + (int)entry->reserved10 * 2) * 3;
		if (vertexTotal <= 30000)
		{
			BfmeShadowBufferManager *buffers =
				*(BfmeShadowBufferManager **)0x01307178;
			if (buffers->m_vertexLock != 0 &&
				buffers->m_indexCapacity < (unsigned)vertexTotal)
			{
				BfmeShadowCall1IntFn release;
				union { void *asVoid; BfmeShadowCall1IntFn asMember; } releaseCast;
				releaseCast.asVoid = (void *)j_00045b83;
				release = releaseCast.asMember;
				(reinterpret_cast<BfmeShadowCall1Int *>(buffers)->*release)(1);
				buffers = *(BfmeShadowBufferManager **)0x01307178;
			}
			if (buffers->m_vertexLock == 0)
			{
				j_00028baa();
				buffers = *(BfmeShadowBufferManager **)0x01307178;
			}

			unsigned short *indexWrite = buffers->m_indexLock->m_indices;
			BfmeShadowVector3 *vertexWrite =
				buffers->m_vertexLock->m_vertices;
			entry->render(
				vertexWrite + (30000 - buffers->m_vertexCapacity),
				(unsigned short)30000 - (unsigned short)buffers->m_vertexCapacity,
				indexWrite + (30000 - buffers->m_indexCapacity),
				scratch);

			BfmeShadowBufferManager *updatedBuffers =
				*(BfmeShadowBufferManager **)0x01307178;
			int otherCount = entry->mesh->m_meshData->m_otherCount;
			updatedBuffers->m_vertexCapacity -= otherCount * 2;
			BfmeShadowBufferManager *updatedBuffers2 =
				*(BfmeShadowBufferManager **)0x01307178;
			updatedBuffers2->m_indexCapacity -=
				vertexCount * 3 + (int)entry->reserved10 * 6;
		}
	}
}
