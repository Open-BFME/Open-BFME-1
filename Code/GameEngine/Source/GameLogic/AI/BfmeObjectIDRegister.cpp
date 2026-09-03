// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	int getID() const { return m_id; }

private:
	unsigned char m_pad00[0x74];
	int m_id;
};

struct BfmeInsertResult
{
	void *m_iterator;
	bool m_inserted;
};

class BfmeObjectIDTree
{
public:
	BfmeInsertResult insertUnique(const int &id);
};

class BfmeObjectNotifyBase
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
	virtual void notifyObject(Object *object, bool removed);
};

class BfmeObjectIDRegisterView
{
public:
	void bfmeRegisterObject(Object *object);

private:
	unsigned char m_pad00[0x30];
	BfmeObjectIDTree m_ids;
};

void BfmeObjectIDRegisterView::bfmeRegisterObject(Object *object)
{
	m_ids.insertUnique(object->getID());
	reinterpret_cast<BfmeObjectNotifyBase *>(
		reinterpret_cast<unsigned char *>(this) - 0xc4)->notifyObject(object, false);
}
