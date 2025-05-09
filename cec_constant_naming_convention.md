# CEC Benchmark Constant-File Standard

---

## 1 . Directory layout (canonical)

```
repo-root/
└── CEC{YEAR}_C-Code/
    ├── src/                # the supplied reference code
    └── input_data/
        └── f{FUNC:02d}/    # one folder per benchmark function
            ├── shift_D10.txt
            ├── rot_D10.txt
            ├── rot_nr_D10.txt
            ├── perm_D10.txt
            ├── …
            └── f{FUNC}.meta.yaml   # optional manifest (see § 4)
```

* Rationale — “year” and “function” are already in the path; no need to repeat them in the file name.
* Anything copied outside this hierarchy will still be readable because each text file starts with a header comment—see § 3.

---

## 2 . File-name template

```
{DATATYPE}{VARIANT}_D{DIMENSION}.txt
```

| Token       | Allowed values                           | Notes                                        |
| ----------- | ---------------------------------------- | -------------------------------------------- |
| `DATATYPE`  | `shift`, `rot`, `perm`, `bias`           | Easily extensible—just add a new word.       |
| `VARIANT`   | (empty), `_ns`, `_nr`, `_sub` …          | Use sparingly; keep meanings in § 2.1 table. |
| `DIMENSION` | integer, **no padding**, preceded by `D` | `D10`, `D100`, …                             |

### 2.1 Variants glossary (keep updated)

| Variant | Meaning                                          |
| ------- | ------------------------------------------------ |
| `_ns`   | “no-shift” vector (all zeros)                    |
| `_nr`   | “no-rotation” / identity matrix                  |
| `_sub`  | sub-component matrix used by composite functions |

> **Examples inside `…/input_data/f05/`**
>
> * `shift_D50.txt`
> * `rot_D50.txt`
> * `rot_nr_D50.txt`
> * `perm_D50.txt`

---

## 3 . File header (first line)

Every text file **must begin** with a single-line comment so it remains self-describing when detached from the tree:

```txt
# CEC2021  •  f05  •  shift vector  •  dim 50
0.12345  -1.2345  …
```

*Use `#` for comments—C and Python readers ignore it.*

---

## 4 . Optional per-function manifest (`f{FUNC}.meta.yaml`)

```yaml
year: 2021
function: 5
dimensions: [10, 30, 50]
files:
  shift:  shift_D{d}.txt
  rot:    rot_D{d}.txt
  perm:   perm_D{d}.txt
notes: "rot_nr indicates identity blocks for separable sub-components."
```

Scripts can load this to locate every constant in one shot.

---

## 5 . Migration recipe (one-liner per year)

```bash
YEAR=2021
for f in CEC${YEAR}_C-Code/input_data_raw/*; do
  base=$(basename "$f")
  func=$(echo "$base" | grep -oE '[0-9]+' | head -1 | xargs printf 'f%02d')
  dim=$(echo "$base" | grep -oE 'D[0-9]+' || echo "D0")
  case "$base" in
    shift*) dt="shift";;
    M_*)    dt="rot";;
    shuffle*) dt="perm";;
    *)      dt="bias";;
  esac
  variant=$(echo "$base" | grep -Eo '_(ns|nr|sub)' || true)
  new="CEC${YEAR}_C-Code/input_data/${func}/${dt}${variant}_${dim}.txt"
  mkdir -p "$(dirname "$new")"
  git mv "$f" "$new"
done
```

Repeat for each historical year; remove the temporary `input_data_raw` folder when done.

---

## 6 . CI lint rule

A single regex is enough:

```
^(shift|rot(_nr)?|shift_ns|perm|bias)(_sub)?_D[0-9]+\.txt$
```

Fail the build if any file in `input_data/` violates it.

---

### Summary

* **No redundant tokens** – year & function live in the path.
* **Human-obvious** – `shift_D10.txt` needs no cheat-sheet.
* **Script-friendly** – fixed pattern + optional manifest = painless I/O.
* **Forward-proof** – adding CEC 2025 or a new datatype is trivial.

Refactor once, lock the linter, and you’ll never worry about file chaos again.
