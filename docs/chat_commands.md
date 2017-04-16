---
layout: default
---

# Chat Commands

Toolbox supports a variety of chat commands; you can use them by typing in chat like in-game commands such as `/age`.

`/age2` or `/tb age` will display a simple in-game instance time.

`/borderless` will toggle borderless window; alternatively, you can use `/borderless on` or `/borderless off`.

`/cam [args]` or `/camera [args]` to control various aspect of the camera:
* `/cam unlock` and `/cam lock` to lock/unlock camera.
* `/cam speed [value]` sets the unlocked camera speed.
* `/cam fog on` or `/cam fog off` to enable or disable fog.
* `/cam fov [amount]` to change the Field-of-View, or `/cam fov` default to reset it.

`/zoom [value]` to change the maximum zoom to the value. Use just `/zoom` to reset to the default value of 750.

`/dmg [arg]` or `/damage [arg]` controls the party damage monitor:
* `/dmg` or `/dmg report` to print the full results in party chat.
* `/dmg me` to print your own damage in party chat.
* `/dmg [number]` to print a particular party member's damage in party chat.
* `/dmg reset` to reset the monitor.

`/flag all` or `/flag [number]` to flag  a hero in the minimap (same as using the buttons by the minimap).

`/hide [name]` or `/show [name]` to hide or show a window or widget, or `/tb [name]` to toggle.

`/tb reset` moves [Settings](settings) and the main Toolbox window to the top-left corner of the screen.

`/tb close`, `/tb quit`, or `/tb exit` completely close Toolbox and all its windows.

`/pcons` will toggle [pcons](pcons); alternatively, you can use `/pcons on` or `/pcons off`.

`/useskill [slot]` will use the selected skill on recharge; for example, `/useskill 1` will use your first skill. Use `/useskill`, `/useskill 0`, or `/useskill stop` to stop.

`/target` or `/tgt` has few advanced ways to interact with your target:
* `/target closest` or `/target nearest` will target the closest agent to the player.
* `/target getid` will print the the target model ID (aka PlayerNumber). This is unique and constant for each kind of agent.
* `/target getpos` will print the coordinates (x, y) of the target.

`/dialog [id]` will send a dialog; use an integer or hex number instead of `[id]`.

`/to [dest]`, `/tp [dest]` or `/travel [dest]` will map travel you to the `[dest]` outpost. You can use the following values instead of `[dest]`:
* `toa`
* `doa`
* `kamadan` or `kama`
* `embark`
* `vlox` or `vloxs`
* `gadd` or `gadds`
* `urgoz`
* `deep`
* `fav1`, `fav2`, `fav3` for your favorite locations

You can also specify the district with a third argument: possible values are `ae1`, `ee1`, `eg1` (or `dd1`) and `int`. For example, `/tp embark ee1` will make you travel to Embark Beach Europe English District 1.

`/chest` or `/xunlai` to open Xunlai Chest in a city or outpost.

`/afk` will make your character `/sit` and set your status to Away