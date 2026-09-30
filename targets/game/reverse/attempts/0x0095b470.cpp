// ?method@Rva0095B470@@QAEHI@Z
// partial score=0.9845 date=2026-09-30
struct Rva0095B470 {
 unsigned int m_00,m_04,m_08;
 int m_0c,m_10,m_14;
 unsigned int *m_18;
 int method(unsigned int value);
};
int Rva0095B470::method(unsigned int value)
{
 unsigned int *data = m_18;
 int index = m_14;
 if (value >= (data[index] & 0x7fffffffU)) return index;
 int stride = m_0c;
 int left = 0;
 int right = m_10 - 2;
 for (;;) {
  int mid = (right + left) / 2;
  unsigned int *packet = data + stride * mid;
  if (value < (*packet & 0x7fffffffU)) {right = mid; continue;}
  if (value < (packet[stride] & 0x7fffffffU)) return packet-data;
  if (left ^ mid) {left = mid; continue;}
  ++left;
 }
}
