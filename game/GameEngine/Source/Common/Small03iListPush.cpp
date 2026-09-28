// Retail 0x00942E80 head-links a node into the word-list: the new node's
// word takes the old head word and the head word takes the new node.
// Returning the node keeps it in eax across retail's final store, so no
// trailing move is emitted. The 23-byte dump extent is a mis-carve: the
// body ends at the ret at +0x0E, and the 8 bytes at 0x00942E90 are a
// separate thiscall dtor body seating vtable 0x0113CEB0 (cf. the landed
// ??1SimpleSceneIterator@@UAE@XZ at 0x00943CE0).
// IDENTITY IS NOT RECOVERED: the owner keeps its address token.
void * __cdecl Rva00942E80Push(void *list, void *node)
{
	void *head = *(void **)list;
	*(void **)node = head;
	*(void **)list = node;
	return node;
}
