"""Callable-loss selection without a retail image, object cache, or git history."""
import json
import os
from pathlib import Path
import subprocess
import sys

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import delta_sources as delta


def row(name, rva, source="Code/Callee.cpp", **changes):
    result = dict(name=name, target_rva=hex(rva), target_size="16",
                  status="matched", source=source, notes="")
    result.update(changes)
    return result


@pytest.fixture
def selection(monkeypatch, tmp_path):
    def configure(old, new, calls, relocations, *, current=True, thunks=None, pins=()):
        monkeypatch.setattr(delta, "ROOT", tmp_path)
        monkeypatch.setattr(delta, "dict_rows_at",
                            lambda spec: old if spec.startswith("old:") else new)
        monkeypatch.setattr(delta, "pins_at", lambda spec: set(pins))
        monkeypatch.setattr(delta.build, "build_call_thunks", lambda: thunks or {})
        monkeypatch.setattr(delta, "call_sites",
                            lambda lost: [(site, target) for site, target in calls
                                          if target in lost])
        monkeypatch.setattr(delta.build, "row_object", lambda r: tmp_path / r["source"])
        monkeypatch.setattr(delta, "object_is_current", lambda source, obj: current)

        def object_rel32(obj):
            source = str(obj.relative_to(tmp_path))
            owners = [r for r in new if r["source"] == source]
            defined = {r["name"]: (1, int(r["target_rva"], 16)) for r in owners}
            return defined, {(1, site + 1): name
                             for site, name in relocations.get(source, [])}
        monkeypatch.setattr(delta, "object_rel32", object_rel32)
    return configure


def test_row_only_loss_selects_untouched_caller(selection):
    callee, caller = row("lost", 0x1000), row("caller", 0x2000, "Code/Caller.cpp")
    selection([callee, caller], [caller], [(0x2000, 0x1000)],
              {"Code/Caller.cpp": [(0x2000, "lost")]})
    assert delta.function_delta_sources("old", "new") == ["Code/Caller.cpp"]


def test_another_name_at_same_address_does_not_preserve_candidate(selection):
    lost, retained = row("lost", 0x1000), row("retained", 0x1000)
    caller = row("caller", 0x2000, "Code/Caller.cpp")
    selection([lost, retained, caller], [retained, caller], [(0x2000, 0x1000)],
              {"Code/Caller.cpp": [(0x2000, "lost")]})
    assert delta.function_delta_sources("old", "new") == ["Code/Caller.cpp"]


def test_only_one_of_two_lost_names_is_supplied_by_retained_pin(selection):
    a, b = row("a", 0x1000), row("b", 0x1000)
    callers = [row("callerA", 0x2000, "Code/A.cpp"),
               row("callerB", 0x2100, "Code/B.cpp")]
    selection([a, b, *callers], callers, [(0x2000, 0x1000), (0x2100, 0x1000)],
              {"Code/A.cpp": [(0x2000, "a")], "Code/B.cpp": [(0x2100, "b")]},
              pins={("a", 0x1000)})
    assert delta.function_delta_sources("old", "new") == ["Code/B.cpp"]


def test_reordered_duplicate_name_loses_previous_effective_body(selection):
    a, b = row("CRC_Memory", 0x1000), row("CRC_Memory", 0x1100)
    caller = row("caller", 0x2000, "Code/Caller.cpp")
    selection([a, b, caller], [b, a, caller], [(0x2000, 0x1100)],
              {"Code/Caller.cpp": [(0x2000, "CRC_Memory")]})
    assert delta.function_delta_sources("old", "new") == ["Code/Caller.cpp"]


def test_pin_loss_uses_last_function_row_not_union():
    rows = [row("f", 0x1000), row("f", 0x1100)]
    assert delta.lost_candidates({("f", 0x1000)}, set(), rows, {}) == {0x1000: {"f"}}


def test_retained_body_expands_only_its_own_thunks():
    thunks = {0x1000: [0x1050], 0x1100: [0x1150]}
    assert delta.lost_candidates({("f", 0x1000), ("f", 0x1100)}, set(),
                                 [row("f", 0x1100)], thunks) == {
                                     0x1000: {"f"}, 0x1050: {"f"}}


def test_retained_thunk_pin_does_not_supply_body():
    assert delta.lost_candidates({("f", 0x1000)}, {("f", 0x1050)}, [],
                                 {0x1000: [0x1050]}) == {0x1000: {"f"}}


def test_lost_ilt_selects_caller_while_other_body_survives(selection):
    callee = row("f", 0x1000)
    callers = [row("a", 0x2000, "Code/A.cpp"), row("b", 0x2100, "Code/B.cpp")]
    selection([callee, *callers], callers, [(0x2000, 0x1050), (0x2100, 0x1150)],
              {"Code/A.cpp": [(0x2000, "f")], "Code/B.cpp": [(0x2100, "f")]},
              pins={("f", 0x1100)}, thunks={0x1000: [0x1050], 0x1100: [0x1150]})
    assert delta.function_delta_sources("old", "new") == ["Code/A.cpp"]


