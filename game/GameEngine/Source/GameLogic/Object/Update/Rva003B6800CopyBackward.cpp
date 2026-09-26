// cl: /DNDEBUG /MD /EHsc

class Gen_t_003b6920_p128podSub
{
public:
	Gen_t_003b6920_p128podSub &operator=(const Gen_t_003b6920_p128podSub &other);

private:
	void *m_item;
};

struct Gen_t_003b6920_p128pod
{
	Gen_t_003b6920_p128podSub m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
	int m_4c;
	int m_50;
	int m_54;
	int m_58;
	int m_5c;
	int m_60;
	int m_64;
	int m_68;
	int m_6c;
	int m_70;
	int m_74;
	int m_78;
	int m_7c;
	int m_80;
	int m_84;
	int m_88;
	int m_8c;
	int m_90;
	int m_94;
	int m_98;
	int m_9c;
	int m_a0;
	int m_a4;
	int m_a8;
	int m_ac;
	int m_b0;
	int m_b4;
	int m_b8;
	int m_bc;
	int m_c0;
	int m_c4;
	int m_c8;
	int m_cc;
	int m_d0;
	int m_d4;
	int m_d8;

	Gen_t_003b6920_p128pod &operator=(const Gen_t_003b6920_p128pod &other);
};

Gen_t_003b6920_p128pod &Gen_t_003b6920_p128pod::operator=(
		const Gen_t_003b6920_p128pod &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0c = other.m_0c;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1c = other.m_1c;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2c = other.m_2c;
	m_30 = other.m_30;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_3c = other.m_3c;
	m_40 = other.m_40;
	m_44 = other.m_44;
	m_48 = other.m_48;
	m_4c = other.m_4c;
	m_50 = other.m_50;
	m_54 = other.m_54;
	m_58 = other.m_58;
	m_5c = other.m_5c;
	m_60 = other.m_60;
	m_64 = other.m_64;
	m_68 = other.m_68;
	m_6c = other.m_6c;
	m_70 = other.m_70;
	m_74 = other.m_74;
	m_78 = other.m_78;
	m_7c = other.m_7c;
	m_80 = other.m_80;
	m_84 = other.m_84;
	m_88 = other.m_88;
	m_8c = other.m_8c;
	m_90 = other.m_90;
	m_94 = other.m_94;
	m_98 = other.m_98;
	m_9c = other.m_9c;
	m_a0 = other.m_a0;
	m_a4 = other.m_a4;
	m_a8 = other.m_a8;
	m_ac = other.m_ac;
	m_b0 = other.m_b0;
	m_b4 = other.m_b4;
	m_b8 = other.m_b8;
	m_bc = other.m_bc;
	m_c0 = other.m_c0;
	m_c4 = other.m_c4;
	m_c8 = other.m_c8;
	m_cc = other.m_cc;
	m_d0 = other.m_d0;
	m_d4 = other.m_d4;
	m_d8 = other.m_d8;
	return *this;
}

namespace _STL
{
struct random_access_iterator_tag {};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy_backward(InputIterator first, InputIterator last,
		OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	Distance count = last - first;
	for (; count > 0; --count, ++first, ++result)
		*result = *first;
	return result;
}

template Gen_t_003b6920_p128pod *__copy_backward(
	Gen_t_003b6920_p128pod *, Gen_t_003b6920_p128pod *,
	Gen_t_003b6920_p128pod *, const random_access_iterator_tag &, int *);
}
