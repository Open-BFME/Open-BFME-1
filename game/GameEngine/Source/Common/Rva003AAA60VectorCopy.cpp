// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <new>

// Retail 0x003AAA60 copies a vector of 40-byte LivingWorldCampaignManager
// records. The loop calls the matched LivingWorldCampaignManager copy
// constructor at 0x003A86D0 and advances both pointers by 40 bytes.

class LivingWorldCampaignManager
{
public:
	LivingWorldCampaignManager(const LivingWorldCampaignManager &other);
	virtual ~LivingWorldCampaignManager();

	char m_body[0x24];
};

namespace _STL
{
	template <typename T> class allocator
	{
		int m_value;
	};

	template <typename T, typename Alloc> struct _Vector_base
	{
		_Vector_base(unsigned count, const Alloc &alloc);
		~_Vector_base();
		T *m_start;
		T *m_finish;
		T *m_storage;
	};

	template <typename T, typename Alloc = allocator<T> > class vector;

	template <> class vector<LivingWorldCampaignManager,
		allocator<LivingWorldCampaignManager> >
		: public _Vector_base<LivingWorldCampaignManager,
			allocator<LivingWorldCampaignManager> >
	{
	public:
		typedef LivingWorldCampaignManager T;
		typedef _Vector_base<T, allocator<T> > Base;
		typedef allocator<T> allocator_type;

		allocator_type get_allocator() const;
		vector(const vector &other);
	};

	vector<LivingWorldCampaignManager,
		allocator<LivingWorldCampaignManager> >::vector(
		const vector<LivingWorldCampaignManager,
			allocator<LivingWorldCampaignManager> > &other)
		: Base((unsigned)(other.m_finish - other.m_start),
			other.get_allocator())
	{
		T *end = other.m_finish;
		T *source = other.m_start;
		T *destination = m_start;
		while (source != end)
		{
			new (destination) T(*source);
			source++;
			destination++;
		}
		m_finish = destination;
	}
}