@pytest.mark.parametrize("changes", [dict(notes="new comment"), dict(status="unmatched"),
                                      dict(source="Code/Moved.cpp"),
                                      dict(target_rva="0x00001000"),
                                      dict(notes="object-symbol=other")])
def test_metadata_changes_do_not_scan_callers(monkeypatch, changes):
    old, new = row("f", 0x1000), row("f", 0x1000, **changes)
    monkeypatch.setattr(delta, "dict_rows_at",
                        lambda spec: [old] if spec.startswith("old:") else [new])
    def unexpected_scan(*args):
        pytest.fail("unchanged callable resolution must not scan the image")
    monkeypatch.setattr(delta, "affected_sources", unexpected_scan)
    assert delta.function_delta_sources("old", "new") == [new["source"]]


def test_unmatched_rows_supply_candidates_but_do_not_own_callers(selection):
    callee = row("lost", 0x1000, status="unmatched")
    caller = row("caller", 0x2000, "Code/Caller.cpp", status="unmatched")
    assert delta.lost_candidates({("lost", 0x1000)}, set(), [callee], {}) == {}
    selection([callee, caller], [caller], [(0x2000, 0x1000)],
              {"Code/Caller.cpp": [(0x2000, "lost")]})
    assert delta.function_delta_sources("old", "new") == []


@pytest.mark.parametrize("current,relocation,expected", [
    (False, "other", ["Code/Caller.cpp"]), (True, "other", []),
    (True, "lost", ["Code/Caller.cpp"])])
def test_object_evidence_only_narrows_when_current(selection, current, relocation, expected):
    callee, caller = row("lost", 0x1000), row("caller", 0x2000, "Code/Caller.cpp")
    selection([callee, caller], [caller], [(0x2000, 0x1000)],
              {"Code/Caller.cpp": [(0x2000, relocation)]}, current=current)
    assert delta.function_delta_sources("old", "new") == expected


def test_missing_object_anchor_keeps_caller(selection, monkeypatch):
    callee, caller = row("lost", 0x1000), row("caller", 0x2000, "Code/Caller.cpp")
    selection([callee, caller], [caller], [(0x2000, 0x1000)], {})
    monkeypatch.setattr(delta, "object_rel32", lambda obj: ({}, {}))
    assert delta.function_delta_sources("old", "new") == ["Code/Caller.cpp"]


@pytest.mark.parametrize("state", ["missing", "missing-sidecar", "malformed",
                                   "changed-source", "changed-header", "current"])
def test_actual_object_freshness_check(tmp_path, monkeypatch, state):
    source, header, obj = [tmp_path / name for name in ("a.cpp", "a.h", "a.obj")]
    source.write_text("source")
    header.write_text("header")
    sidecar = tmp_path / "a.deps.json"
    monkeypatch.setattr(delta.build, "_deps_sidecar", lambda path: sidecar)
    if state != "missing":
        obj.touch()
    if state not in {"missing", "missing-sidecar"}:
        sidecar.write_text(json.dumps({"source": delta.build._hash_file(str(source)),
                                      "deps": {str(header): delta.build._hash_file(str(header))}}))
    if state == "malformed":
        sidecar.write_text("{")
    elif state == "changed-source":
        source.write_text("changed source")
    elif state == "changed-header":
        header.write_text("changed header")
    assert delta.object_is_current(source, obj) == (state == "current")


@pytest.mark.parametrize("second_start,second_size,site", [
    (0x2000, "64", 0x2000), (0x2010, "8", 0x2020)])
def test_every_overlapping_owner_is_considered(selection, second_start, second_size, site):
    callee = row("lost", 0x1000)
    a = row("a", 0x2000, "Code/A.cpp", target_size="64")
    b = row("b", second_start, "Code/B.cpp", target_size=second_size)
    selection([callee, a, b], [a, b], [(site, 0x1000)],
              {"Code/A.cpp": [(site, "lost")], "Code/B.cpp": [(site, "other")]})
    assert delta.function_delta_sources("old", "new") == ["Code/A.cpp"]


def test_stale_tu_evidence_keeps_only_exact_affected_row(selection):
    callee = row("lost", 0x1000)
    caller = row("caller", 0x2000, "Code/Shared.cpp")
    sibling = row("unrelated", 0x2100, "Code/Shared.cpp")
    selection([callee, caller, sibling], [caller, sibling], [(0x2000, 0x1000)],
              {}, current=False)
    assert delta.affected_row_indices({("lost", 0x1000)}, set(),
                                      [caller, sibling], "test") == [0]


def test_current_tu_relocation_can_exclude_exact_caller_row(selection):
    callee = row("lost", 0x1000)
    caller = row("caller", 0x2000, "Code/Shared.cpp")
    sibling = row("unrelated", 0x2100, "Code/Shared.cpp")
    selection([callee, caller, sibling], [caller, sibling], [(0x2000, 0x1000)],
              {"Code/Shared.cpp": [(0x2000, "other")]}, current=True)
    assert delta.affected_row_indices({("lost", 0x1000)}, set(),
                                      [caller, sibling], "test") == []


