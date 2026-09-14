// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ConnectionManager scalar-deleting destructor at retail RVA
// 0x00681E10 (30 bytes). Its constructor installs the ConnectionManager vtable
// and Network's matched teardown calls the canonical complete destructor
// through ILT 0x00019E25 before operator delete. This wrapper reproduces that
// non-virtual destructor/delete sequence.

class ConnectionManager
{
public:
	~ConnectionManager();
};

void forceConnectionManagerDelete(ConnectionManager *manager)
{
	delete manager;
}
