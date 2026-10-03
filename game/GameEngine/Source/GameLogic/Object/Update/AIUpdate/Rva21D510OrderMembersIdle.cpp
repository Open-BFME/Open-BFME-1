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

void j_0000a5dd(void);

class Rva21D510Exit
{
public:
	void exit(Object *objectToExit, CommandSourceType commandSource);
};
typedef void (Rva21D510Exit::*Rva21D510ExitCall)(Object *, CommandSourceType);

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
			Rva21D510Exit *command = (Rva21D510Exit *)((char *)ai + 0x20);
			union
			{
				void (*raw)(void);
				Rva21D510ExitCall member;
			} call;
			call.raw = j_0000a5dd;
			Object *owner = *(Object **)((char *)this - 0x18);
			(command->*call.member)(owner, (CommandSourceType)commandSource);
		}
	}
}
