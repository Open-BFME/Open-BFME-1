class Rva00436730StrideDifference {
public:
    static int difference(const int *left, const int *right);
};

int Rva00436730StrideDifference::difference(const int *left, const int *right)
{
    return (right[0] - left[0]) >> 3;
}
