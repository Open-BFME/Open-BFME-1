// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: NetGameCommandMsg scalar-deleting destructor at retail RVA
// 0x00674380 (30 bytes). Its exact constructors at 0x00673640/0x00674A40,
// complete destructor at 0x006736B0, and recovered command methods establish
// the class. The destructor ILT is 0x00010B36.

class NetGameCommandMsg
{
public:
	virtual ~NetGameCommandMsg();
};

void forceNetGameCommandMsgDeletingDestructor()
{
	NetGameCommandMsg value;
}
