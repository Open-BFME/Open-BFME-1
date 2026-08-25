// EA FESL client SDK ("jabba") -- feedback transaction request builder.
// The literal keys and the 'fdbk' category identify the wire payload.  The
// helper callees serialize an 8-byte-stride target-id array and 0x208-byte
// chat-log records (64-bit user id followed by a 0x200-byte string).

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	void reset( void );
	void addString( const char *key, const char *value );
	void addInt( const char *key, int value );
	void addInt64( const char *key, FeslInt64 value );

	char m_head[ 0x1C ];
	unsigned int m_category;
};

struct Rva007F2010TargetId
{
	int id;
	int unused;
};

struct Rva007F2080ChatLog
{
	FeslInt64 userId;
	char chat[ 0x200 ];
};

extern const char * const g_Rva0130A63C;

class Rva007F1F60Feedback
{
public:
	void addTargetIds( Rva007E8810Message *msg,
		const Rva007F2010TargetId *targetIds, int count );
	void addChatLog( Rva007E8810Message *msg,
		const Rva007F2080ChatLog *chatLog, int count );
	void buildRequest( Rva007E8810Message *msg, int targetType,
		const Rva007F2010TargetId *targetIds, int targetIdCount,
		FeslInt64 originatorUserId, const char *message, int feedbackType,
		const Rva007F2080ChatLog *chatLog, int chatLogCount,
		const char *extraFeedbackDetail );
};

void Rva007F1F60Feedback::buildRequest( Rva007E8810Message *msg, int targetType,
	const Rva007F2010TargetId *targetIds, int targetIdCount,
	FeslInt64 originatorUserId, const char *message, int feedbackType,
	const Rva007F2080ChatLog *chatLog, int chatLogCount,
	const char *extraFeedbackDetail )
{
	const char *txn = g_Rva0130A63C;
	msg->reset();
	msg->m_category = 'fdbk';
	msg->addString( "TXN", txn );
	addTargetIds( msg, targetIds, targetIdCount );
	msg->addInt( "targetType", targetType );
	msg->addInt64( "originatorUserId", originatorUserId );
	msg->addString( "message", message );
	msg->addInt( "feedbackType", feedbackType );
	addChatLog( msg, chatLog, chatLogCount );
	msg->addString( "extraFeedbackDetail", extraFeedbackDetail );
}
