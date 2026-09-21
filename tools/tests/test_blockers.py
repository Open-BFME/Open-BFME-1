"""blocker= tags share one vocabulary, so a shared problem can be clustered."""
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import blockers  # noqa: E402


def test_spellings_of_one_problem_share_a_family():
    for tag in ("compiler-register-schedule", "register-role-allocation", "compiler-register-coloring",
                "ntohl-register-schedule", "source-sourceObject-register-allocation"):
        assert blockers.canonical(tag) == "regalloc", tag
    assert blockers.canonical("unwind-funclet") == "eh"
    assert blockers.canonical("compiler-stack-slot-allocation") == "stack-slot"
    assert blockers.canonical("path-vector-frame-layout") == "stack-slot"   # first family wins
    assert blockers.canonical("no-new-source-lever") == "no-lever"
    assert blockers.canonical("MSVC") == "toolchain"
    assert blockers.canonical("something-nobody-listed") == "other"


def test_normalise_keeps_the_detail_and_is_idempotent():
    line = "t=25min blocker=unwind-funclet second try blocker=MSVC run=abc"
    once = blockers.normalise(line)
    assert once == "t=25min blocker=eh/unwind-funclet second try blocker=toolchain/MSVC run=abc"
    assert blockers.normalise(once) == once
    assert blockers.families(once) == ["eh", "toolchain"]
    assert blockers.families(line) == ["eh", "toolchain"]      # old rows classify when read


def test_text_that_only_mentions_the_word_is_left_alone():
    line = "the unblocker=foo token and noblocker= are not tags"
    assert blockers.normalise(line) == line
    assert blockers.families(line) == []


def test_every_family_name_is_its_own_canonical_form():
    for name in blockers.NAMES:
        assert blockers.canonical(name) == name
        assert blockers.canonical(name + "/free text detail") == name
