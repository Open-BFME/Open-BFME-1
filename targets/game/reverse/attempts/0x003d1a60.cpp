// ?d_003d1a60@@YAXXZ
// partial score=0.16 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x003D1A60 is the update pass over the two pointer vectors in the
// 0x3c-byte sound-key record.  The owner/method identity is not proved by the
// available evidence, so the class keeps the body address in its name.
//
// The field names below are deliberately limited to the witnessed offsets:
// the map thresholds and hand-off word, the element's event/rank/ref/tie
// fields, and the two pointer vectors.  All calls remain on the ILT or pinned
// contracts printed by tools/callees.py.

#define _M_insert_overflow j_00028e2a
#include <vector>
#undef _M_insert_overflow

class AsciiString
{
public:
	void *m_data;
};

struct Coord3D
{
	float x, y, z;
};

class Rva003D1A60AudioEvent
{
public:
	virtual void scalarDeletingDestructor(unsigned int flags) = 0;

	char m_pad04[0x0c];
	unsigned int m_handle;
};

struct Rva003D1A60Element
{
	char m_head[0x0c];
	void *m_event;
	Rva003D1A60Element *m_nodes[8];
	int m_rank;
	int m_handOff;
	char m_refs;
	char m_tie;
	char m_tail[2];
};

struct Rva003D1A60Pair
{
	void *m_releasedEvent;
	Rva003D1A60Element *m_element;
};

typedef _STL::vector<Rva003D1A60Pair,
	_STL::allocator<Rva003D1A60Pair> > Rva003D1A60PairBase;

class Rva003D1A60PairVector : public Rva003D1A60PairBase
{
public:
	using Rva003D1A60PairBase::_M_start;
	using Rva003D1A60PairBase::_M_finish;
	using Rva003D1A60PairBase::_M_end_of_storage;
};

struct Rva003D1A60PointerVector
{
	Rva003D1A60Element **m_start;
	Rva003D1A60Element **m_finish;
	Rva003D1A60Element **m_endOfStorage;

	void append(Rva003D1A60Element *const &value);
};

struct Rva003D1A60Map
{
	char m_head[0x8c];
	int m_startThreshold;
	int m_stopThreshold;
	unsigned short m_handOffModeDuration;
};

extern void j_000028c4(void);
extern void j_000049ef9(void);
extern void j_000058fd(void);
extern void j_0000af10(void);
extern void j_00010d93(void);
extern void j_00016b21(void);
extern void j_00026ebd(void);
extern void j_00026f35(void);
extern void j_00028e2a(void);
extern void j_00034d7e(void);
extern void j_00036a9d(void);
extern void j_0003f88c(void);
extern void j_00040a52(void);
extern void j_0004327f(void);
extern void j_00047b27(void);
extern void j_0004941d(void);

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(
	void *destination, const void *source, unsigned int bytes);

extern "C" unsigned char bfmeVftBTB[];

class Rva003D1A60AudioStorage
{
public:
	__forceinline Rva003D1A60AudioStorage(const AsciiString &name,
		const Coord3D *position, int extra)
	{
		typedef void (Rva003D1A60AudioStorage::*Construct)(
			const AsciiString &, const Coord3D *, int);
		union
		{
			void (*raw)(void);
			Construct member;
		} call;
		call.raw = j_0004941d;
		(this->*call.member)(name, position, extra);
	}

	__forceinline Rva003D1A60AudioStorage(
		const Rva003D1A60AudioStorage &other)
	{
		typedef void (Rva003D1A60AudioStorage::*Construct)(
			const Rva003D1A60AudioStorage &);
		union
		{
			void (*raw)(void);
			Construct member;
		} call;
		call.raw = j_00047b27;
		(this->*call.member)(other);
	}

	__forceinline ~Rva003D1A60AudioStorage()
	{
		typedef void (Rva003D1A60AudioStorage::*Destroy)();
		union
		{
			void (*raw)(void);
			Destroy member;
		} call;
		call.raw = j_00026f35;
		(this->*call.member)();
	}

	char m_data[0x70];
};

