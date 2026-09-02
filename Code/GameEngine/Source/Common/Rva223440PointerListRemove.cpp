void __cdecl __stlp_deallocate_small(void *memory, unsigned int bytes);

struct Rva223440Node
{
	Rva223440Node *next;
	Rva223440Node *previous;
	void *value;
};

class Rva223440PointerList
{
public:
	void remove(void *value);

private:
	char gap[0x38];
	Rva223440Node *sentinel;
	int count;
};

void Rva223440PointerList::remove(void *value)
{
	Rva223440Node *end = sentinel;
	Rva223440Node *node = end->next;

	while (node != end) {
		if (node->value == value) {
			Rva223440Node *next = node->next;
			Rva223440Node *previous = node->previous;

			previous->next = next;
			next->previous = previous;
			__stlp_deallocate_small(node, sizeof(Rva223440Node));
			node = next;
			--count;
		} else {
			node = node->next;
		}
	}
}
