// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for five concrete network command
// messages. Each exact constructor installs the dedicated vtable documented
// beside its force function; slot zero routes to the corresponding wrapper.

class NetAckStage1CommandMsg { public: virtual ~NetAckStage1CommandMsg(); };
class NetAckStage2CommandMsg { public: virtual ~NetAckStage2CommandMsg(); };
class NetPlayerLeaveCommandMsg { public: virtual ~NetPlayerLeaveCommandMsg(); };
class NetDestroyPlayerCommandMsg { public: virtual ~NetDestroyPlayerCommandMsg(); };
class NetKeepAliveCommandMsg { public: virtual ~NetKeepAliveCommandMsg(); };

// ctor 0x006738A0; vtable 0x0111A49C; slot-zero ILT 0x0003BF9D
void forceNetAckStage1CommandMsgDelete() { NetAckStage1CommandMsg value; }
// ctor 0x006739B0; vtable 0x0111A4B0; slot-zero ILT 0x00002E32
void forceNetAckStage2CommandMsgDelete() { NetAckStage2CommandMsg value; }
// ctor 0x00673AA0; vtable 0x0111A4C4; slot-zero ILT 0x0001BC89
void forceNetPlayerLeaveCommandMsgDelete() { NetPlayerLeaveCommandMsg value; }
// ctor 0x00673B10; vtable 0x0111A4D8; slot-zero ILT 0x0003AD37
void forceNetDestroyPlayerCommandMsgDelete() { NetDestroyPlayerCommandMsg value; }
// ctor 0x00673B80; vtable 0x0111A4EC; slot-zero ILT 0x0000A790
void forceNetKeepAliveCommandMsgDelete() { NetKeepAliveCommandMsg value; }