class Rva003D1A60OwnedBase
{
public:
	Rva003D1A60OwnedBase() : m_vft(bfmeVftBTB) {}

	void *m_vft;
};

class Rva003D1A60Owned : public Rva003D1A60OwnedBase
{
public:
	Rva003D1A60Owned(const Rva003D1A60AudioStorage &audio) : m_audio(audio) {}

	Rva003D1A60AudioStorage m_audio;
};

struct Rva003D1A60FalseType
{
};

void Rva003D1A60PointerVector::append(
	Rva003D1A60Element *const &value)
{
	Rva003D1A60Element **finish = m_finish;
	if (finish != m_endOfStorage)
	{
		if (finish != 0)
			*finish = value;
		m_finish = finish + 1;
	}
	else
	{
		typedef void (Rva003D1A60PointerVector::*Insert)(
			Rva003D1A60Element **, Rva003D1A60Element *const &,
			const Rva003D1A60FalseType &, unsigned int, bool);
		union
		{
			void (*raw)(void);
			Insert member;
		} call;
		Rva003D1A60FalseType tag;
		call.raw = j_000028c4;
		(this->*call.member)(finish, value, tag, 1, true);
	}
}

struct Rva003D1A60BfmeCmp
{
	char m_raw;
};

class Rva003D1A60BfmeVector
{
public:
	void insert(Rva003D1A60Element **where,
		Rva003D1A60Element **value);

	Rva003D1A60Element **m_start;
	Rva003D1A60Element **m_finish;
	Rva003D1A60Element **m_endOfStorage;
};

void ** __cdecl bfmeLowerRQ(void **begin, void **end, void **key,
	Rva003D1A60BfmeCmp compare, int spare);

static __forceinline void Rva003D1A60InsertFirst(
	Rva003D1A60PointerVector *first, Rva003D1A60Element *value)
{
	Rva003D1A60Element *key = value;
	Rva003D1A60BfmeCmp compare;
	compare.m_raw = 0;
	void **found = bfmeLowerRQ((void **)first->m_start,
		(void **)first->m_finish, (void **)&key, compare, 0);
	if (found == (void **)first->m_finish ||
		*(Rva003D1A60Element **)found != key)
	{
		((Rva003D1A60BfmeVector *)first)->insert(
			(Rva003D1A60Element **)found, &key);
	}
}

static __forceinline void Rva003D1A60ReleaseSlots(
	Rva003D1A60Element *element, void **released)
{
	typedef void *(Rva003D1A60Element::*Release)();
	union
	{
		void (*raw)(void);
		Release member;
	} call;
	call.raw = j_000049ef9;
	*released = (element->*call.member)();
}

static __forceinline void Rva003D1A60Release(
	Rva003D1A60Element *element)
{
	typedef void (Rva003D1A60Element::*Release)();
	union
	{
		void (*raw)(void);
		Release member;
	} call;
	call.raw = j_00036a9d;
	(element->*call.member)();
}

static __forceinline void Rva003D1A60GetPosition(
	Rva003D1A60Element *element, Coord3D *position)
{
	typedef void (Rva003D1A60Element::*GetPosition)(Coord3D *);
	union
	{
		void (*raw)(void);
		GetPosition member;
	} call;
	call.raw = j_0004327f;
	(element->*call.member)(position);
}

static __forceinline void Rva003D1A60UpdateElement(
	Rva003D1A60Element *element)
{
	typedef void (Rva003D1A60Element::*Update)();
	union
	{
		void (*raw)(void);
		Update member;
	} call;
	call.raw = j_00026ebd;
	(element->*call.member)();
}

static __forceinline void Rva003D1A60SetPlayingHandle(
	Rva003D1A60AudioStorage *audio, unsigned int handle)
{
	typedef void (Rva003D1A60AudioStorage::*SetHandle)(unsigned int);
	union
	{
		void (*raw)(void);
		SetHandle member;
	} call;
	call.raw = j_00040a52;
	(audio->*call.member)(handle);
}

