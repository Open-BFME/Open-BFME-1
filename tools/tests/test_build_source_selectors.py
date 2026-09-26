"""A full Code path must not also verify its reference twin."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def check_complete_path_and_partial_selectors(tmp_path):
    source = "game/WW3D2/dx8wrapper.cpp"
    twin = "inputs/reference/GeneralsMD/Code/WW3D2/dx8wrapper.cpp"
    rows = [{"source": source, "name": "?Set@DX8Wrapper@@SAXXZ"},
            {"source": twin, "name": "?Reset@DX8Wrapper@@SAXXZ"}]
    for name in (source, twin):
        path = tmp_path / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("// fixture\n")
    with patch.object(build, "ROOT", tmp_path):
        build.complete_source_selector.cache_clear()
        try:
            def selected(selector):
                return [r["source"] for r in rows if build.selector_matches_row(selector, r)]
            for selector in (source, "./" + source, source.replace("/", "\\"), str(tmp_path / source)):
                assert selected(selector) == [source]
            assert selected(twin) == [twin]
            assert selected("dx8wrapper.cpp") == [source, twin]
            assert selected("WW3D2") == [source, twin]
            assert selected("DX8Wrapper") == [source, twin]
            assert selected("?Set@DX8Wrapper") == [source]
            assert selected(rows[0]["name"]) == [source]
            assert selected("missing.cpp") == []
            with patch.object(build, "ensure_case_shims"), \
                 patch.object(build, "verify_source_claims"), \
                 patch.object(build, "verify_functions"), \
                 patch.object(build, "load_function_rows", return_value=rows), \
                 patch.object(build, "verify_string_refs") as strings:
                build.main([source])
                strings.assert_called_once_with([rows[0]])
        finally:
            build.complete_source_selector.cache_clear()


class BuildSourceSelectorTests(unittest.TestCase):
    def test_complete_path_and_partial_selectors(self):
        with tempfile.TemporaryDirectory() as directory:
            check_complete_path_and_partial_selectors(Path(directory))

    def test_exact_row_selector_does_not_expand_to_sibling_rows(self):
        source = "game/Generated.cpp"
        rows = [
            {"source": source, "name": "?same@@YAXXZ", "target_rva": "0x1000",
             "target_size": "5", "status": "matched"},
            {"source": source, "name": "?same@@YAXXZ", "target_rva": "0x2000",
             "target_size": "6", "status": "matched"},
            {"source": source, "name": "?other@@YAXXZ", "target_rva": "0x3000",
             "target_size": "5", "status": "matched"},
        ]
        selector = "row:0x00001000:5:?same@@YAXXZ"
        self.assertEqual([r for r in rows if build.selector_matches_row(selector, r)],
                         [rows[0]])
        with patch.object(build, "ensure_case_shims"), \
             patch.object(build, "verify_source_claims") as source_claims, \
             patch.object(build, "verify_functions") as functions, \
             patch.object(build, "load_function_rows", return_value=rows), \
             patch.object(build, "verify_string_refs") as strings:
            build.main(["source:" + source, selector])
            source_claims.assert_called_once_with(["source:" + source, selector])
            functions.assert_called_once_with([selector], selected_rows=[rows[0]])
            strings.assert_called_once_with([rows[0]])

    def test_malformed_exact_row_selector_fails_closed(self):
        row = {"source": "game/Generated.cpp", "name": "?same@@YAXXZ",
               "target_rva": "0x1000", "target_size": "5"}
        for selector in ("row:0x1000:5:?same@@YAXXZ",
                         "row:0x00001000:not-a-size:?same@@YAXXZ",
                         "row:0x00001000:5:"):
            with self.subTest(selector=selector), self.assertRaises(SystemExit):
                build.selector_matches_row(selector, row)

    def test_unknown_exact_row_is_not_hidden_by_a_valid_source_selector(self):
        rows = [{"source": "game/Generated.cpp", "name": "?same@@YAXXZ",
                 "target_rva": "0x1000", "target_size": "5", "status": "matched"}]
        selectors = ["source:game/Generated.cpp", "row:0x00001000:5:?same@@YAXXZ",
                     "row:0x00009999:5:?missing@@YAXXZ"]
        with patch.object(build, "load_function_rows", return_value=rows), \
             self.assertRaisesRegex(SystemExit, "matched 0 matched ledger rows"):
            build.verify_functions(selectors)

    def test_many_exact_rows_use_one_ledger_index_not_selector_per_row_scans(self):
        rows = [{"source": "game/Generated.cpp", "name": f"?f{i}@@YAXXZ",
                 "target_rva": hex(0x1000 + i * 8), "target_size": "5",
                 "status": "matched"} for i in range(1000)]
        selectors = [f"row:0x{0x1000 + i * 8:08X}:5:?f{i}@@YAXXZ"
                     for i in range(1000)]
        with patch.object(build, "selector_matches_row",
                          side_effect=AssertionError("exact selectors must use the tuple index")), \
             patch.object(build, "parse_row_selector", wraps=build.parse_row_selector) as parse:
            selected = build.select_function_rows(selectors, rows)
        self.assertEqual(selected, rows)
        self.assertEqual(parse.call_count, len(selectors))


if __name__ == "__main__":
    unittest.main()
