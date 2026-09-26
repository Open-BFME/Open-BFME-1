class BfmeStrXD
{
public:
	int bfmeCmpXD(const BfmeStrXD &o) const;
};

const BfmeStrXD &bfmeMedianXD(const BfmeStrXD &a, const BfmeStrXD &b, const BfmeStrXD &c)
{
	if (a.bfmeCmpXD(b) < 0)
		if (b.bfmeCmpXD(c) < 0)
			return b;
		else if (a.bfmeCmpXD(c) < 0)
			return c;
		else
			return a;
	else if (a.bfmeCmpXD(c) < 0)
		return a;
	else if (b.bfmeCmpXD(c) < 0)
		return c;
	else
		return b;
}
