// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: Connection scalar-deleting destructor at retail RVA 0x00665320
// (30 bytes). The exact constructor at 0x006623A0 and matched complete
// destructor at 0x006652B0 establish the non-virtual class. The wrapper calls
// that destructor through ILT 0x0003CECF before conditionally invoking delete.

class Connection
{
public:
	~Connection();
};

void forceConnectionDelete(Connection *connection)
{
	delete connection;
}
