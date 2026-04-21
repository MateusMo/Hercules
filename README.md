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

The installer compiles from source, removes the previous version (using Hercules itself), and drops the binary into `/usr/local/bin`.

```bash
chmod +x install.sh
./install.sh
```

Requirements: `gcc` and `sudo` access.  
`/usr/local/bin` is already in PATH on Debian/Ubuntu — no extra config needed.

To reinstall or update, just run `./install.sh` again.

---

## 🛠️ Manual Build

```bash
gcc src/main.c src/animation.c src/messages.c src/commands/clear.c src/commands/find.c -Iinclude -o hercules
```

---

## 📖 Usage

```bash
hercules --clear <file|dir> [file2|dir2...]
hercules --find  <name>
```

### Examples

```bash
# Remove a file
hercules --clear old_report.txt

# Remove multiple files
hercules --clear a.txt b.txt c.log

# Remove a directory (recursive)
hercules --clear build/

# Find a file or directory by name
hercules --find config.json
hercules --find my_project
```

`--clear` detects automatically whether the target is a file or directory.  
`--find` searches from `~` and returns all matches, files and directories alike.

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
| `--find <name>` | Plays animation, runs `find ~` and prints all matches |

On success or failure, a random mythological message is printed.
