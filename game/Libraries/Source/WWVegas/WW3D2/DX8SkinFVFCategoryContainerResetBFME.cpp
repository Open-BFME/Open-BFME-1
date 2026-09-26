// cl: /DNDEBUG /MD /EHsc
// BFME DX8SkinFVFCategoryContainer::Reset at 0x00945E00.  The retail layout
// carries eight 0x18-byte per-pass texture-category lists, followed by its
// index buffer at +0xD8, used-index count at +0xDC, and pass count at +0xE4.

class DX8TextureCategoryClass
{
public:
	virtual ~DX8TextureCategoryClass(void);
};

struct MultiListNodeClass
{
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	void *Object;
	void *List;
};

class TextureCategoryList
{
public:
	DX8TextureCategoryClass *Peek_Head(void)
	{
		MultiListNodeClass *node = *reinterpret_cast<MultiListNodeClass **>(this);
		if (node == reinterpret_cast<MultiListNodeClass *>(
			reinterpret_cast<char *>(this) - 4))
			return 0;
		return static_cast<DX8TextureCategoryClass *>(node->Object);
	}

private:
	char Data[0x18];
};

class IndexBufferClass
{
public:
	virtual void Delete_This(void) = 0;
	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

private:
	int NumRefs;
};

class DX8SkinFVFCategoryContainer
{

	void Reset(void);
	void clearVisibleSkinList(void);

	char Prefix[0x10];
	TextureCategoryList texture_category_list[8];
	char BeforeIndexBuffer[0x08];
	IndexBufferClass *index_buffer;
	unsigned used_indices;
	unsigned dynamic_fvf_type;
	unsigned passes;
};

// ?Reset@DX8SkinFVFCategoryContainer@@AAEXXZ
void DX8SkinFVFCategoryContainer::Reset(void)
{
	clearVisibleSkinList();

	for (unsigned pass = 0; pass < passes; ++pass) {
		while (DX8TextureCategoryClass *texture_category =
			texture_category_list[pass].Peek_Head()) {
			delete texture_category;
		}
	}

	if (index_buffer != 0) {
		index_buffer->Release_Ref();
		index_buffer = 0;
	}
	used_indices = 0;
}
