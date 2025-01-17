# Custom Resolution Utility (CRU)

version | license | build

This is just a fork of the work [ToastyX](https://www.monitortests.com/forum/User-ToastyX) has been done to fix several problems with graphic cards, monitors, drivers and their communication since 2012. Please download the latest version directly from [https://www.monitortests.com/forum/Thread-Custom-Resolution-Utility-CRU](https://www.monitortests.com/forum/Thread-Custom-Resolution-Utility-CRU) and consider supporting him [on Patreon](https://www.patreon.com/ToastyX).

<a href="https://www.patreon.com/ToastyX"><img src="https://github.com/user-attachments/assets/ecefa998-2b13-4a6b-acae-fc805eb97570" width=20%></a>

### Requirements:

- Windows Vista or later (Windows XP does not support EDID overrides)
- AMD/ATI or NVIDIA GPU with appropriate driver installed (Microsoft Basic Display Adapter driver does not support EDID overrides)
- Intel GPUs and laptops with switchable graphics are supported with one of these drivers:
  - Newer Intel GPUs are supported with the latest drivers.
  - 6th generation (Skylake): Intel Graphics Driver for Windows [15.45]
  - 4th/5th generation (Haswell/Broadwell): Intel Graphics Driver for Windows [15.40]
  - 4th generation (Haswell) for Windows 7/8.1: Intel Graphics Driver for Windows 7/8.1 [15.36]
  - Older Intel GPUs are supported for external displays only using the alternative method described below.

Before making any changes, familiarize yourself with booting Windows in safe mode using a recovery drive in case you can't see the screen. If you don't have a recovery drive, press and hold the power button to shut off the computer while Windows is booting. Doing this twice should give you recovery options that you can use to get into safe mode: Troubleshoot > Advanced options > Startup Settings > Restart

### Getting started:

1. Run CRU.exe. A UAC prompt may appear because it needs permission to access the registry.
2. Choose a display from the drop-down list.
  - "(active)" means the display is connected and recognized by the graphics driver.
  - "*" means changes were made and an override was saved in the registry.
3. Edit the configuration as desired. Please read the sections below for more information.
4. Repeat steps 2-3 for other displays if required.
  - The "Copy" and "Paste" buttons at the top can be used to copy all the resolutions, extension blocks, and range limits if included. It will not copy the name or serial number, but it will copy the inclusion of these items using the display's own information. Import follows the same logic unless "Import complete EDID" is selected.
5. Click "OK" to save the changes.
6. Run restart.exe to restart the graphics driver.
  - If the display does not return after 15 seconds, press F8 for recovery mode. This will temporarily unload all the EDID overrides without deleting them. Restart the driver again to reload any changes.
  - On some systems, the graphics driver might crash while restarting. If that happens, the driver might be disabled after rebooting. Simply run restart.exe again to enable the driver.
7. Set the resolution in the Windows display settings. To set the refresh rate:
  - Windows 10: right-click on the desktop > Display settings > Advanced display settings > Display adapter properties > Monitor tab
  - Windows Vista/7/8/8.1: right-click on the desktop > Screen resolution > Advanced settings > Monitor tab

To reset a display back to the default configuration, use the "Delete" button at the top to delete the override from the registry and reboot. To reset all displays, run reset-all.exe and reboot. This can be done in safe mode if necessary.

### Alternative method for Intel GPUs:

If you have an older Intel GPU, use the "Export..." button and choose "EXE file" for the file type to export a self-contained EDID override installer. Then run the .exe file and choose "Install EDID" to install the EDID override on all matching displays.

### Detailed resolutions:

- Detailed resolutions are the preferred way to add custom resolutions. More detailed resolutions can be added using extension blocks.
- The first detailed resolution is considered the preferred or native resolution. At least one detailed resolution should exist to define the native resolution. All other resolutions can be removed if they are not needed. The graphics driver will automatically add some common lower resolutions as scaled resolutions. To edit the list of scaled resolutions for AMD and NVIDIA GPUs, use Scaled Resolution Editor.
- CRU adds monitor resolutions, not scaled resolutions.
