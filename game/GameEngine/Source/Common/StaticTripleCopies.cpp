// cl: /O2 /MD

struct RvaTriple
{
    unsigned first;
    unsigned second;
    unsigned third;
};

extern RvaTriple bfmeRva012B5074Source;
extern RvaTriple bfmeRva012B5080FirstCopy;
extern RvaTriple bfmeRva012B5068SecondCopy;
extern RvaTriple bfmeRva012B50D4Source;
extern RvaTriple bfmeRva012B50E0FirstCopy;
extern RvaTriple bfmeRva012B50C8SecondCopy;
extern RvaTriple bfmeRva012B5134Source;
extern RvaTriple bfmeRva012B5140FirstCopy;
extern RvaTriple bfmeRva012B5128SecondCopy;
extern RvaTriple bfmeRva012B518CSource;
extern RvaTriple bfmeRva012B5198FirstCopy;
extern RvaTriple bfmeRva012B5180SecondCopy;

void bfmeRva00C6B500CopyTripleTwice()
{
    unsigned first = bfmeRva012B5074Source.first;
    unsigned second = bfmeRva012B5074Source.second;
    unsigned third = bfmeRva012B5074Source.third;
    bfmeRva012B5080FirstCopy.first = first;
    bfmeRva012B5080FirstCopy.second = second;
    bfmeRva012B5080FirstCopy.third = third;
    bfmeRva012B5068SecondCopy.first = first;
    bfmeRva012B5068SecondCopy.second = second;
    bfmeRva012B5068SecondCopy.third = third;
}

void bfmeRva00C6B550CopyTripleTwice()
{
    unsigned first = bfmeRva012B50D4Source.first;
    unsigned second = bfmeRva012B50D4Source.second;
    unsigned third = bfmeRva012B50D4Source.third;
    bfmeRva012B50E0FirstCopy.first = first;
    bfmeRva012B50E0FirstCopy.second = second;
    bfmeRva012B50E0FirstCopy.third = third;
    bfmeRva012B50C8SecondCopy.first = first;
    bfmeRva012B50C8SecondCopy.second = second;
    bfmeRva012B50C8SecondCopy.third = third;
}

void bfmeRva00C6B5A0CopyTripleTwice()
{
    unsigned first = bfmeRva012B5134Source.first;
    unsigned second = bfmeRva012B5134Source.second;
    unsigned third = bfmeRva012B5134Source.third;
    bfmeRva012B5140FirstCopy.first = first;
    bfmeRva012B5140FirstCopy.second = second;
    bfmeRva012B5140FirstCopy.third = third;
    bfmeRva012B5128SecondCopy.first = first;
    bfmeRva012B5128SecondCopy.second = second;
    bfmeRva012B5128SecondCopy.third = third;
}

void bfmeRva00C6B5F0CopyTripleTwice()
{
    unsigned first = bfmeRva012B518CSource.first;
    unsigned second = bfmeRva012B518CSource.second;
    unsigned third = bfmeRva012B518CSource.third;
    bfmeRva012B5198FirstCopy.first = first;
    bfmeRva012B5198FirstCopy.second = second;
    bfmeRva012B5198FirstCopy.third = third;
    bfmeRva012B5180SecondCopy.first = first;
    bfmeRva012B5180SecondCopy.second = second;
    bfmeRva012B5180SecondCopy.third = third;
}
