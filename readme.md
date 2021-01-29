# Display Orientation Switcher

This is a small windows tool which toggles between landscape and portrait mode of the main display device.
Currently the program toggles between a rotation of 90 degrees clockwise and the default orientation.

## Notice

As stated in Microsoft's documentation the functions used in this program do not support Windows 2000.
It is also recommended to use the program in a command-line to see all relevant debug info.

## Sources

The documentation provided by Microsoft is sadly a bit rough and undetailed, so I had to look for someone who knew how the functions worked.

 * https://stackoverflow.com/questions/30310000/how-to-perform-same-action-as-changing-windows-7-display-from-landscape-to-portr
 * https://stackoverflow.com/questions/28104898/controlling-windows-screen-orientation-in-c-qt-windows
 * https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-changedisplaysettingsa
 * https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-devmodea
 * https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enumdisplaysettingsa