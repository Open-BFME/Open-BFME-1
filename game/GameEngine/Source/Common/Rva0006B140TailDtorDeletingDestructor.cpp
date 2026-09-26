// cl: /DNDEBUG /MD /EHsc
// Vtable 0x01075AD8 slot 0 reaches 0x0006B110; its call targets 0x0006B140.

class Rva0006B140TailDtor
{
public:
	virtual ~Rva0006B140TailDtor();
};

__declspec(noinline) Rva0006B140TailDtor::~Rva0006B140TailDtor() {}

void Force_Rva0006B140TailDtor_Deleting_Destructor(Rva0006B140TailDtor *value)
{
	delete value;
}
