# Factorio Proximity Chat

Proximity/positional audio in Factorio!

![Positional audio GIF](./images/Positional_Audio.gif)

## To install

- Download [Mumble](https://www.mumble.info/) voice chat software
- Install [mumble plugin](https://github.com/alifeee/MumblePlugin-FactorioPositionalAudio/releases) (see [below](#mumble-plugin-installation) for more info)
- Install Factorio mod (see [below](#factorio-mod-installation) for more info)
- Enable Positional Audio (PA) in Mumble
- Done!
  
  PA will enable when you are in the same game server.

  ![Alt text](images/mumble_enable_pa.png)

### Mumble plugin installation

1. Download the latest `factorio.mumble_plugin` from the [releases page](https://github.com/alifeee/MumblePlugin-FactorioPositionalAudio/releases).
1. Install the plugin in Mumble
  ![Screenshot of mumble, installing plugin](images/mumble_install.png)
1. Enable positional audio
  ![Screenshot of mumble, enabling positional audio](images/mumble_enable_pa.png)
1. Done! To check it works, try the positional audio viewer (requires Mumble v1.5)
  ![Screenshot of mumble, viewing positional audio debugger](images/mumble_PAviewer.png)

### Factorio mod installation

\<placeholder image of mod portal\>

## Development

### Mumble plugin

All files are in [`./mumble`](./mumble/)

The main plugin is in [`plugin.c`](./mumble/plugin.c). For development guide, see [plugin docs](https://github.com/mumble-voip/mumble/blob/master/docs/dev/plugins/README.md). This plugin reads player position information from the file on disk (via the Factorio mod) and attaches to the Mumble Positional Audio API.

To build it, I use [GitHub actions](https://github.com/alifeee/MumblePlugin-FactorioPositionalAudio/actions). The plugin is generated as a file `factorio.mumble_plugin` in the `bundle` artifact (deleted after 1 day).

To make a release, I make a release then manually add `factorio.mumble_plugin` to the release. Version number must be changed in [`plugin.c`](./mumble/plugin.c), [`CMakeLists.txt`](./mumble/CMakeLists.txt), and [`manifest.xml`](./mumble/manifest.xml).

### Factorio mod

All files are in [`./factorio`](./factorio/).

The mod itself is very simple, and consists of a single control script in [`control.lua`](./factorio/control.lua). This script dumps relevant information to a text file every few frames.

Mod information is held in [`info.json`](./factorio/info.json).

Example file output:

```text
XYZ, Player, sUrface, Server
x: 5.65625
y: -2.8359375
z: 0
p: 1
u: 1
s: alifeee
```

#### File location

The log file is put in [`%application directory%`](https://wiki.factorio.com/Application_directory)`/script-output/player_position.txt`.

On Windows, that's

```path
%APPDATA%/Factorio/script-output/player_position.txt
```
