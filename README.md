# Custom Resolution Utility (CRU)

[![GitHub Release](https://img.shields.io/github/v/release/kreier/cru)](https://GitHub.com/kreier/cru/releases/)
![GitHub License](https://img.shields.io/github/license/kreier/cru)
[![pages-build-deployment](https://github.com/kreier/cru/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/kreier/cru/actions/workflows/pages/pages-build-deployment)

This is just a fork of the work [ToastyX](https://www.monitortests.com/forum/User-ToastyX) has been done to fix several problems with graphic cards, monitors, drivers and their communication since 2012. Please download the latest version directly from [https://www.monitortests.com/forum/Thread-Custom-Resolution-Utility-CRU](https://www.monitortests.com/forum/Thread-Custom-Resolution-Utility-CRU) and consider supporting him [on Patreon](https://www.patreon.com/ToastyX).

[![Patreon support](docs/patreon.png)](https://www.patreon.com/ToastyX)

## Example

This is how this Windows program looks like:

![sample image](docs/example.png)

### Requirements:

- Windows Vista or later (Windows XP does not support EDID overrides)
- AMD/ATI or NVIDIA GPU with appropriate driver installed (Microsoft Basic Display Adapter driver does not support EDID overrides)
- Intel GPUs and laptops with switchable graphics are supported with one of these drivers:
  - Newer Intel GPUs are supported with the latest drivers.
  - 6th generation (Skylake): [Intel Graphics Driver for Windows [15.45]](https://downloadcenter.intel.com/download/30195)
  - 4th/5th generation (Haswell/Broadwell): [Intel Graphics Driver for Windows [15.40]](https://downloadcenter.intel.com/download/30196)
  - 4th generation (Haswell) for Windows 7/8.1: [Intel Graphics Driver for Windows 7/8.1 [15.36]](https://downloadcenter.intel.com/download/29970)
  - Older Intel GPUs are supported for external displays only using the alternative method described below.

Before making any changes, familiarize yourself with booting Windows in safe mode using a recovery drive in case you can't see the screen. If you don't have a recovery drive, press and hold the power button to shut off the computer while Windows is booting. Doing this twice should give you recovery options that you can use to get into safe mode: Troubleshoot > Advanced options > Startup Settings > Restart

### Getting started:

1. Run CRU.exe. A UAC prompt may appear because it needs permission to access the registry.
2. Choose a display from the drop-down list.
    - "(active)" means the display is connected and recognized by the graphics driver.
    - "*" means changes were made and an override was saved in the registry.
3. Edit the configuration as desired. __Please read the sections below for more information.__
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

* Detailed resolutions are the preferred way to add custom resolutions. More detailed resolutions can be added using extension blocks.
* The first detailed resolution is considered the preferred or native resolution. At least one detailed resolution should exist to define the native resolution. All other resolutions can be removed if they are not needed. The graphics driver will automatically add some common lower resolutions as scaled resolutions. To edit the list of scaled resolutions for AMD and NVIDIA GPUs, use [Scaled Resolution Editor](https://www.monitortests.com/forum/Thread-Scaled-Resolution-Editor-SRE).
* CRU adds monitor resolutions, not scaled resolutions. Lower resolutions can be scaled up to the native resolution by enabling GPU scaling in the graphics driver's control panel, but higher resolutions won't be scaled down by the GPU. Higher resolutions will only work if the monitor can handle them.
* Laptop displays usually don't have scalers and can't display non-native resolutions without GPU scaling. To add other refresh rates, add the refresh rate at the native resolution. The graphics driver will automatically add the refresh rate to lower scaled resolutions.
* Monitors with NVIDIA's G-SYNC processor only support a limited set of resolutions with display scaling. To add non-native resolutions, make sure GPU scaling is enabled in the NVIDIA control panel, or use [Scaled Resolution Editor](https://www.monitortests.com/forum/Thread-Scaled-Resolution-Editor-SRE).
* EDID detailed resolutions are limited to 4095x4095 and 655.35 MHz pixel clock. If a value turns <span style="color:red">**red**</span>, that means it's invalid or out of limits. Use a DisplayID extension block to add resolutions with higher limits.
* Use the timing options to help fill in the values:
    * Manual - Allows the timing parameters to be set manually. The dialog will always open in this mode. See also: Timing parameters explained
    * Automatic PC - Uses standards common with PC monitors. Uses CTA-861 for 4:3/16:9 resolutions up to 1920x1080 @ 60 Hz, VESA DMT for 1360/1366x768 and 1600x900, CVT-RB otherwise.
    * Automatic HDTV - Uses standards common with HDTVs. Uses CTA-861 for all TV resolutions if possible, VESA DMT for 1360/1366x768 and 1600x900, CVT-RB otherwise.
    * Automatic CRT - Uses standards compatible with CRT monitors. Uses VESA DMT for 4:3/5:4 resolutions, CVT otherwise.
    * Native PC/HDTV - Uses the 60 Hz "Automatic" timing parameters for all refresh rates. This may help when trying other refresh rates.
    * Exact - Uses non-standard timing parameters to produce exact integer refresh rates.
    * Exact reduced - Adjusts the "Exact" timing parameters to reduce the pixel clock if possible. This may help when trying higher refresh rates.
    * Exact CRT - Uses timing parameters compatible with CRT monitors to produce exact integer refresh rates.
    * VESA standards:
        * CVT standard - Standard intended for CRT monitors.
        * CVT-RB standard - Standard intended for LCD monitors. Reduces the blanking compared with CVT.
        * CVT-RB2 standard - Newer standard intended for LCD monitors. Reduces the horizontal blanking compared with CVT-RB.
        * GTF standard - Old standard commonly used with CRT monitors.
    * Vertical total calculator - Calculates the vertical total required for the specified refresh rate and pixel clock. This can be used to implement Quick Frame Transport (QFT), which can help reduce crosstalk with backlight strobing at lower refresh rates.
* __Pay attention to pixel clock limits:__
    * Single-link DVI is limited to 165 MHz and dual-link DVI is limited to 330 MHz unless the graphics driver is patched:
        * AMD/ATI Pixel Clock Patcher
        * NVIDIA Pixel Clock Patcher
    * HDMI is treated as single-link DVI unless an "HDMI support" data block is defined in a CTA-861 extension block.
    * HDMI 2.0 requires both an "HDMI support" data block and an "HDMI 2.0 support" data block.
    * HDMI limits depend on the GPU:
        * Newer GPUs with HDMI 2.0 support up to 600 MHz with HDMI 2.0 and up to 340 MHz with HDMI 1.x.
        * AMD HD 7000-series and newer GPUs without HDMI 2.0 support up to 297 MHz. Older GPUs are limited to 165 MHz unless the driver is patched.
        * Intel GPUs without HDMI 2.0 support up to 300.99 MHz.
        * AMD/ATI and Intel also listen to the maximum TMDS clock in the "HDMI support" data block. Make sure it's enabled and set to 340 MHz.
    * DisplayPort limits are listed here: Common pixel clock limits
    * Passive DisplayPort to HDMI adapters are limited to 165 MHz unless the driver is patched.
    * These DisplayPort to HDMI 2.0 active adapters support up to 600 MHz pixel clock (Amazon affiliate links):
        * Plugable DisplayPort 1.2 to HDMI 2.0 Active Adapter
        * Club 3D CAC-1080 DisplayPort 1.4 to HDMI 2.0b HDR Active Adapter
        * Club 3D CAC-1180 Mini DisplayPort 1.4 to HDMI 2.0b HDR Active Adapter

### Standard resolutions:

* Standard resolutions are mostly useful for CRT monitors and for adding lower resolutions with LCD monitors. Do not add the native resolution as a standard resolution.
* AMD/ATI only supports the resolutions in the drop-down list. Other resolutions will be ignored by the driver. These will be listed in gray.
* NVIDIA does not support more than 8 standard resolutions. Additional resolutions will use up detailed resolution slots.
* Standard resolutions are limited to certain aspect ratios: 4:3, 5:4, 16:9, 16:10. Use detailed resolutions for other aspect ratios.
* The horizontal resolution is limited to 256-2288 and must be a multiple of 8. Use detailed resolutions for other resolutions.
* The refresh rate is limited to 60-123 Hz. Use detailed resolutions for other refresh rates.

### Extension blocks:

* GPU-specific limtations:
    * CRU can read extension blocks from displays connected to AMD and NVIDIA GPUs.
    * CRU can't read extension blocks with Intel GPUs or switchable graphics.
    * Older drivers or GPUs may only support up to 3 extension blocks.
