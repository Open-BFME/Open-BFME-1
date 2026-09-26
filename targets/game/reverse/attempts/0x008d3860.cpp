// ?d_008d3860@@YAXXZ
// partial score=0.41 date=2026-09-23
// cl: /O2 /Ob1

struct Rva008D3860Command;
struct Rva008D3860Owner;

struct Rva008D3860Frame
{
	int m_count00;
	Rva008D3860Command **m_commands04;
};

struct Rva008D3860Command
{
	int m_kind00;
	int m_value04;
	void *m_payload08;
	void *m_key0c;
};

struct Rva008D3860ActionList
{
	int m_count00;
	Rva008D3860Command **m_commands04;
};

struct Rva008D3860ActionRow
{
	int m_count00;
	Rva008D3860ActionList *m_actions04;
};

struct Rva008D3860ActionSublist
{
	char m_padding00[8];
	Rva008D3860ActionRow m_row08;
};

struct Rva008D3860MapItem
{
	const char *m_name00;
	int m_index04;
};

struct Rva008D3860Group
{
	char m_padding00[4];
	Rva008D3860ActionList *m_actions04;
	char m_padding08[0x10];
	Rva008D3860ActionSublist **m_actionRows18;
	char m_padding1c[0x14];
	int m_count30;
	Rva008D3860MapItem *m_items34;
};

struct Rva008D3860GroupOwner
{
	char m_padding00[0x10];
	Rva008D3860Group *m_group10;
};

struct Rva008D3860Slot
{
	void *m_value00;
	const char *m_name04;
	char m_padding08[4];
	Rva008D3860GroupOwner *m_owner0c;
};

struct Rva008D3860ActionContext
{
	char m_padding00[4];
	Rva008D3860ActionList *m_actions04;
	char m_padding08[8];
	void *m_audio10;
	char m_padding14[4];
	Rva008D3860ActionSublist **m_actionRows18;
};

struct Rva008D3860LookupView
{
	Rva008D3860ActionContext m_actions00;
	char m_padding1c[4];
	int m_count20;
	Rva008D3860Slot *m_slots24;
};

struct Rva008D3860LookupParent
{
	char m_padding00[8];
	Rva008D3860LookupView m_view08;
};

struct Rva008D3860Descriptor
{
	void *m_value00;
	Rva008D3860LookupParent *m_parent04;
	Rva008D3860ActionRow m_row08;
};

struct Rva008D3860OwnerState
{
	char m_padding00[0x0c];
	Rva008D3860Descriptor *m_descriptor0c;
};

struct Rva008D3860Owner
{
	char m_padding00[0x50];
	Rva008D3860OwnerState *m_state50;
};

struct Rva008D3860Audio
{
	char m_padding00[8];
	void *m_handle08;
};

struct Rva008D3860FrameOwner
{
	void *m_value00;
	Rva008D3860Frame *m_frames04;
	void doFrameControls(void *context, Rva008D3860Owner *owner, int frame);
};

struct Gen_008A06C0
{
	int m_padding00[8];
	int m_count20;
	void *m_entries24;
	int bfmeIndexOf(void *key) const;
};

struct Rva008A1CF0
{
	int rva008A1CF0(int index);
	char m_padding00[0x24];
	Rva008D3860Slot *m_slots24;
};

struct Rva008A1D80
{
	void apply(Rva008D3860Owner *owner, void *key);
};

struct Rva008BEF00
{
	void apply(int *value, Rva008D3860Owner *owner);
};

struct Rva008AE770Stack {};
extern Rva008AE770Stack Rva008AE770TheStack;

class BfmeR1226
{
public:
	void bfmeAdd1226(void *value, void *source, int flags);
	void bfmeLine1226(char *text);
};

struct BfmeInput1279
{
	void *m_value;
};

class BfmeWrapper1279
{
public:
	void bfmeForward1279(BfmeInput1279 *input);
};

extern void (__cdecl *g_bfmePlay1282)(void *handle, int zero);
extern unsigned char rva013377FCFlag;
extern void (__cdecl *rva01337838Callback)(int value);

void Rva008D3860FrameOwner::doFrameControls(
	void *context, Rva008D3860Owner *owner, int frame)
{
	int frameIndex = frame;
	for (int i = 0; i < m_frames04[frameIndex].m_count00; ++i) {
		Rva008D3860Command *command = m_frames04[frameIndex].m_commands04[i];
		if (command->m_kind00 == 8 && command->m_value04 >= 0) {
			BfmeR1226 *stack = (BfmeR1226 *)&Rva008AE770TheStack;
			stack->bfmeAdd1226(command->m_payload08, owner, -1);
			stack->bfmeLine1226((char *)"doFrameControls");
			command->m_value04 = -command->m_value04;
		}
	}

	for (int i = 0; i < m_frames04[frameIndex].m_count00; ++i) {
		Rva008D3860Command *command = m_frames04[frameIndex].m_commands04[i];
		switch (command->m_kind00) {
		case 5:
			if (rva013377FCFlag == 0) {
				rva01337838Callback(command->m_value04);
				rva013377FCFlag = 1;
			}
			break;
		case 3: {
			Rva008D3860Descriptor *descriptor = owner->m_state50->m_descriptor0c;
			Rva008D3860LookupParent *parent = descriptor->m_parent04;
			Rva008D3860LookupView *lookup = &parent->m_view08;
			int action = (int)command->m_key0c;
			int slot = ((Gen_008A06C0 *)lookup)->bfmeIndexOf((void *)action);
			Rva008D3860ActionContext *actions = (Rva008D3860ActionContext *)lookup;
			Rva008D3860ActionRow *row = &descriptor->m_row08;

			if (slot != -1) {
				action = ((Rva008A1CF0 *)lookup)->rva008A1CF0(slot);
				if (action != -1) {
					actions = (Rva008D3860ActionContext *)lookup->m_slots24[slot].m_owner0c->m_group10;
					row = &((Rva008D3860ActionSublist *)actions->m_actionRows18[action])->m_row08;
				}
			}

			if (row->m_count00 > 0) {
				Rva008D3860ActionList *nestedList = row->m_actions04;
				for (int j = 0; j < nestedList->m_count00; ++j) {
					Rva008D3860Command *nested = nestedList->m_commands04[j];
					if (nested->m_kind00 == 3 && nested->m_key0c != (void *)-1)
					((Rva008A1D80 *)actions)->apply(owner, nested->m_key0c);
				}
			}

			if (action != -1)
				((Rva008A1D80 *)actions)->apply(owner, (void *)action);
			((Rva008BEF00 *)context)->apply(&command->m_value04, owner);
			break;
		}
		case 4:
			((BfmeWrapper1279 *)owner)->bfmeForward1279(
				(BfmeInput1279 *)&command->m_value04);
			break;
		case 6: {
			Rva008D3860Descriptor *descriptor = owner->m_state50->m_descriptor0c;
			Rva008D3860Audio *audio = (Rva008D3860Audio *)
				descriptor->m_parent04->m_view08.m_actions00.m_audio10;
			g_bfmePlay1282(audio[command->m_value04].m_handle08, 0);
			break;
		}
		case 7:
			continue;
		}
	}
}
