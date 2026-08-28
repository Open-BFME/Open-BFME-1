// cl: /DNDEBUG /MD /EHsc

// MessageStream's constructor, retail 0x0008A600. SubsystemInterface's
// constructor - a name the ledger already has - then five fields.
//
// The four zeroes share one cleared register and the 1 at +0x18 is an
// immediate, so retail's vftable store lands between them rather than ahead of
// both. That is the scheduler and not an order the source asks for.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();

	virtual void subsystemAnchor();

private:
	unsigned char m_unmodelled_04[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class MessageStream : public SubsystemInterface
{
public:
	MessageStream();

private:
	int m_unmodelled_08;					// +0x08
	int m_unmodelled_0C;					// +0x0C
	int m_unmodelled_10;					// +0x10
	int m_unmodelled_14;					// +0x14
	int m_unmodelled_18;					// +0x18
};

// ??0MessageStream@@QAE@XZ
MessageStream::MessageStream()
	: m_unmodelled_08( 0 ),
	  m_unmodelled_0C( 0 ),
	  m_unmodelled_10( 0 ),
	  m_unmodelled_14( 0 ),
	  m_unmodelled_18( 1 )
{
}
