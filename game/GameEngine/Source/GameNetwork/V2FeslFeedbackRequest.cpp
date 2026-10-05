// cl: /GS
// EA FESL client SDK ("jabba") -- feedback transaction request builder.
// The literal keys and the 'fdbk' category identify the wire payload.  The
// helper callees serialize an 8-byte-stride target-id array and 0x208-byte
// chat-log records (64-bit user id followed by a 0x200-byte string).

typedef __int64 FeslInt64;

extern "C" int __cdecl sprintf( char *buffer, const char *format, ... );

extern const char g_Rva012DAC14[];
// retail 0x007E8AC0: ?run@Rva007E8AC0@@QAEXXZ
class Rva007E8AC0
{
public:
	void run( void );
};

class Rva007E8810Message
{
public:
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

void Rva007F1F60Feedback::addTargetIds( Rva007E8810Message *msg,
	const Rva007F2010TargetId *targetIds, int count )
{
	char key[ 32 ];
	Rva007E8810Message *message = msg;
	const Rva007F2010TargetId *ids = targetIds;
	int limit = count;
	for ( int i = 0; i < limit; ++i )
	{
		sprintf( key, "targetIds.%d", i );
		message->addInt( key, ids[ i ].id );
	}
	message->addInt( "targetIds.[]", count );
}

void Rva007F1F60Feedback::addChatLog( Rva007E8810Message *msg,
	const Rva007F2080ChatLog *chatLog, int count )
{
	char key[ 32 ];
	Rva007E8810Message *message = msg;
	const Rva007F2080ChatLog *logs = chatLog;
	int limit = count;
	for ( int i = 0; i < limit; ++i )
	{
		sprintf( key, "chatLog.%d.userId", i );
		message->addInt64( key, logs[ i ].userId );
		sprintf( key, "chatLog.%d.chat", i );
		message->addString( key, logs[ i ].chat );
	}
	message->addInt( "chatLog.[]", count );
}

void Rva007F1F60Feedback::buildRequest( Rva007E8810Message *msg, int targetType,
	const Rva007F2010TargetId *targetIds, int targetIdCount,
	FeslInt64 originatorUserId, const char *message, int feedbackType,
	const Rva007F2080ChatLog *chatLog, int chatLogCount,
	const char *extraFeedbackDetail )
{
	const char *txn = g_Rva0130A63C;
	((Rva007E8AC0 *)msg)->run();
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
