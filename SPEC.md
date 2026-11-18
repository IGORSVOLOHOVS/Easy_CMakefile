# easy-cmakefile: software requirements specification

Reverse-engineered from commit `830f3cc` (branch `release`, tag `v1.0.0`) on
2026-11-18. Every requirement below describes behaviour present in the files;
nothing here is a plan. Documentation hub: [docs/README.md](docs/README.md).

<!-- jira-sync:start -->
Jira: KAN-97

## Tasks

This list is one ticket in Jira project KAN, [KAN-97](https://igorsvolohovs.atlassian.net/browse/KAN-97). Each line is a checkbox there: tick it in Jira and the sync ticks it here; add a checkbox there and it is appended here. Done items are the features described in section 3; open items are what the project declares but the code does not do yet.

- [x] Build configuration (`CMakeLists.txt`) (section 3.1) <!-- spec-build-configuration-cmakelists-txt -->
- [x] Example program (`src/main.cpp`) (section 3.2) <!-- spec-example-program-src-main-cpp -->
- [x] Editor integration (`.vscode/`) (section 3.3) <!-- spec-editor-integration-vscode -->
- [x] Repository interface (`recipe.ps1`) (section 3.4) <!-- spec-repository-interface-recipe-ps1 -->
- [x] Git hooks (`.claude/hooks/git/`) (section 3.5) <!-- spec-git-hooks-claude-hooks-git -->
- [x] Claude Code hooks (`.claude/hooks/`, `.claude/settings.json`) (section 3.6) <!-- spec-claude-code-hooks-claude-hooks-claude-settings-jso -->
- [x] Gitea workflows (`.gitea/workflows/`) (section 3.7) <!-- spec-gitea-workflows-gitea-workflows -->
- [ ] The executable is found in `bin` after building (declared, not implemented) <!-- spec-the-executable-is-found-in-bin-after-building -->
- [ ] Libraries come through the vcpkg toolchain (declared, not implemented) <!-- spec-libraries-come-through-the-vcpkg-toolchain -->
- [ ] Static curl (`CURL_STATICLIB`) (declared, not implemented) <!-- spec-static-curl-curlstaticlib -->
- [ ] A separate link block for the static-library variant (declared, not implemented) <!-- spec-a-separate-link-block-for-the-static-library-varia -->
- [ ] Wiki generation by `tools/wiki.py` (declared, not implemented) <!-- spec-wiki-generation-by-tools-wiki-py -->
- [ ] Compliance with lab requirements revision 4.0.0 (declared, not implemented) <!-- spec-compliance-with-lab-requirements-revision-4-0-0 -->

<!-- jira-sync:end -->

## 1. Purpose and scope

The repository provides an annotated CMake configuration for a C++20
executable that uses libraries installed by vcpkg, and one example program
that performs an HTTP GET with libcurl (`README.md`). It is a template to
copy from, not a distributed program (`README.md`; `recipe.ps1:16-17`).

In scope:

- `CMakeLists.txt` and `src/main.cpp` (the template and its example);
- `.vscode/` (editor tasks and debug launch for the template);
- the repository tooling: `recipe.ps1`, the git hooks in `.claude/hooks/git/`,
  the Claude Code hooks and skill in `.claude/`, and the Gitea Actions
  workflows in `.gitea/workflows/`.

Out of scope (not present in the repository): a vcpkg manifest, any header
in `include/`, an installer, a library for other projects (`$Provides = @()`,
`recipe.ps1:17`), automated tests, GitHub Actions workflows.

## 2. Context

| Item | What the files show |
|---|---|
| Actors | The person who copies the template (not named); the repository owner, the only name in `$Reviewers` (`recipe.ps1:22`, `CLAUDE.md`); Claude Code sessions working under `CLAUDE.md`; the CI account `lab-bot` (`.gitea/workflows/release.yaml:38-41`). |
| External systems | vcpkg installation at `VCPKG_PATH` (`CMakeLists.txt:5`); the HTTP endpoint `https://api.example.com/data`, a placeholder (`src/main.cpp:24`, `README.md`); a Gitea server and its API, reached by the workflows with secret `LAB_BOT_TOKEN` (`.gitea/workflows/*.yaml`); Git LFS when installed (`.claude/hooks/git/pre-push:4-6`). |
| Runtime, template | CMake 3.20 or newer (`CMakeLists.txt:1`); a C++20 compiler (`CMakeLists.txt:11-13`); vcpkg triplet `x64-windows` (`CMakeLists.txt:26,30`); `.vscode/` expects `make` and `/usr/bin/gdb` (`.vscode/tasks.json:11`, `.vscode/launch.json:16`). |
| Runtime, tooling | Windows PowerShell via `powershell.exe -NoProfile -ExecutionPolicy Bypass` (`.claude/settings.json:8-18`, `.claude/hooks/git/commit-msg:3`); Python with pytest and ruff (`recipe.ps1:46-52`); Gitea runners labelled `windows` with shell `powershell` (`.gitea/workflows/*.yaml`, `runs-on`, `defaults`). |

## 3. Functional requirements

### 3.1 Build configuration (`CMakeLists.txt`)

- **FR-1.** The system shall require CMake 3.20 or newer and declare project `test_cmake` with the C++ language only. Source: `CMakeLists.txt:1-2`. Verification: no test.
- **FR-2.** The system shall require the C++20 standard with compiler extensions off. Source: `CMakeLists.txt:11-13`. Verification: no test.
- **FR-3.** The system shall create the folders `bin`, `lib`, `include` and `src` inside the build folder at configure time. Source: `CMakeLists.txt:19-22`. Verification: no test.
- **FR-4.** The system shall add `${VCPKG_PATH}/installed/x64-windows/include` to the include path and `${VCPKG_PATH}/installed/x64-windows/lib` to the link path, with `VCPKG_PATH` fixed in the file. Source: `CMakeLists.txt:5,25-31`. Verification: no test.
- **FR-5.** The system shall build one executable named after the project from every file matching `src/*.cpp` and `include/*.h`, searched recursively. Source: `CMakeLists.txt:34-44`. Verification: no test.
- **FR-6.** The system shall link the executable privately with `libcurl`. Source: `CMakeLists.txt:50-56` (repeated at `58-64`). Verification: no test.

### 3.2 Example program (`src/main.cpp`)

- **FR-7.** The program shall initialise libcurl and send one HTTP GET request to `https://api.example.com/data`. Source: `src/main.cpp:14,17,24-25,33`. Verification: no test.
- **FR-8.** The program shall collect the response body in memory through a write callback. Source: `src/main.cpp:6-10,28-30`. Verification: no test.
- **FR-9.** When the transfer succeeds, the program shall print `Response: <body>` to stdout, release libcurl and exit with code 0. Source: `src/main.cpp:40-46`. Verification: no test.
- **FR-10.** When `curl_easy_init` fails, the program shall print `Failed to initialize libcurl.` to stderr and exit with code 1. Source: `src/main.cpp:18-21`. Verification: no test.
- **FR-11.** When the transfer fails, the program shall print `Failed to perform HTTP request: <libcurl error text>` to stderr and exit with code 1. Source: `src/main.cpp:34-37`. Verification: no test.

### 3.3 Editor integration (`.vscode/`)

- **FR-12.** The editor configuration shall offer three shell tasks: `Build C++ project` (`cd ./build && make`), `Build & run C++ project` (`cd ./build && make && ./main`) and `Build CMake` (`cd ./build && cmake build ..`). Source: `.vscode/tasks.json:5-30`. Verification: no test.
- **FR-13.** The editor configuration shall launch `${workspaceFolder}/build/main` under gdb (`/usr/bin/gdb`, pretty-printing on, external console) after the `Build C++ project` task. Source: `.vscode/launch.json:5-23`. Verification: no test.

### 3.4 Repository interface (`recipe.ps1`)

- **FR-14.** The recipe shall accept exactly one verb out of `build`, `install`, `uninstall`, `clean`, `run`, `publish`, `info`, `test`, followed by any further arguments. Source: `recipe.ps1:1-7`. Verification: no test.
- **FR-15.** Before any verb, the recipe shall load `KEY=VALUE` lines from `.claude/.env` into the process environment, strip surrounding quotes, and skip any variable that is already set. Source: `recipe.ps1:30-38`. Verification: no test.
- **FR-16.** The verb `test` shall set `core.hooksPath` to `.claude/hooks/git`, run `python -m pytest .claude` (exit code 5 accepted), `python -m ruff check .claude` and `python -m ruff format .claude`, and exit 1 on the first failure, else 0. Source: `recipe.ps1:41-55`. Verification: no test.
- **FR-17.** The verb `info` shall print `Name`, `Code`, `Version` and `Summary` and exit 0. Source: `recipe.ps1:56-62`. Verification: no test; run by hand for this document, exit 0.
- **FR-18.** The verb `clean` shall delete every `__pycache__`, `.pytest_cache` and `.ruff_cache` folder under the repository root. Source: `recipe.ps1:63-68`. Verification: no test.
- **FR-19.** The verbs `build`, `install`, `uninstall`, `run` and `publish` shall print `nothing to <verb>` and exit 0. Source: `recipe.ps1:69-73`. Verification: no test; `build` and `run` run by hand for this document.

### 3.5 Git hooks (`.claude/hooks/git/`)

- **FR-20.** The `commit-msg` hook shall refuse a message that starts with a UTF-8 byte-order mark. Source: `.claude/hooks/git/commit-msg.ps1:22-28`. Verification: no test.
- **FR-21.** The `commit-msg` hook shall refuse a subject (first line not starting with `#`) that does not match `<type>(<scope>): <text>`, case-sensitive, with types and scopes read from `$CommitTypes` and `$CommitScopes` in `recipe.ps1`; a subject starting with `Merge ` while `MERGE_HEAD` exists passes. Source: `.claude/hooks/git/commit-msg.ps1:8-19,30-47`. Verification: no test.
- **FR-22.** The `commit-msg` hook shall refuse a message without a `Signed-off-by: <name> <<address>>` trailer. Source: `.claude/hooks/git/commit-msg.ps1:49-53`. Verification: no test.
- **FR-23.** The `pre-push` hook shall run `git lfs pre-push` first when `git-lfs` is installed. Source: `.claude/hooks/git/pre-push:3-6`. Verification: no test.
- **FR-24.** The `pre-push` hook shall refuse a pushed branch whose name does not match `<$Code>-<issue number>/<branch type>/<slug>` (lower-case slug words joined by `-`), skipping tags, deletions, `test` and `from-*`. Source: `.claude/hooks/git/pre-push.ps1:16-41,48-52,87-93`. Verification: no test.
- **FR-25.** The `pre-push` hook shall refuse deleting `release`, and refuse updating `release` unless one pushed first-parent commit not on `origin/test` carries `$OverridePhrase` alone on a line and a `Why: ` line; creating `release` passes. Source: `.claude/hooks/git/pre-push.ps1:43-45,54-86`. Verification: no test.

### 3.6 Claude Code hooks (`.claude/hooks/`, `.claude/settings.json`)

- **FR-26.** The gate shall deny a `PreToolUse` call whose payload cannot be parsed or names no tool. Source: `.claude/hooks/gate.ps1:3-4,34-36`. Verification: no test.
- **FR-27.** For `Bash` and `PowerShell` calls, the gate shall split the command at `;`, `|`, `&`, `&&`, `||` and newlines, unwrap `bash -c`, `sh`, `cmd /c`, `powershell`, `pwsh` and `xargs`, and deny a recursive delete (`rm -r`, `Remove-Item -Recurse`, `rd /s`, `rimraf` and similar) unless every path resolves under `$env:TEMP`. Source: `.claude/hooks/gate.ps1:40-57,83-119,138-154`. Verification: no test.
- **FR-28.** The gate shall deny `git push` with `--force`, `-f`, `--mirror` or a `+<ref>` refspec, and allow `--force-with-lease`. Source: `.claude/hooks/gate.ps1:155-163`. Verification: no test.
- **FR-29.** On branches `test` and `release`, the gate shall deny `git reset --hard` (except to `origin/<branch>`, `@{u}` or `@{upstream}`), `git clean -f` / `--force`, `git commit --amend`, `git rebase` and `git filter-branch`. Source: `.claude/hooks/gate.ps1:121-129,164-177`. Verification: no test.
- **FR-30.** The hooks shall append one JSON object per event to `.claude/logs/ai.jsonl` (fields `ts`, `event`, `session`, `tool`, `decision`, `detail`) for the nine events wired in settings. Source: `.claude/hooks/log.ps1:2-24`, `.claude/hooks/gate.ps1:6-23`, `.claude/hooks/session-start-stop.ps1:8-23`, `.claude/settings.json:7-18`. Verification: no test.
- **FR-31.** At `SessionStart`, the hooks shall move `ai.jsonl` larger than 10 MB to `ai.jsonl.<yyyyMMddHHmmss>.bak`, set `core.hooksPath`, write an error to stderr if `recipe.ps1` is missing, and return the branch and the issue number taken from the branch name as additional context. Source: `.claude/hooks/session-start-stop.ps1:26-48`. Verification: no test.
- **FR-32.** The `lab-ai-env` skill shall direct Claude Code to write `.claude/logs/report-<yyyy-mm-dd>.md` with six parts (totals, failures, friction, context health, prompt quality, suggestions) from `ai.jsonl` and the session transcripts. Source: `.claude/skills/lab-ai-env/SKILL.md:39-69`. Verification: no test.

### 3.7 Gitea workflows (`.gitea/workflows/`)

- **FR-33.** `propose` shall, on a pull request into `test`, check the branch name grammar (`from-*` exempt), check subject and `Signed-off-by` of every non-merge commit not already on `release`, run `.\recipe.ps1 test` followed by `git diff --exit-code`, and on open or reopen request review from `$Reviewers` other than the poster and post a comment. Source: `.gitea/workflows/propose.yaml:1-193`. Verification: no test.
- **FR-34.** `test` shall, on a push to `test`, daily at 03:00 (cron) and on manual dispatch, check runner disk space and that `python`, `ruff`, `pytest` and `mypy` answer, run `.\recipe.ps1 test`, `git diff --exit-code` and `.\recipe.ps1 build`, run the install/uninstall step only when `recipe.ps1` defines `$App`, and the wiki step only when it defines `$App` or a non-empty `$Provides`. Source: `.gitea/workflows/test.yaml:1-120`. Verification: no test.
- **FR-35.** `release-gate` shall, on a pull request into `release`, fail unless the head branch is `test`, rerun the checks, and run a manual gate driven by `tests/manual/tests.json`, posting status `manual/verdict` as success when the list is absent or empty. Source: `.gitea/workflows/release-gate.yaml:1-150`. Verification: no test.
- **FR-36.** `release` shall, on a push to `release`, read `$Version`, skip publishing when tag `v<version>` exists, otherwise create release `v<version>` with notes from the commits since the last tag, attach `manual-report.md` and `sbom.md`, and close the shipped issues; in both cases it merges `release` back into `test` (that step runs on `success() || failure()`, not gated by the tag check). Source: `.gitea/workflows/release.yaml:45-60,76-125,279-354,356-400`. Verification: no test.
- **FR-37.** `sweep` shall, every Monday at 04:00 (cron), delete work branches already merged into `test`, comment on open pull requests idle for 30 days or more, and close those idle for 60 days or more. Source: `.gitea/workflows/sweep.yaml:1-80`. Verification: no test.

### 3.8 Declared but not implemented

| Claim | Where it is claimed | What the code does |
|---|---|---|
| The executable is found in `bin` after building | 2023 README, `git show 9e9ebb8:README.md` ("Building the Project") | No output directory is set; `bin` is only created (`CMakeLists.txt:19`). |
| Libraries come through the vcpkg toolchain | `CMakeLists.txt:7-8` comment and `set` | Set after `project()` (line 2); `README.md` states it is not used. |
| Static curl (`CURL_STATICLIB`) | `CMakeLists.txt:15` | `set(-DCURL_STATICLIB=ON)` defines nothing (`README.md`). |
| A separate link block for the static-library variant | `CMakeLists.txt:58` comment | The block is active, so `libcurl` is listed twice for the executable. |
| Wiki generation by `tools/wiki.py` | `.gitea/workflows/test.yaml:73-109` | `tools/wiki.py` is not in the repository; the step is skipped while nothing ships. |
| Compliance with lab requirements revision 4.0.0 | `README.md`, "Lab requirements" | Five exceptions named there (R-02, R-09, R-37, R-41, R-42); the requirement text is on a server outside the repository. |

## 4. Interfaces

### 4.1 Example program

| Item | Value | Source |
|---|---|---|
| Arguments | none read | `src/main.cpp:12` |
| Request | HTTP GET `https://api.example.com/data`, libcurl defaults | `src/main.cpp:24-33` |
| stdout | `Response: <body>` | `src/main.cpp:40` |
| stderr | `Failed to initialize libcurl.` / `Failed to perform HTTP request: <error>` | `src/main.cpp:19,35` |
| Exit code | 0 success, 1 failure | `src/main.cpp:20,36,46` |

### 4.2 `recipe.ps1`

| Verb | Effect | Exit code | Source |
|---|---|---|---|
| `test` | hooks path, pytest, ruff check, ruff format | 0 / 1 | `recipe.ps1:41-55` |
| `info` | four metadata lines | 0 | `recipe.ps1:56-62` |
| `clean` | delete tool caches | 0 | `recipe.ps1:63-68` |
| `build`, `install`, `uninstall`, `run`, `publish` | `nothing to <verb>` | 0 | `recipe.ps1:69-73` |

### 4.3 Hooks

| Hook | Input | Output | Source |
|---|---|---|---|
| `commit-msg` | path of the message file | exit 1 and a reason on refusal | `.claude/hooks/git/commit-msg.ps1` |
| `pre-push` | stdin lines `<local ref> <local sha> <remote ref> <remote sha>` | exit 1 and a reason on refusal | `.claude/hooks/git/pre-push.ps1:1` |
| `gate.ps1` (PreToolUse, Bash/PowerShell) | hook JSON on stdin | `{"hookSpecificOutput":{"permissionDecision":"deny",...}}` on denial | `.claude/hooks/gate.ps1:25-32` |
| `session-start-stop.ps1` (SessionStart) | hook JSON on stdin | `hookSpecificOutput.additionalContext` with branch and issue | `.claude/hooks/session-start-stop.ps1:44-47` |

### 4.4 Workflows

| Workflow | Trigger | Jobs | Source |
|---|---|---|---|
| `propose` | pull request into `test` | `gate` | `.gitea/workflows/propose.yaml:2-13` |
| `test` | push to `test`, cron `0 3 * * *`, dispatch | `prove` | `.gitea/workflows/test.yaml:2-15` |
| `release-gate` | pull request into `release` | `checks`, `manual-gate` | `.gitea/workflows/release-gate.yaml:2-18,87-89` |
| `release` | push to `release` | `publish` | `.gitea/workflows/release.yaml:2-12` |
| `sweep` | cron `0 4 * * 1` | `sweep` | `.gitea/workflows/sweep.yaml:2-12` |

## 5. Data

| Entity | Storage and format | Source |
|---|---|---|
| Sources of the target | `src/**/*.cpp`, `include/**/*.h` (no `include/` in the repository) | `CMakeLists.txt:34-41` |
| Repository metadata | one-line PowerShell literals in `recipe.ps1`, read as text by hooks and workflows | `recipe.ps1:9-23`, `.gitea/workflows/propose.yaml:48-70` |
| Local keys | `.claude/.env`, `KEY=VALUE` per line, gitignored | `recipe.ps1:30-38`, `.gitignore:24` |
| Event log | `.claude/logs/ai.jsonl`, one JSON object per line, UTF-8 without BOM, gitignored; `detail` holds at most 200 characters | `.claude/hooks/log.ps1:7-19`, `.gitignore:17` |
| Manual test list | `tests/manual/tests.json`, `{"tests": [{"id": ..., "blocking": ...}]}`; ids match `^[a-z0-9][a-z0-9_-]{0,60}$`, not `verdict`, unique (absent) | `.gitea/workflows/release-gate.yaml:107-137` |
| Release assets | `manual-report.md`, `sbom.md` (from `$Needs`, `$Tools`, `$Version` lines) | `.gitea/workflows/release.yaml:279-336` |

## 6. Non-functional requirements

- **NFR-1.** C++20 is mandatory and compiler extensions are off. Source: `CMakeLists.txt:11-13`.
- **NFR-2.** Library paths assume the vcpkg triplet `x64-windows`. Source: `CMakeLists.txt:26,30`.
- **NFR-3.** Hook log writes retry up to 20 times on a locked file, waiting 10 ms × attempt. Source: `.claude/hooks/log.ps1:20-24`, `.claude/hooks/gate.ps1:17-21`, `.claude/hooks/session-start-stop.ps1:17-21`.
- **NFR-4.** The event log is rotated above 10 MB at session start. Source: `.claude/hooks/session-start-stop.ps1:28-30`.
- **NFR-5.** Keys and prompt text stay out of git: `.claude/.env`, `.env` and `.claude/logs/` are ignored. Source: `.gitignore:17,24,27`; `CLAUDE.md` rules 4-5.
- **NFR-6.** Workflow time limits: `propose`, `test`, `release-gate/checks` and `release` 60 min, `manual-gate` 170 min with a 150 min wait, `sweep` 15 min. Source: `timeout-minutes` in each file; `.gitea/workflows/release-gate.yaml:91,101`.
- **NFR-7.** Runs that install share the concurrency group `installer-<repository>` without cancelling each other; `release-gate` cancels an older run for the same pull request. Source: `.gitea/workflows/test.yaml:18-20`, `.gitea/workflows/release-gate.yaml:7-9,20-22`.
- **NFR-8.** The `test` workflow fails below 5 GB free on drive C: and warns below 20 GB. Source: `.gitea/workflows/test.yaml:34-36`.
- **NFR-9.** ruff refuses to run unless its version is `0.16.1`. Source: `.claude/ruff.toml:2`.
- **NFR-10.** Line endings are LF, except CRLF for `*.ps1`, `*.bat`, `*.cmd`; PDF, PNG, JPG, ZIP and 7z go through Git LFS. Source: `.gitattributes:1-12`.
- **NFR-11.** Claude Code sessions run with `PYTHONIOENCODING=utf-8`, `PYTHONUTF8=1`, `MSYS_NO_PATHCONV=1`. Source: `.claude/settings.json:2-6`.

## 7. Constraints and dependencies

| Dependency | Version | Source |
|---|---|---|
| CMake | ≥ 3.20 | `CMakeLists.txt:1` |
| libcurl via vcpkg | not pinned; no `vcpkg.json` | `CMakeLists.txt:55`, `src/main.cpp:3` |
| C++ standard library (`iostream`, `string`) | C++20 | `src/main.cpp:1-2` |
| Windows PowerShell | 5.1 | `.gitea/pull_request_template.md:16` |
| Python, pytest | not pinned | `recipe.ps1:46`, `.claude/pytest.ini` |
| ruff | `==0.16.1` | `.claude/ruff.toml:2` |
| mypy | presence checked on the runner only | `.gitea/workflows/test.yaml:38` |
| `actions/checkout` | `v4` | `.gitea/workflows/*.yaml` |
| `actions/upload-artifact` | `v3` | `.gitea/workflows/release-gate.yaml:442` |
| Easy C++ Projects (VS Code) | not pinned | `.vscode/.easycpp:1` |
| Licence | MIT | `LICENSE` |

No lock file exists for any language.

## 8. Acceptance

There are no automated tests; `python -m pytest --collect-only -q -p
no:cacheprovider .claude` prints `no tests collected`. Checks that exist:

1. `.\recipe.ps1 test` exits 0 and leaves `git diff --exit-code` clean
   (FR-16; the same check runs in `propose`, `test` and `release-gate`).
2. `.\recipe.ps1 info` prints four lines and `.\recipe.ps1 build` prints
   `nothing to build`, both exit 0 (FR-17, FR-19; run for this document).
3. Manual, not run here: configure and build with CMake on a machine with a
   C++20 compiler and libcurl at `VCPKG_PATH`, then run the executable and see
   FR-7 to FR-11 (with a reachable URL in place of the placeholder).
4. Manual, not run here: a commit without `-s`, a subject `Fix(core): x`, and
   a push of a branch named `my-branch` are refused by the git hooks
   (FR-21, FR-22, FR-24).

## 9. Open questions

1. Who copies the template, and for which platform: the CMake file uses the
   `x64-windows` triplet, the `.vscode/` files use `make` and `/usr/bin/gdb`.
2. Was this exact `CMakeLists.txt` ever built successfully? The README says
   nothing is built or tested in the lab.
3. Which libcurl version, and was static linking (`CURL_STATICLIB`) wanted?
4. Why do the VS Code tasks run `build/main` when the target is `test_cmake`,
   and what was `cmake build ..` in the `Build CMake` task meant to do?
5. What R-37, R-41 and R-42 of the lab requirements say, and what issues
   #7-#11 hold: both live on the Gitea server, outside the repository.
6. Does a Gitea runner serve this repository, and have `propose` and
   `release-gate` run yet? `CLAUDE.md` makes branch protection depend on it.
7. Is the branch `main` (old default, `17cff4e`) still kept on GitHub
   alongside `release` and `test`? Answered: yes - on 2026-11-18
   `git ls-remote origin` lists `refs/heads/main` at `17cff4e` next to
   `release` (`830f3cc`) and `test` (`222dd46`). Whether it is meant to stay
   is not stated.
8. Will `$Version` be bumped? `release` publishes nothing while tag `v1.0.0`
   exists.
