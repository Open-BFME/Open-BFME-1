// cl: /O2 /Ob1
// BfmeNode1236List::bfmeProcess1236, retail 0x008D3860 (473 B of code plus
// its five-entry case table, 496 B). The matched BfmeNode1236::
// bfmeActivate1236 (0x008D2810) calls it through this pinned name with
// (&child->walk, node, frame); ret 0xC. Pass one runs kind-8 commands of the
// frame through the Apt bytecode runner (trace literal "doFrameControls", a
// lead for EA's name, not proof); pass two dispatches kinds 3..7. Types are
// address-derived views; callee names are the ledger's.
// Kind 3 re-targets the lookup to the found group's +8 view before reading
// that view's +0x10 row table: assigning the row first swaps ESI for EAX.

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

class BfmeNode1236List
{
public:
	void bfmeProcess1236(void *context, void *ownerArg, int frame);

private:
	void *m_value00;
	Rva008D3860Frame *m_frames04;
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

class Rva008A1D80Owner
{
public:
	void runImportedInitActions(void *owner, int key);
};

struct BfmeDescriptor1288;
struct BfmeContext1288;
class BfmeSubmitter1283
{
public:
	void rva008BEF00(BfmeDescriptor1288 *descriptor, BfmeContext1288 *context);
};

class Rva008CCED0BytecodeRunner
{
public:
	unsigned char *run(void *code, void *owner, int flags);
};

struct Rva008AE770Stack {};
extern Rva008AE770Stack Rva008AE770TheStack;

class BfmeR1226
{
public:
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

// Callback cells the Apt host installs (data rows at VA 0x01337838 and
// 0x01337884, declared there as void (*)()) and the one-shot flag 0x013377FC.
extern void (*g_bfmeSlot03VB)();
extern void (*g_bfmeSlot19VB)();
extern unsigned char g_bfmeFlagESP;
typedef void (__cdecl *Rva008D3860IntCallback)(int value);
typedef void (__cdecl *Rva008D3860PlayCallback)(void *handle, int zero);

void BfmeNode1236List::bfmeProcess1236(void *context, void *ownerArg, int frame)
{
	Rva008D3860Owner *owner = (Rva008D3860Owner *)ownerArg;
	int frameIndex = frame;
	for (int i = 0; i < m_frames04[frameIndex].m_count00; ++i) {
		Rva008D3860Command *command = m_frames04[frameIndex].m_commands04[i];
		if (command->m_kind00 == 8 && command->m_value04 >= 0) {
			((Rva008CCED0BytecodeRunner *)&Rva008AE770TheStack)->run(command->m_payload08, owner, -1);
			((BfmeR1226 *)&Rva008AE770TheStack)->bfmeLine1226((char *)"doFrameControls");
			command->m_value04 = -command->m_value04;
		}
	}

	for (int i = 0; i < m_frames04[frameIndex].m_count00; ++i) {
		Rva008D3860Command *command = m_frames04[frameIndex].m_commands04[i];
		switch (command->m_kind00) {
		case 5:
			if (g_bfmeFlagESP == 0) {
				((Rva008D3860IntCallback)g_bfmeSlot03VB)(command->m_value04);
				g_bfmeFlagESP = 1;
			}
			break;
		case 3: {
			Rva008D3860Descriptor *descriptor = owner->m_state50->m_descriptor0c;
			Rva008D3860LookupView *lookup = &descriptor->m_parent04->m_view08;
			int action = (int)command->m_key0c;
			Rva008D3860ActionRow *row = &descriptor->m_row08;
			int slot = ((Gen_008A06C0 *)lookup)->bfmeIndexOf((void *)action);
			if (slot != -1) {
				action = ((Rva008A1CF0 *)lookup)->rva008A1CF0(slot);
				if (action != -1) {
					Rva008D3860LookupParent *group = (Rva008D3860LookupParent *)
						lookup->m_slots24[slot].m_owner0c->m_group10;
					lookup = &group->m_view08;
					row = &((Rva008D3860ActionSublist **)
						lookup->m_actions00.m_audio10)[action]->m_row08;
				}
			}

			if (row->m_count00 > 0) {
				for (int j = 0; j < row->m_actions04->m_count00; ++j) {
					Rva008D3860Command *nested = row->m_actions04->m_commands04[j];
					if (nested->m_kind00 == 3 && nested->m_key0c != (void *)-1)
						((Rva008A1D80Owner *)lookup)->runImportedInitActions(owner, (int)nested->m_key0c);
				}
			}

			if (action != -1)
				((Rva008A1D80Owner *)lookup)->runImportedInitActions(owner, action);
			((BfmeSubmitter1283 *)context)->rva008BEF00(
				(BfmeDescriptor1288 *)&command->m_value04, (BfmeContext1288 *)owner);
			break;
		}
		case 4:
			((BfmeWrapper1279 *)context)->bfmeForward1279(
				(BfmeInput1279 *)&command->m_value04);
			break;
		case 6: {
			Rva008D3860Descriptor *descriptor = owner->m_state50->m_descriptor0c;
			Rva008D3860Audio **audio = (Rva008D3860Audio **)
				descriptor->m_parent04->m_view08.m_actions00.m_audio10;
			((Rva008D3860PlayCallback)g_bfmeSlot19VB)(audio[command->m_value04]->m_handle08, 0);
			break;
		}
		case 7:
			continue;
		}
	}
}
