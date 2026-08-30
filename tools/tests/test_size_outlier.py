"""size_outlier flags a body that FORWARDS where its siblings IMPLEMENT.

Both halves of the rule earn their place, and the tests say why: size alone
flags 104 rows on the live ledger because a virtual method may legitimately have
a tiny override, and the tail-jump test alone would flag every honest thunk in
the tree. Together they give 14.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import size_outlier  # noqa: E402


def _row(name, size, rva="0x00001000"):
    return {"name": name, "export_rva": "", "target_rva": rva,
            "target_size": str(size), "source": "a.cpp", "status": "matched", "notes": ""}


def _family(small_size, small_name="?f@Small@@QAEXXZ"):
    """Three real implementations and one candidate, all one method name."""
    return [_row("?f@Big1@@QAEXXZ", 260), _row("?f@Big2@@QAEXXZ", 263),
            _row("?f@Big3@@QAEXXZ", 261), _row(small_name, small_size)]


JMP_REL32 = b"\x90" * 3 + b"\xe9\x00\x00\x00\x00"          # ends in E9 rel32
VTABLE_JMP = b"\x8b\x01\xff\x60\x0c"                        # mov eax,[ecx]; jmp [eax+0xC]
PLAIN_RET = b"\x33\xc0\xc3\x90\x90"                         # xor eax,eax; ret


def _read(body_for_small):
    return lambda rva, size: body_for_small if size < 100 else b"\x90" * size


def test_a_forwarder_among_implementations_is_flagged():
    """The reverseAnimateWindow case: five bytes of vtable dispatch where the
    family is 260."""
    got = list(size_outlier.outliers(_family(5), _read(VTABLE_JMP)))
    assert len(got) == 1
    median, size, method, cls, _ = got[0]
    assert (size, method, cls) == (5, "f", "Small")
    assert median >= size * size_outlier.RATIO


def test_a_small_body_that_RETURNS_is_left_alone():
    """A virtual method may legitimately have a tiny override. Size alone flags
    104 rows on the live ledger; this is why the tail-jump half exists."""
    assert list(size_outlier.outliers(_family(5), _read(PLAIN_RET))) == []


def test_an_e9_tail_jump_counts_too():
    assert list(size_outlier.outliers(_family(8), _read(JMP_REL32)))


def test_a_forwarder_the_SAME_size_as_its_family_is_not_an_outlier():
    """The tail-jump test alone would flag every honest thunk in the tree. The
    claim is only interesting when the siblings are much bigger."""
    assert list(size_outlier.outliers(_family(200), _read(VTABLE_JMP))) == []


def test_a_family_of_trivial_accessors_says_nothing():
    """Three 8-byte getters and a 2-byte one is not evidence of anything, so the
    median floor drops the whole family before the ratio is even considered."""
    rows = [_row("?g@A@@QAEXXZ", 8), _row("?g@B@@QAEXXZ", 9),
            _row("?g@C@@QAEXXZ", 8), _row("?g@D@@QAEXXZ", 2)]
    assert list(size_outlier.outliers(rows, _read(VTABLE_JMP))) == []


def test_two_classes_are_not_a_family():
    """A median needs a family. One big implementation and one small forwarder
    is a pair, and a pair has no majority to be an outlier from."""
    rows = [_row("?f@Big1@@QAEXXZ", 260), _row("?f@Small@@QAEXXZ", 5)]
    assert list(size_outlier.outliers(rows, _read(VTABLE_JMP))) == []


def test_tail_jump_ignores_a_jump_in_the_middle():
    """A jump in the middle is control flow; a jump at the end is delegation."""
    assert not size_outlier.tail_jumps(b"\xe9\x00\x00\x00\x00" + b"\x90" * 40)
    assert size_outlier.tail_jumps(b"\x90" * 40 + b"\xe9\x00\x00\x00\x00")