def test_delta_selector_pairs_source_check_with_exact_affected_row(selection, monkeypatch):
    callee = row("lost", 0x1000)
    caller = row("caller", 0x2000, "Code/Shared.cpp")
    sibling = row("unrelated", 0x2100, "Code/Shared.cpp")
    old, new = [callee, caller, sibling], [caller, sibling]
    selection(old, new, [(0x2000, 0x1000)], {}, current=False)
    monkeypatch.setattr(delta, "dict_rows_at",
                        lambda spec: old if spec.startswith("old:") else new)
    assert delta.function_delta_selectors("old", "new") == [
        "row:0x00002000:16:caller", "source:Code/Shared.cpp"]


@pytest.mark.parametrize("hook", ["pre-commit", "pre-push"])
@pytest.mark.parametrize("mode", ["ordinary", "pins"])
@pytest.mark.parametrize("outcome", ["failure", "empty", "source", "many"])
def test_hooks_check_selector_status_before_using_output(tmp_path, hook, mode, outcome):
    """Run the actual hooks; a failing selector emits valid partial output first."""
    source = "Code/Caller With Space.cpp"
    (tmp_path / "Code").mkdir()
    (tmp_path / source).touch()
    bindir = tmp_path / "bin"
    bindir.mkdir()
    scripts = {
        "git": '''import os, sys
a = sys.argv[1:]
if a[:2] == ["rev-parse", "--show-toplevel"]:
    print(os.environ["FIXTURE_ROOT"])
elif a and a[0] == "diff":
    if "--name-only" in a and "--diff-filter=ACMRT" in a:
        print("reverse/functions.csv")
        if os.environ["SELECTOR_MODE"] == "pins": print("reverse/symbols.csv")
    elif "--quiet" in a:
        changed = "--cached" in a or "base" in a
        sys.exit(1 if changed else 0)
''',
        "python3": '''import os, sys
if sys.argv[1] == "tools/delta_sources.py":
    mode = "pins" if "--pins" in sys.argv else "ordinary"
    if mode == os.environ["SELECTOR_MODE"]:
        outcome = os.environ["SELECTOR_OUTCOME"]
        if outcome != "empty":
            if outcome == "many":
                for index in range(240):
                    print("row:0x%08X:16:?caller_%03d_%s@@YAXXZ" %
                          (0x1000 + index, index, "x" * 150))
            else:
                print("source:Code/Caller With Space.cpp")
                print("row:0x00001000:16:?caller@@YAXXZ")
        if outcome == "failure":
            print("selector fixture failed", file=sys.stderr)
            sys.exit(23)
''',
    }
    for name, body in scripts.items():
        path = bindir / name
        path.write_text(f"#!{sys.executable}\n" + body)
        path.chmod(0o755)
    build_script = tmp_path / "build.sh"
    build_script.write_text('''#!/bin/bash
n=0
if [ -f build-count ]; then read -r n < build-count; fi
n=$((n + 1))
printf '%s\\n' "$n" > build-count
printf '%s\\n' "$@" > "build-args-$n"
''')
    build_script.chmod(0o755)
    env = dict(os.environ, PATH=f"{bindir}:{os.environ['PATH']}",
               FIXTURE_ROOT=str(tmp_path), SELECTOR_MODE=mode, SELECTOR_OUTCOME=outcome)
    if hook == "pre-push" and outcome == "many" and mode == "ordinary":
        pass
    elif outcome == "many":
        pytest.skip("many-selector argv exercise targets the pre-push chunker")
    result = subprocess.run(["bash", str(TOOLS.parent / ".githooks" / hook)],
                            input="refs/heads/test local refs/heads/test base\n",
                            text=True, capture_output=True, env=env)
    records = sorted(tmp_path.glob("build-args-*"), key=lambda p: int(p.name.rsplit("-", 1)[1]))
    chunks = [record.read_text().splitlines() for record in records]
    if outcome == "failure":
        assert result.returncode != 0
        assert "selector fixture failed" in result.stderr
        assert "FAILED: delta_sources" in result.stderr
        assert not records
    else:
        assert result.returncode == 0, result.stderr
        if outcome == "source":
            assert set(chunks[0]) == {
                "source:Code/Caller With Space.cpp",
                "row:0x00001000:16:?caller@@YAXXZ"}
        elif outcome == "many":
            assert len(chunks) > 1
            flattened = [selector for chunk in chunks for selector in chunk]
            assert len(flattened) == 240
            assert all(sum(2 * len(selector.encode("utf-8")) + 3
                           for selector in chunk) <= 24000 for chunk in chunks)
            for chunk in chunks:
                command = subprocess.list2cmdline(["p" * 1000, "s" * 1000] + chunk)
                assert len(command.encode("utf-16-le")) // 2 < 32767
        else:
            assert not records
