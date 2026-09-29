// Retail 0x00872650 is the TableMap visitor passed by bfmeWalkXM at
// 0x00872680. The matched caller builds this four-word context on its stack.
typedef void (__cdecl *BfmeWalkXMCallback)(void *, int, void *, int);

struct BfmeWalkXMVisitorData
{
	void *m_bfmeOwner;					// +0x00
	BfmeWalkXMCallback m_bfmeCallback;	// +0x04
	int m_bfmeValue;					// +0x08
	int m_bfmeIndex;					// +0x0C
};

extern "C" void __cdecl bfmeVisitXM(void *entry, void *opaque)
{
	BfmeWalkXMVisitorData *data = (BfmeWalkXMVisitorData *)opaque;
	int index = data->m_bfmeIndex;
	data->m_bfmeIndex = index + 1;
	data->m_bfmeCallback(data->m_bfmeOwner, index, entry, data->m_bfmeValue);
}
