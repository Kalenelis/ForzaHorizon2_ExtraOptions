# Forza Horizon 2 - Extra Options
A quality-of-life mod for the Xbox One version of Forza Horizon 2 that adds several tweaks to the game.

# Features
 - Intro Skip.
 - Change Car Anywhere.
 - Autodrive (as seen in Forza Horizon 6).
 - Drift Camera (as seen in Forza Horizon 4/5/6).
 - FOV Sliders.
 - Roof toggle for supported cars during free-roam.
 - Lights toggle for all cars.
 - Custom spawn locations.
 - All Stock Rims for All Cars.
 - All DLC Packs Unlocked.
 - VIP Status & Treasure Map Unlocks.
 - 4K Liveries w/ Enhanced Sampling.
 - Unrestricted Photo Mode.
 - Custom Gamerpic Support.
 - Rim Style category with all rims.
 - Minimap Follows Orbit Camera.
 - Azimuth's Save Data Tamper Checks Bypass.
 - "mediapc" Modding Folder Support.

# Information

Many of the features can now be toggled and tweaked inside the game itself through the native menus.

The treasure map is disabled by default. Open the INI and set "UnlockTreasureMap" to 1 if you wish to have it.

Autodrive is engaged with D-Pad Down on a controller or F2 on a keyboard.

Night lights can be toggled by just pressing the right-stick.

Roofs can be toggled by pressing and holding the right-stick for 3 seconds while stationary.

Important: The 3 cars with proper roof animations (BMW Z4 iDrive, Mazda MX-5 (2013), and Ferrari California) will look broken if you are using vanilla car model quality. Set "Car Detail" to High or Ultra in Azimuth.

Important #2: This is a rather experimental feature, so it doesn't look perfect in some cars due to the way the ForzaVista animations were authored.
The Lotus Exige, for example, will have its roof floating above the car. It's beyond the view of the camera but you will spot its shadow. This will be looked into in future updates.

# Installation

The installation is different depending on the translation layer you're using.

### Azimuth (v0.9.10 and newer):

 - Place `dxgi.dll`, `FH2_ExtraOptions.ini`, and `Gamerpic.png` in the **root directory of Azimuth** (directly beside `azimuth.exe`).
 - **Important:** Do **NOT** replace any files inside `Azimuth\data\bin`. Azimuth 0.9.10 introduces SHA-256 integrity checks on its internal files. The new loader uses clean DirectX proxying via `dxgi.dll`.

### Azimuth (v0.9.9 and older legacy):

 - Extract files into `Azimuth\data\bin`, replacing `azimuth-tls.dll`.

### Mezcal:

 - Extract files into `Forza Horizon 2\Mount` where `forza_durango_release_final.exe` is located (the mod is loaded as `xg.dll`).

# Custom gamerpic 
 - You can edit the "Gamerpic.png" image located where you extracted the mod files to with any image you like and it will be used as your avatar in-game.
 - The maximum dimensions supported are 2048x2048 and the image must weight less than 16 megabytes.

# AI Usage Disclosure
Codex was used in this project to create the DLL. The actual research was done manually, mostly based on things I already toyed with in the other titles from the series, but I don't yet have the C language knowledge to code something like this fully from scratch (I was initially editing the raw executable). Leaving this here as I believe people have the right to know.
