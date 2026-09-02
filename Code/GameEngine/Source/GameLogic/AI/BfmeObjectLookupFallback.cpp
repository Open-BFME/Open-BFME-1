// cl: /DNDEBUG /MD /EHsc

struct BfmeObjectNode
{
	BfmeObjectNode *m_next;
	BfmeObjectNode *m_previous;
	void *m_object;
	unsigned char m_pad0C[4];
	int m_objectID;
};

struct BfmeObjectList
{
	BfmeObjectNode *m_header;
};

struct BfmeFallbackHeader
{
	unsigned char m_pad00[8];
	BfmeObjectNode *m_last;
};

class BfmePrimaryObjectSource
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64();
	virtual BfmeObjectList *getPrimaryObjects();
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class BfmeObjectLookupView
{
public:
	void *bfmeFindObject();

private:
	unsigned char m_pad00[0x30];
	BfmeFallbackHeader *m_fallbackHeader;
};

void *BfmeObjectLookupView::bfmeFindObject()
{
	BfmePrimaryObjectSource *source = reinterpret_cast<BfmePrimaryObjectSource *>(
		reinterpret_cast<unsigned char *>(this) - 0xc4);
	BfmeObjectNode *header = source->getPrimaryObjects()->m_header;
	BfmeObjectNode *node = header->m_next;
	if (node != header)
		return node->m_object;

	BfmeFallbackHeader *fallback = m_fallbackHeader;
	node = fallback->m_last;
	if (node != reinterpret_cast<BfmeObjectNode *>(fallback))
		return TheGameLogic->findObjectByID(node->m_objectID);
	return 0;
}
