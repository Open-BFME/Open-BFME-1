// cl: /DNDEBUG /MD /EHsc /GS
// Open-BFME: compact FESL transaction message sender, retail 0x00804010.
//
// The message object and its fixed-buffer constructor are the same retail
// type recovered in BfmeConv994.cpp.  This method supplies the transaction
// category and depth, appends the integer transaction id, and submits it.
class BfmeC994
{
public:
	BfmeC994(char *buffer, int capacity);
	void addInt(const char *key, int value);
	void clear();

	char m_beforeCategory[0x1C];
	int m_category;
	int m_depth;
	char m_tail[0x10];
};

class BfmeSinkSKA
{
public:
	void bfmeSendSKA(int category, int transactionId, int depth);

private:
	void submit(BfmeC994 *message);
};

void BfmeSinkSKA::bfmeSendSKA(int category, int transactionId, int depth)
{
	char buffer[32];
	BfmeC994 message(buffer, sizeof(buffer));
	message.m_category = category;
	message.m_depth = depth;
	message.addInt("TID", transactionId);
	submit(&message);
	message.clear();
}
