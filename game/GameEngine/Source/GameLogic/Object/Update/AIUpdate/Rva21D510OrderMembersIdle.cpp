// Retail calls the ILT thunk at 0x0000A5DD, which gen_small/thunks_004.cpp owns
// as ?j_0000a5dd@@YAXXZ and forwards to 0x00154330 -- the body
// AICommandInterfaceObjectCommands.cpp matches as ?aiExit@AICommandInterface.
// The caller therefore names the real method; the resolver keeps the thunk
// address, which is the one retail's call encodes.
#include "../../../command_source_type.h"

class Object;

class Rva21D510Object
{
public:
	unsigned char gap[0x204];
	void *ai;
};

struct Rva21D510Node
{
	Rva21D510Node *next;
	Rva21D510Node *previous;
	Rva21D510Object *object;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiExit(Object *objectToExit, CommandSourceType commandSource);
};

class Rva21D510OrderMembersIdle
{
public:
	void orderAll(int commandSource);

private:
	char m_gap0[0x99C];
	Rva21D510Node *m_objects;
};

void Rva21D510OrderMembersIdle::orderAll(int commandSource)
{
	Rva21D510Node *node = m_objects->next;

	while (node != m_objects) {
		Rva21D510Object *object = node->object;
		void *ai = object->ai;
		node = node->next;

		if (ai != 0) {
			AICommandInterface *command =
				(AICommandInterface *)((char *)ai + 0x20);
			Object *owner = *(Object **)((char *)this - 0x18);
			command->aiExit(owner, (CommandSourceType)commandSource);
		}
	}
}
