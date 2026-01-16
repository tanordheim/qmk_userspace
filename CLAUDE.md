# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a QMK userspace repository forked from splitkb that supports building firmware for Splitkb Halcyon keyboards with modular hardware components (HLC modules). The repository uses the Vial QMK fork and supports keyboards like Kyria, Elora, Ferris, Lily58, and Corne.

## IMPORTANT: Primary Focus

**When discussing keymaps, implementations, or making changes, always focus on the `tanordheim` keymap directory** for any keyboard that has this layout. This is the user's personal keymap configuration.

Other keymaps in the repository (like `default_hlc`, `vial`, etc.) are reference implementations and should only be mentioned when:
- Explicitly asked about them
- Providing context for how the module system works
- Showing examples of structure that the tanordheim keymap follows

Do not discuss or analyze other keymaps unless specifically requested.

## Building Firmware

### Setup
```bash
# Enable userspace overlay (run from repo root)
qmk config user.overlay_dir="$(realpath .)"

# Setup QMK if not already done
qmk setup
```

### Compile Single Keymap
```bash
# General format
qmk compile -kb <keyboard> -km <keymap> -e <HLC_MODULE>=1 -e TARGET=<output_filename>

# Example for Kyria with encoder module
qmk compile -kb splitkb/halcyon/kyria/rev4 -km tanordheim -e HLC_ENCODER=1 -e TARGET=splitkb_halcyon_kyria_rev4_hlc_encoder

# Using Make
make splitkb/halcyon/kyria/rev4:tanordheim -e HLC_ENCODER=1 -e TARGET=splitkb_halcyon_kyria_rev4_hlc_encoder
```

### Compile All Build Targets
```bash
# Compiles all targets defined in qmk.json
qmk userspace-compile
```

### Managing Build Targets

```bash
# Add a build target to qmk.json
qmk userspace-add -kb <keyboard> -km <keymap> -e <HLC_MODULE>=1 -e TARGET=<filename>

# Remove a build target
qmk userspace-remove -kb <keyboard> -km <keymap> -e <HLC_MODULE>=1 -e TARGET=<filename>

# List current build targets
qmk userspace-list
```

## Halcyon Module System

The Halcyon keyboard line supports hot-swappable hardware modules (HLC). **Every build MUST specify exactly one module** via environment variable:

- `HLC_NONE=1` - No module installed (but other half may have one)
- `HLC_ENCODER=1` - Rotary encoder module
- `HLC_TFT_DISPLAY=1` - TFT RGB display module
- `HLC_CIRQUE_TRACKPAD=1` - Cirque trackpad module

### Module Implementation

Module support is implemented in `users/halcyon_modules/`:
- `users/halcyon_modules/rules.mk` - Top-level conditional inclusion
- `users/halcyon_modules/splitkb/rules.mk` - Module-specific includes and validation
- `users/halcyon_modules/splitkb/hlc_*/` - Per-module implementation directories

Keymaps must:
1. Use `LAYOUT_split_3x6_5_hlc` layout macro (includes 10 extra keys for modules)
2. Set `USER_NAME := halcyon_modules` in their `rules.mk`
3. Define encoder mappings if using `HLC_ENCODER=1` (via `ENCODER_MAP_ENABLE`)

## Architecture

### Directory Structure

- `keyboards/splitkb/halcyon/<keyboard>/keymaps/<keymap>/` - User keymap definitions
  - `keymap.c` or `keymap.json` - Key layout
  - `rules.mk` - Build rules and feature flags
  - `config.h` - Keyboard-specific config
  - `vial.json` - Vial configuration (for vial keymaps)

- `users/halcyon_modules/` - Shared module code
  - `splitkb/` - Halcyon-specific implementation
  - `splitkb/hlc_*/` - Individual module implementations

- `qmk.json` - Build targets configuration
- `Makefile` - Delegates to QMK firmware with userspace overlay

### Build System

The repository uses QMK's userspace build system:
1. `Makefile` auto-detects QMK firmware location via `qmk config`
2. Delegates builds to QMK firmware with `QMK_USERSPACE` set
3. Module selection via environment variables (`-e HLC_*=1`)
4. GitHub Actions build using Vial QMK fork (configured in `.github/workflows/build_binaries.yaml`)

### Keymap Structure

The layout macro `LAYOUT_split_3x6_5_hlc` defines:
- 3x6 key matrix per half
- 5 thumb keys per half
- 5 additional module keys per half (bottom row)

**The `tanordheim` keymap** is the primary keymap configuration in this repository. When working with keymaps, always refer to the tanordheim implementation unless explicitly told otherwise.

For reference, default keymaps (`default_hlc`) typically provide 7 layers:
- `_QWERTY`, `_DVORAK`, `_COLEMAK_DH` - Base layouts
- `_NAV` - Navigation and media controls
- `_SYM` - Numbers and symbols
- `_FUNCTION` - Function keys
- `_ADJUST` - Layout switching and RGB control

## Development Environment

A Nix flake is provided for development:
```bash
# Enter development shell
nix develop

# Available tools: qmk, dos2unix
```

## GitHub Actions

Firmware is automatically built on push via `.github/workflows/build_binaries.yaml`:
- Uses `vial-kb/vial-qmk` repository (vial branch)
- Builds all targets in `qmk.json`
- Publishes `.uf2` files to GitHub Releases

To use standard QMK instead, modify the workflow:
```yaml
with:
  qmk_repo: qmk/qmk_firmware
  qmk_ref: master
```
