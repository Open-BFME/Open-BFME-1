// cl: /O2 /EHsc /MD

class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	~UnicodeString();

private:
	void *m_data;
};

class PopupMessageData
{
public:
	PopupMessageData();
	virtual ~PopupMessageData();

private:
	UnicodeString m_message;
};

PopupMessageData::PopupMessageData()
{
}

PopupMessageData::~PopupMessageData()
{
}
