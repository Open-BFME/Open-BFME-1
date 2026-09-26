// cl: /DNDEBUG /MD /EHsc
struct S3Elem009F3050 { int m_value; float m_key; };
struct S3Less009F3050 {
 bool operator()(const S3Elem009F3050 &left, const S3Elem009F3050 &right) const
 { return left.m_key < right.m_key; }
};
void Gen009F3050(S3Elem009F3050 *first, S3Elem009F3050 *last,
 S3Elem009F3050 *valueType, S3Less009F3050 comp);
void Rva009F32E0UnguardedInsertionSort(S3Elem009F3050 *first,
 S3Elem009F3050 *last, S3Less009F3050 comp)
{
 Gen009F3050(first, last, (S3Elem009F3050 *)0, comp);
}

struct S3Elem009F30B0 { int m_value; float m_key; };
struct S3Greater009F30B0 {
 bool operator()(const S3Elem009F30B0 &left, const S3Elem009F30B0 &right) const
 { return left.m_key > right.m_key; }
};
void Gen009F30B0(S3Elem009F30B0 *first, S3Elem009F30B0 *last,
 S3Elem009F30B0 *valueType, S3Greater009F30B0 comp);
void Rva009F3360UnguardedInsertionSort(S3Elem009F30B0 *first,
 S3Elem009F30B0 *last, S3Greater009F30B0 comp)
{
 Gen009F30B0(first, last, (S3Elem009F30B0 *)0, comp);
}
