#!/bin/bash

# ─────────────────────────────────────────────
#  Hercules Installer
#  Debian/Ubuntu friendly
# ─────────────────────────────────────────────

RESET="\033[0m"
RED="\033[1;31m"
GREEN="\033[1;32m"
GOLD="\033[1;33m"
CYAN="\033[1;36m"

INSTALL_DIR="/usr/local/bin"
BINARY_NAME="hercules"
INSTALL_PATH="$INSTALL_DIR/$BINARY_NAME"

SRC_FILES="src/main.c src/animation.c src/messages.c src/commands/clear.c src/commands/find.c"
INCLUDES="-Iinclude"

# ── garante que está na raiz do projeto ──────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo -e "${GOLD}"
echo "  ██╗  ██╗███████╗██████╗  ██████╗██╗   ██╗██╗     ███████╗███████╗"
echo "  ██║  ██║██╔════╝██╔══██╗██╔════╝██║   ██║██║     ██╔════╝██╔════╝"
echo "  ███████║█████╗  ██████╔╝██║     ██║   ██║██║     █████╗  ███████╗"
echo "  ██╔══██║██╔══╝  ██╔══██╗██║     ██║   ██║██║     ██╔══╝  ╚════██║"
echo "  ██║  ██║███████╗██║  ██║╚██████╗╚██████╔╝███████╗███████╗███████║"
echo "  ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚══════╝╚══════╝╚══════╝"
echo -e "${RESET}"
echo -e "${CYAN}  Installer — The strength of a demigod, now in your PATH${RESET}"
echo ""

# ── verifica gcc ─────────────────────────────
if ! command -v gcc &>/dev/null; then
    echo -e "${RED}[✗] gcc not found. Install it with: sudo apt install gcc${RESET}"
    exit 1
fi

# ── verifica arquivos fonte ──────────────────
for f in $SRC_FILES; do
    if [ ! -f "$f" ]; then
        echo -e "${RED}[✗] Source file not found: $f${RESET}"
        echo -e "${RED}    Run this script from the root of the Hercules project.${RESET}"
        exit 1
    fi
done

# ── compila ───────────────────────────────────
echo -e "${CYAN}[~] Forging Hercules...${RESET}"

gcc $SRC_FILES $INCLUDES -o /tmp/hercules_new

if [ $? -ne 0 ]; then
    echo -e "${RED}[✗] Compilation failed. Fix the errors above and try again.${RESET}"
    exit 1
fi

echo -e "${GREEN}[✓] Compilation successful.${RESET}"

# ── remove versão antiga ──────────────────────
if [ -f "$INSTALL_PATH" ]; then
    echo -e "${CYAN}[~] Removing old version...${RESET}"

    # usa o proprio hercules instalado para se deletar, como pedido :)
    "$INSTALL_PATH" --clear "$INSTALL_PATH" 2>/dev/null \
        || sudo rm -f "$INSTALL_PATH"
fi

# ── instala ───────────────────────────────────
echo -e "${CYAN}[~] Installing to $INSTALL_PATH ...${RESET}"

sudo mv /tmp/hercules_new "$INSTALL_PATH"
sudo chmod +x "$INSTALL_PATH"

if [ $? -ne 0 ]; then
    echo -e "${RED}[✗] Failed to install. Are you in the sudoers list?${RESET}"
    exit 1
fi

echo -e "${GREEN}[✓] Hercules installed at $INSTALL_PATH${RESET}"

# ── verifica PATH (só avisa se não estiver) ───
if ! echo "$PATH" | grep -q "$INSTALL_DIR"; then
    echo -e "${GOLD}[⚠] $INSTALL_DIR is not in your PATH.${RESET}"
    echo -e "${GOLD}    Add this line to your ~/.bashrc or ~/.zshrc:${RESET}"
    echo -e "${CYAN}    export PATH=\"$INSTALL_DIR:\$PATH\"${RESET}"
else
    echo -e "${GREEN}[✓] $INSTALL_DIR already in PATH — you're good to go.${RESET}"
fi

echo ""
echo -e "${GOLD}[🏛] The gods are pleased. Run: hercules --help${RESET}"
echo ""