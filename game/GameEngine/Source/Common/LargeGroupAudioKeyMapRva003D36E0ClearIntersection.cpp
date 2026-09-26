// cl: /DNDEBUG /MD /EHsc
// Address-derived intersection removal over the global audio-key tree.
namespace _STL
{
struct _Rb_tree_node_base
{
    bool m_color;
    _Rb_tree_node_base *m_parent;
    _Rb_tree_node_base *m_left;
    _Rb_tree_node_base *m_right;
};
template <class Dummy> class _Rb_global
{
public:
    static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};
}
struct LargeGroupAudioKeyRecord : public _STL::_Rb_tree_node_base
{
    unsigned int m_bfmeUnmodelled10;
    unsigned int m_key;
    unsigned int m_useCount;
};
class LargeGroupAudioKeyMap
{
public:
    void rva003D36E0ClearIntersection(const LargeGroupAudioKeyMap &other);
    unsigned int *m_wordsBegin;
    unsigned int *m_wordsEnd;
    unsigned int *m_wordsCapacity;
};
extern LargeGroupAudioKeyRecord *g_lgaKeyRecordSentinel;
void LargeGroupAudioKeyMap::rva003D36E0ClearIntersection(const LargeGroupAudioKeyMap &other)
{
    int wordCount = m_wordsEnd - m_wordsBegin;
    LargeGroupAudioKeyRecord *record = (LargeGroupAudioKeyRecord *)g_lgaKeyRecordSentinel->m_left;
    LargeGroupAudioKeyRecord *sentinel = g_lgaKeyRecordSentinel;
    while (record != sentinel)
    {
        unsigned int bit = record->m_key;
        int word = bit >> 5;
        unsigned int mask = 1 << (bit & 31);
        if (wordCount > word &&
            (other.m_wordsBegin[word] & mask) &&
            (m_wordsBegin[word] & mask))
        {
            --record->m_useCount;
            m_wordsBegin[word] &= ~mask;
        }
        record = (LargeGroupAudioKeyRecord *)_STL::_Rb_global<bool>::_M_increment(record);
    }
}
