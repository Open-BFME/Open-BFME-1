// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructors for four concrete network command
// messages. Exact constructors and dedicated vtable slot-zero routes establish
// each class identity independently of the shared wrapper shape.

class NetDisconnectFrameCommandMsg { public: virtual ~NetDisconnectFrameCommandMsg(); };
class BFMENetInformPlayerLeaveFrameCommandMsg { public: virtual ~BFMENetInformPlayerLeaveFrameCommandMsg(); };
class BFMENetRequestFrameDataCommandMsg { public: virtual ~BFMENetRequestFrameDataCommandMsg(); };
class NetDisconnectScreenOffCommandMsg { public: virtual ~NetDisconnectScreenOffCommandMsg(); };

// ctor 0x006740C0; vtable 0x0111A578; slot-zero ILT 0x00033109
void forceNetDisconnectFrameCommandMsgDelete() { NetDisconnectFrameCommandMsg value; }
// ctor 0x00674130; vtable 0x0111A58C; slot-zero ILT 0x0002EBF9
void forceBFMENetInformPlayerLeaveFrameCommandMsgDelete() { BFMENetInformPlayerLeaveFrameCommandMsg value; }
// ctor 0x00674260; vtable 0x0111A5B4; slot-zero ILT 0x0003AA62
void forceBFMENetRequestFrameDataCommandMsgDelete() { BFMENetRequestFrameDataCommandMsg value; }
// ctor 0x00674310; vtable 0x0111A5C8; slot-zero ILT 0x000256DF
void forceNetDisconnectScreenOffCommandMsgDelete() { NetDisconnectScreenOffCommandMsg value; }
