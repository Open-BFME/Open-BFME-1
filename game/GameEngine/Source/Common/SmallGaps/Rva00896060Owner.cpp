// ??1Rva00896060Owner@@QAE@XZ
class Rva00893960List
{
public:
	void *head;
	void clear();
	~Rva00893960List() { clear(); }
};

extern void d_00895d30();

class Rva00896060Owner : public Rva00893960List
{
public:
	~Rva00896060Owner();
};

Rva00896060Owner::~Rva00896060Owner()
{
	typedef void (Rva00896060Owner::*Fn)(void *);
	union
	{
		void (*plain)();
		Fn member;
	} target;
	target.plain = d_00895d30;
	while (head)
	{
		void *arg = (char *)(*(void **)head) + 4;
		(this->*target.member)(arg);
	}
}
