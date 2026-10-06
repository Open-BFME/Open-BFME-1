#!/usr/bin/env python3
"""tools/variant_search.py: round loop, parallel scoring, regalloc-only blind phase."""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import variant_search as vs  # noqa: E402

RETAIL = bytes.fromhex("8b442404" "8b4808" "03c8" "c3")     # mov eax,[esp+4]; mov ecx,[eax+8]; add ecx,eax
REGALLOC = bytes.fromhex("8b542404" "8b4a08" "03ca" "c3")   # same with edx
STRUCTURAL = bytes.fromhex("33c0" "c3")


def test_classify():
    assert vs.classify(RETAIL, RETAIL) == "exact"
    assert vs.classify(REGALLOC, RETAIL) == "regalloc"
    assert vs.classify(STRUCTURAL, RETAIL) == "structural"


def test_parse_variants_drops_asm_and_duplicates():
    answer = ("```cpp\nint f(){return 1;}\n```\n```cpp\nint f(){return 1;}\n```\n"
              "```cpp\nint f(){__asm nop}\n```\n```c++\nint f(){return 2;}\n```")
    assert vs.parse_variants(answer, 16) == ["int f(){return 1;}\n", "int f(){return 2;}\n"]


def fake_scorer(table):
    """Scores by lookup: text -> compiled bytes (None = does not compile)."""
    def make(_slot):
        def score(text):
            compiled = table.get(text.strip())
            if compiled is None:
                return {"fitness": -1.0, "exact": False, "class": "compile-error"}
            exact = compiled == RETAIL
            return {"fitness": 1.0 if exact else vs.fitness(compiled, RETAIL), "exact": exact,
                    "class": vs.classify(compiled, RETAIL), "compiled": compiled, "target": RETAIL}
        return score
    return make


def run(tmp_path, table, answers, **kw):
    draft = tmp_path / "draft.cpp"
    draft.write_text("draft", encoding="latin-1")
    prompts = []

    def propose(prompt):
        prompts.append(prompt)
        return answers[min(len(prompts) - 1, len(answers) - 1)]
    result = vs.search(draft, "?f@@YAXXZ", 0x1000, len(RETAIL), model="m", propose=propose,
                       make_scorer=fake_scorer(table), out=tmp_path / "out", jobs=4, **kw)
    return result, prompts


def fenced(*texts):
    return "\n".join(f"```cpp\n{t}\n```" for t in texts)


def test_model_round_reaches_exact(tmp_path):
    table = {"draft": STRUCTURAL, "good": RETAIL, "meh": STRUCTURAL + b"\x90"}
    result, prompts = run(tmp_path, table, [fenced("meh", "broken", "good")], n=8)
    assert result["exact"] and result["stop"] == "exact"
    assert len(prompts) == 1 and "xor eax, eax" in prompts[0]  # the diff reached the model
    assert (tmp_path / "out" / "win.cpp").read_text(encoding="latin-1").strip() == "good"
    assert result["runner_model"] == "m"


def test_round_cap(tmp_path):
    table = {"draft": STRUCTURAL}
    result, prompts = run(tmp_path, table, [fenced("nope")], n=8, rounds=3)
    assert len(prompts) == 3 and not result["exact"] and result["stop"] == "round cap"


def test_regalloc_only_goes_blind_under_a_cap(tmp_path):
    table = {"draft": REGALLOC}
    result, prompts = run(tmp_path, table, [fenced("x")], n=8, permute_trials=10)
    assert prompts == []  # no model round is spent on register choice
    assert result["blind_trials"] <= 10 and result["stop"] == "regalloc: blind trial cap"


def test_n_band_enforced(tmp_path):
    with pytest.raises(ValueError):
        run(tmp_path, {"draft": STRUCTURAL}, [""], n=4)
