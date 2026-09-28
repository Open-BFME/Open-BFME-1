// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x00597680 calls Rva00597FC0Client::~Rva00597FC0Client through ILT 0x00025FB8.

class Rva00597FC0Client
{
public:
	virtual ~Rva00597FC0Client();
};

__declspec(noinline) Rva00597FC0Client::~Rva00597FC0Client() {}

void Force_Rva00597FC0Client_Deleting_Destructor(Rva00597FC0Client *client)
{
	delete client;
}
