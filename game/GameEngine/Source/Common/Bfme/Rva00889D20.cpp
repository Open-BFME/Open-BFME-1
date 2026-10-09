// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern void* __cdecl DebugAllocMemory( unsigned int );

struct Rva00889D20Node
{
	Rva00889D20Node* next;
	void* arg1;
	void* arg2;
	void* arg3;
	int unk_10;
	int unk_14;
	int unk_18;
	int unk_1c;
};

struct Rva00889D70Node
{
	Rva00889D70Node* next;
	void* arg1;
	void* arg2;
};

class Rva00889D20Class
{
public:
	char pad[0xC];
	Rva00889D20Node* head_0C;
	Rva00889D70Node* head_10;

	bool d_00889d20( void* arg1, void* arg2, void* arg3 );
};

bool Rva00889D20Class::d_00889d20( void* arg1, void* arg2, void* arg3 )
{
	if ( !arg1 || !arg3 )
	{
		return true;
	}

	Rva00889D20Node* node = (Rva00889D20Node*)DebugAllocMemory( 0x20 );
	node->next = head_0C;
	node->arg1 = arg1;
	node->arg2 = arg2;
	node->arg3 = arg3;
	node->unk_10 = 0;
	node->unk_14 = 0;
	node->unk_1c = 0;
	node->unk_18 = 0;

	head_0C = node;
	return true;
}

