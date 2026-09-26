// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for five concrete network command
// messages. Their exact constructors and dedicated vtable slot-zero routes
// independently establish every identity below.

class NetDisconnectKeepAliveCommandMsg { public: virtual ~NetDisconnectKeepAliveCommandMsg(); };
class NetDisconnectPlayerCommandMsg { public: virtual ~NetDisconnectPlayerCommandMsg(); };
class NetDisconnectVoteCommandMsg { public: virtual ~NetDisconnectVoteCommandMsg(); };
class NetProgressCommandMsg { public: virtual ~NetProgressCommandMsg(); };
class NetFileProgressCommandMsg { public: virtual ~NetFileProgressCommandMsg(); };

// ctor 0x00673BD0; vtable 0x0111A500; slot-zero ILT 0x000458FE
void forceNetDisconnectKeepAliveCommandMsgDelete() { NetDisconnectKeepAliveCommandMsg value; }
// ctor 0x00673C20; vtable 0x0111A514; slot-zero ILT 0x0001413C
void forceNetDisconnectPlayerCommandMsgDelete() { NetDisconnectPlayerCommandMsg value; }
// ctor 0x00673CD0; vtable 0x0111A528; slot-zero ILT 0x000297CB
void forceNetDisconnectVoteCommandMsgDelete() { NetDisconnectVoteCommandMsg value; }
// ctor 0x00673D60; vtable 0x0111A53C; slot-zero ILT 0x0004376B
void forceNetProgressCommandMsgDelete() { NetProgressCommandMsg value; }
// ctor 0x00674030; vtable 0x0111A564; slot-zero ILT 0x00045011
void forceNetFileProgressCommandMsgDelete() { NetFileProgressCommandMsg value; }
