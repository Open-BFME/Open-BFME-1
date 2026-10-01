// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BfmeS1238
{
public:
	BfmeS1238 *bfmeAt1238B(int index);
};

struct Rva008AC190Node
{
	int m_kind;
	unsigned m_unused;
	unsigned m_field8;
	union { int m_childCount; Rva008AC190Node *m_second; float m_float0c; };
	union { Rva008AC190Node **m_children; BfmeS1238 *m_index; };
	union { int m_count14; float m_float14; };
	union { Rva008AC190Node **m_children18; float m_float18; };
	union { unsigned m_limit1c; float m_float1c; };
	int m_limit20;
	unsigned m_align24;
	int m_limit28;
	int m_recordCount;
	union { char *m_records; int m_limit30; };
	int m_limit34;
	char m_pad38[4];
	Rva008AC190Node **m_four;
	int m_count40;
	int m_count44;

	int count008AC190() const;
	Rva008AC190Node *select008AC460(int index);
};
class Rva0089CC10Object
{
public:
	int get() const;
};

int Rva008AC190Node::count008AC190() const
{
	int count = 0;
	if ((unsigned)m_children18 < 0xfffff)
		return count;
	switch (m_kind) {
	case 1:
	case 2:
		break;
	case 3:
		if (m_field8 < 0x10000 || (m_field8 & 3) || m_childCount > 0x10000)
			return 0;
		for (int i = 0; i < m_childCount; ++i) {
			Rva008AC190Node *child = m_children[i];
			if ((unsigned)child < 0x10000 || (m_field8 & 3))
				return 0;
			count += child->count008AC190();
		}
		break;
	case 4:
		if (m_float18 > 20000.0f || m_float0c > 20000.0f ||
		    m_float18 > 20000.0f || m_float14 > 20000.0f ||
		    (int)m_limit1c > 0x20000 || m_limit20 < (int)m_limit1c ||
		    (m_align24 & 3) || m_recordCount > 0x10000 || m_limit34 > 0x1000)
			return 0;
		for (int i = 0; i < m_recordCount; ++i) {
			Rva008AC190Node *child = *(Rva008AC190Node **)(m_records + i * 0x44 + 4);
			if (child)
				count += child->count008AC190();
		}
		if (m_four) {
			if (m_four[0])
				count += m_four[0]->count008AC190();
			if (m_four[1])
				count += m_four[1]->count008AC190();
			if (m_four[2])
				count += m_four[2]->count008AC190();
			if (m_four[3])
				count += m_four[3]->count008AC190();
		}
		break;
	case 5:
		if ((int)m_field8 > 0x2000 || (int)m_field8 < 0 ||
		    ((unsigned)m_children & 3) || ((unsigned)m_childCount & 3))
			return 0;
		if (m_children)
			count = ((Rva0089CC10Object *)m_children)->get();
		break;
	case 8:
		if (m_field8 && m_field8 < 0x10000)
			return 0;
		if (m_second && (unsigned)m_second < 0x10000)
			return 0;
		if ((m_field8 & 3) || ((unsigned)m_second & 3))
			return 0;
		if (m_field8)
			count = ((Rva008AC190Node *)m_field8)->count008AC190();
		if (m_second)
			count += m_second->count008AC190();
		break;
	case 9:
		if ((unsigned)m_children18 < 0x10000 || ((unsigned)m_children18 & 3) ||
		    m_count14 > 0x10000 || m_limit28 > 0x1000 ||
		    m_limit30 > 0x1000 || m_limit1c > 0x8000 ||
		    (unsigned)m_limit20 > 0x8000)
			return 0;
		if ((unsigned)m_children18 <= 0xfffff)
			break;
		for (int i = 0; i < m_count14; ++i) {
			Rva008AC190Node *child = m_children18[i];
			if (this == child)
				break;
			count += child->count008AC190();
		}
		break;
	case 6:
	case 7:
	case 10:
	case 11:
	case 12:
		break;
	default:
		return 0;
	}
	return count;
}


Rva008AC190Node *Rva008AC190Node::select008AC460(int initialIndex)
{
	Rva008AC190Node *node = this;
	int index = initialIndex;
	for (;;) {
		switch (node->m_kind) {
		case 3:
			for (int i = 0; i < node->m_childCount; ++i) {
				int n = node->m_children[i]->count008AC190();
				if (index < n) {
					node = node->m_children[i];
					goto next;
				}
				index -= n;
			}
			return 0;
		case 4:
			for (int i = 0; i < node->m_recordCount; ++i) {
				if (*(Rva008AC190Node **)(node->m_records + i * 0x44 + 4)) {
					int n = (*(Rva008AC190Node **)(node->m_records + i * 0x44 + 4))->count008AC190();
					if (index < n) {
						node = *(Rva008AC190Node **)(node->m_records + i * 0x44 + 4);
						goto next;
					}
					index -= n;
				}
			}
			if (node->m_four) {
				if (node->m_four[0]) {
					int n = node->m_four[0]->count008AC190();
					if (index < n) {
						node = node->m_four[0];
						goto next;
					}
					index -= n;
				}
				if (node->m_four[1]) {
					int n = node->m_four[1]->count008AC190();
					if (index < n) {
						node = node->m_four[1];
						goto next;
					}
				}
				if (node->m_four[2]) {
					int n = node->m_four[2]->count008AC190();
					if (index < n) {
						node = node->m_four[2];
						goto next;
					}
				}
				if (node->m_four[3]) {
					int n = node->m_four[3]->count008AC190();
					if (index < n) {
						node = node->m_four[3];
						goto next;
					}
				}
			}
			return 0;
		case 5:
			return (Rva008AC190Node *)node->m_index->bfmeAt1238B(index);
		case 6:
		case 7:
			return 0;
		case 8:
			if (node->m_field8) {
				int n = ((Rva008AC190Node *)node->m_field8)->count008AC190();
				if (index < n) {
					node = (Rva008AC190Node *)node->m_field8;
					goto next;
				}
			}
			index -= ((Rva008AC190Node *)node->m_field8)->count008AC190();
			if (node->m_second) {
				int n = node->m_second->count008AC190();
				if (index < n) {
					node = node->m_second;
					goto next;
				}
			}
			node->m_second->count008AC190();
			return 0;
		case 9:
			for (int i = 0; i < node->m_count14; ++i) {
				if (node == node->m_children18[i])
					return 0;
				int n = node->m_children18[i]->count008AC190();
				if (index < n) {
					node = node->m_children18[i];
					goto next;
				}
				index -= n;
			}
			return 0;
		default:
			return 0;
		}
next:;
	}
}
