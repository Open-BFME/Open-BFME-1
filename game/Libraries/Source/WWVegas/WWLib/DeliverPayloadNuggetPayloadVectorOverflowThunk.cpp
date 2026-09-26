struct DeliverPayloadNugget
{
	struct Payload
	{
	};
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
};

class DeliverPayloadNuggetPayloadInsertOverflowShim
{
public:
	void insert_overflow(DeliverPayloadNugget::Payload *pos, const DeliverPayloadNugget::Payload &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<DeliverPayloadNugget::Payload, allocator<DeliverPayloadNugget::Payload> >::_M_insert_overflow(
	DeliverPayloadNugget::Payload *pos, const DeliverPayloadNugget::Payload &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((DeliverPayloadNuggetPayloadInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
