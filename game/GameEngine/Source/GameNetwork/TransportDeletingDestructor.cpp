// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: Transport scalar-deleting destructor at retail RVA 0x00662A20
// (30 bytes). The exact constructor at 0x00683360, recovered transport method
// family, and LANAPI's owned deletion establish the non-virtual class. The
// wrapper calls its destructor through ILT 0x0003A48B before delete.

class Transport
{
public:
	~Transport();
};

void forceTransportDelete(Transport *transport)
{
	delete transport;
}
