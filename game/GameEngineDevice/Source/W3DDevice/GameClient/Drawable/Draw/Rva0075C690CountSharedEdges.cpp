// Address-qualified reconstruction of retail RVA 0x0075C690.
// Each packed entry names three vertices. The helper counts entries containing
// both requested vertices after translating the packed indices through the
// caller's vertex-remap table.

typedef unsigned short UnsignedShort;

struct Rva0075C690PackedEntry
{
	UnsignedShort vertex[3];
};

static __declspec(noinline) int Rva0075C690CountSharedEdges(
	int entryCount, const Rva0075C690PackedEntry *entries,
	const int *vertexRemap, int firstVertex, int secondVertex)
{
	int sharedCount = 0;
	for (int i = 0; i < entryCount; ++i)
	{
		bool hasFirst =
			firstVertex == vertexRemap[entries[i].vertex[0]] ||
			firstVertex == vertexRemap[entries[i].vertex[1]] ||
			firstVertex == vertexRemap[entries[i].vertex[2]];
		bool hasSecond =
			secondVertex == vertexRemap[entries[i].vertex[0]] ||
			secondVertex == vertexRemap[entries[i].vertex[1]] ||
			secondVertex == vertexRemap[entries[i].vertex[2]];
		if (hasFirst && hasSecond)
			++sharedCount;
	}
	return sharedCount;
}

// The retail helper has internal linkage and is called three times from its
// owning routine. Keeping that call pattern visible lets MSVC apply the same
// translation-unit-local register convention.
int Rva0075C690CallPattern(int count,
	const Rva0075C690PackedEntry *entries, const int *remap,
	int a, int b, int c)
{
	return Rva0075C690CountSharedEdges(count, entries, remap, a, b)
		+ Rva0075C690CountSharedEdges(count, entries, remap, b, c)
		+ Rva0075C690CountSharedEdges(count, entries, remap, c, a);
}