static __forceinline void Rva003D1A60ReservePairs(
	Rva003D1A60PairVector *pairs, unsigned int count)
{
	typedef void (Rva003D1A60PairVector::*Reserve)(unsigned int);
	union
	{
		void (*raw)(void);
		Reserve member;
	} call;
	call.raw = j_0000af10;
	(pairs->*call.member)(count);
}

struct Rva003D1A60Q4Compare
{
	char m_raw;
};

static __forceinline void Rva003D1A60IntroSort(
	Rva003D1A60Element **begin, Rva003D1A60Element **end,
	int depth, Rva003D1A60Q4Compare compare)
{
	typedef void (__cdecl *IntroSort)(
		int *, int *, int *, int, Rva003D1A60Q4Compare);
	union
	{
		void (*raw)(void);
		IntroSort typed;
	} call;
	call.raw = j_00010d93;
	call.typed((int *)begin, (int *)end, (int *)0, depth, compare);
}

static __forceinline void Rva003D1A60InsertionSort(
	Rva003D1A60Element **begin, Rva003D1A60Element **end,
	Rva003D1A60Q4Compare compare)
{
	typedef void (__cdecl *InsertionSort)(
		int *, int *, Rva003D1A60Q4Compare);
	union
	{
		void (*raw)(void);
		InsertionSort typed;
	} call;
	call.raw = j_0003f88c;
	call.typed((int *)begin, (int *)end, compare);
}

static __forceinline void Rva003D1A60UnguardedInsertionSort(
	Rva003D1A60Element **begin, Rva003D1A60Element **end,
	Rva003D1A60Q4Compare compare)
{
	typedef void (__cdecl *UnguardedInsertionSort)(
		int *, int *, int *, Rva003D1A60Q4Compare);
	union
	{
		void (*raw)(void);
		UnguardedInsertionSort typed;
	} call;
	call.raw = j_000058fd;
	call.typed((int *)begin, (int *)end, (int *)0, compare);
}

class Rva005A00B0AudioClient
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual unsigned int addAudioEvent(Rva003D1A60AudioStorage *event) = 0;
	virtual void slot18() = 0;
	virtual void stopAudioEvent(unsigned int handle) = 0;
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class Rva003D1A60
{
public:
	void process();

	char m_keyMap[0x0c];
	AsciiString m_headerKey;
	Rva003D1A60Element *m_groups[4];
	Rva003D1A60Map *m_owner;
	Rva003D1A60PointerVector m_second;
	Rva003D1A60PointerVector m_first;
};

