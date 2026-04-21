# 🏛️ Hercules CLI

Hercules is a terminal C CLI tool that wraps file and directory operations with cinematic ASCII animations inspired by Greek mythology. Instead of silent `rm` and `find` calls, you get drama.

---

## ⚙️ Features

- 🎬 ASCII animations while operations run
- 🧹 File and directory removal (`--clear`)
- 🔍 Deep system search for files and directories (`--find`)
- 🎨 Colored ANSI terminal output
- 📂 Multi-target support for deletion
- ⚡ Pure C, minimal dependencies

---

## 🚀 Installation

### Linux (Debian/Ubuntu)

The installer compiles from source, removes the previous version (using Hercules itself), and drops the binary into `/usr/local/bin`.

```bash
chmod +x install.sh
./install.sh
```

Requirements: `gcc` and `sudo` access.  
`/usr/local/bin` is already in PATH on Debian/Ubuntu — no extra config needed.

To reinstall or update, just run `./install.sh` again.

### Android (Termux)

The `install.sh` is Linux-only. On Termux, build and install manually:

```bash
# 1. Install the compiler
pkg update
pkg install clang

# 2. Clone or copy the project, then enter the folder
cd ~/Hercules

# 3. Compile
clang src/main.c src/animation.c src/messages.c \
  src/commands/clear.c src/commands/find.c \
  -Iinclude -o hercules

# 4. Install globally
mv hercules $PREFIX/bin/
chmod +x $PREFIX/bin/hercules
```

`$PREFIX/bin` is already in PATH on Termux — no extra config needed.

To update, repeat steps 3 and 4. The old binary is replaced automatically.

#### Searching device storage on Termux

To let Hercules access your internal storage (photos, downloads, etc.), run once:

```bash
termux-setup-storage
```

Then search normally:

```bash
hercules --find .jpg
hercules --find Screenshot -p ~/storage/shared/Pictures
hercules --find .mp4 -p ~/storage/shared/DCIM/Camera
```

---

## 🛠️ Manual Build (Linux)

```bash
gcc src/main.c src/animation.c src/messages.c src/commands/clear.c src/commands/find.c -Iinclude -o hercules
```

---

## 📖 Usage

```bash
hercules --clear <file|dir> [file2|dir2...]
hercules --find  <term> [-p <path>] [-t f|d]
```

### --clear examples

```bash
# Remove a file
hercules --clear old_report.txt

# Remove multiple files
hercules --clear a.txt b.txt c.log

# Remove a directory (recursive)
hercules --clear build/
```

`--clear` detects automatically whether the target is a file or directory.

### --find examples

```bash
# Find by extension
hercules --find .txt

# Partial name search (matches anything containing "config")
hercules --find config

# Exact filename
hercules --find main.c

# Limit search to a specific directory
hercules --find .jpg -p ~/Pictures

# Files only
hercules --find report -t f

# Directories only
hercules --find build -t d
```

`--find` searches from `/` by default (excluding `/proc`, `/sys`, `/dev`, `/run`) and matches files and directories. Search is case-insensitive.

---

## 📁 Project Structure

```
Hercules/
├── src/
│   ├── main.c
│   ├── animation.c
│   ├── messages.c
│   └── commands/
│       ├── clear.c
│       └── find.c
├── include/
│   ├── animation.h
│   ├── commands.h
│   └── messages.h
└── install.sh
```

---

## 🔧 How It Works

| Command | Behavior |
|---|---|
| `--clear <file>` | Plays animation, then calls `remove()` |
| `--clear <dir>` | Plays animation, removes recursively via `rm -rf` |
| `--find <term>` | Detects if term is extension, partial name or exact — builds the right glob and runs `find` with `-iname` |
| `--find <term> -p <path>` | Same, but scoped to a specific directory |
| `--find <term> -t f\|d` | Filters results to files only or directories only |

On success or failure, a random mythological message is printed.