void Rva003D1A60::process()
{
	Rva003D1A60 *self = this;
	int lowestRank = 0;
	int startThreshold = self->m_owner->m_startThreshold;
	int stopThreshold = self->m_owner->m_stopThreshold;

	if (self->m_first.m_start != self->m_first.m_finish)
	{
		Rva003D1A60PairVector pending;
		Rva003D1A60ReservePairs(&pending,
			(unsigned int)(self->m_first.m_finish - self->m_first.m_start));

		for (Rva003D1A60Element **it = self->m_first.m_start;
			it != self->m_first.m_finish; ++it)
		{
			Rva003D1A60Element *element = *it;
			if (element->m_event != 0 && element->m_rank < lowestRank)
			{
				Rva003D1A60Pair value;
				Rva003D1A60ReleaseSlots(element,
					&value.m_releasedEvent);
				value.m_element = element;
				pending.push_back(value);

				Rva003D1A60Element **secondEnd = self->m_second.m_finish;
				Rva003D1A60Element **second = self->m_second.m_start;
				if (second != secondEnd)
				{
					while (*second != element)
					{
						second += 1;
						if (second == secondEnd)
							break;
					}

					if (second != secondEnd)
					{
						Rva003D1A60Element **source = second + 1;
						if (secondEnd != source)
							BfmeMemMove(second, source,
								(unsigned int)((char *)secondEnd -
									(char *)source));
						self->m_second.m_finish = secondEnd - 1;
					}
				}
			}
		}

		Rva003D1A60Element *best = 0;
		Rva003D1A60Pair *pendingIt = pending._M_start;
		Rva003D1A60Pair *pendingEnd = pending._M_finish;
		if (pendingIt != pendingEnd)
		{
			int offset = 0x10;
			do
			{
				Rva003D1A60Element *candidate =
					*(Rva003D1A60Element **)(
						(char *)pendingIt->m_element + offset);
				if (candidate != 0 && candidate->m_rank >= startThreshold &&
					candidate->m_refs <= 0)
				{
					if (best == 0)
					{
						best = candidate;
					}
					else if (candidate->m_rank > best->m_rank)
					{
						Rva003D1A60InsertFirst(&self->m_first, best);
						best = candidate;
					}
					else if (candidate->m_rank != best->m_rank)
					{
						Rva003D1A60InsertFirst(&self->m_first, candidate);
						best = candidate;
					}
					else if (candidate->m_tie < best->m_tie)
					{
						Rva003D1A60InsertFirst(&self->m_first, best);
						best = candidate;
					}
				}

				offset += 4;
			}
			while (offset < 0x30);

			if (best != 0)
			{
				unsigned short handOff = self->m_owner->m_handOffModeDuration;
				Rva003D1A60Pair *pair = pending._M_start;
				Rva003D1A60Release(best);
				best->m_event = pair->m_releasedEvent;
				best->m_handOff = (int)handOff;

				for (int index = 0; index < 8; ++index)
				{
					Rva003D1A60Element *node = best->m_nodes[index];
					if (node != 0)
						++node->m_refs;
				}
				++best->m_refs;
				self->m_second.append(best);

				for (Rva003D1A60Pair *release = pending._M_start;
					release != pending._M_finish; ++release)
				{
					Rva003D1A60AudioEvent *event =
						(Rva003D1A60AudioEvent *)release->m_releasedEvent;
					if (event != 0)
					{
						TheAudioClientUpdate->stopAudioEvent(
							event->m_handle);
						event->scalarDeletingDestructor(1);
					}
				}
			}
		}

		Rva003D1A60Element **first = self->m_first.m_start;
		Rva003D1A60Element **last = self->m_first.m_finish;
		int count = (int)(last - first);
		Rva003D1A60Q4Compare compare;
		compare.m_raw = 0;
		if (count != 0)
		{
			int depth = 0;
			int remaining = count;
			while (remaining != 1)
			{
				remaining >>= 1;
				++depth;
			}
			Rva003D1A60IntroSort(first, last, depth, compare);
			if (count > 0x10)
			{
				Rva003D1A60InsertionSort(first, first + 0x10, compare);
				Rva003D1A60UnguardedInsertionSort(
					first + 0x10, last, compare);
			}
			else
			{
				Rva003D1A60InsertionSort(first, last, compare);
			}
		}

		for (Rva003D1A60Element **it = self->m_first.m_start;
			it != self->m_first.m_finish; ++it)
		{
			Rva003D1A60Element *element = *it;
			if (element->m_rank >= stopThreshold && element->m_refs <= 0)
			{
				Coord3D position;
				Rva003D1A60GetPosition(element, &position);
				void *raw = ::operator new(0x74);
				Rva003D1A60Owned *owned = 0;
				if (raw != 0)
				{
					Rva003D1A60AudioStorage audio(
						self->m_headerKey, &position, 0);
					owned = new (raw) Rva003D1A60Owned(audio);
				}

				if (owned != 0)
				{
					element->m_event = owned;
					element->m_handOff = 0;
					Rva003D1A60SetPlayingHandle(
						&owned->m_audio,
						TheAudioClientUpdate->addAudioEvent(&owned->m_audio));
					Rva003D1A60Release(element);
					for (int index = 0; index < 8; ++index)
					{
						Rva003D1A60Element *node = element->m_nodes[index];
						if (node != 0)
							++node->m_refs;
					}
					++element->m_refs;
					self->m_second.append(element);
				}
			}
		}

		// Retail's post-pass erase is the vector range-to-end operation; spelling
		// its resulting empty range explicitly keeps the witnessed two pointers.
		self->m_first.m_finish = self->m_first.m_start;
	}

	for (Rva003D1A60Element **it = self->m_second.m_start;
		it != self->m_second.m_finish; ++it)
		Rva003D1A60UpdateElement(*it);
}
