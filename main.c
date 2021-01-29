#include <Windows.h>
#include <stdio.h>

void PutDispChangeError(LONG Result)
{
	// DISP_CHANGE_RESTART;
	// DISP_CHANGE_SUCCESSFUL;
	// DISP_CHANGE_FAILED;
	// DISP_CHANGE_BADMODE;
	// DISP_CHANGE_NOTUPDATED;
	// DISP_CHANGE_BADFLAGS;
	// DISP_CHANGE_BADPARAM;
	// DISP_CHANGE_BADDUALVIEW;

	switch (Result)
	{
		case 1:
			puts(" -> DISP_CHANGE_RESTART     - The computer must be restarted for the graphics mode to work.");
			break;
		case 0:
			puts(" -> DISP_CHANGE_SUCCESSFUL  - The settings change was successful.");
			break;
		case -1:
			puts(" -> DISP_CHANGE_FAILED      - The display driver failed the specified graphics mode.");
			break;
		case -2:
			puts(" -> DISP_CHANGE_BADMODE     - The graphics mode is not supported.");
			break;
		case -3:
			puts(" -> DISP_CHANGE_NOTUPDATED  - Unable to write settings to the registry.");
			break;
		case -4:
			puts(" -> DISP_CHANGE_BADFLAGS    - An invalid set of flags was passed in.");
			break;
		case -5:
			puts(" -> DISP_CHANGE_BADPARAM    - An invalid parameter was passed in. This can include an invalid flag or combination of flags.");
			break;
		case -6:
			puts(" -> DISP_CHANGE_BADDUALVIEW - The settings change was unsuccessful because the system is DualView capable.");
			break;
		default:
			printf("Given result does not belong to any constant: %li!\n", Result);
	}
}

int main(void)
{
	DEVMODEA DisplayModeA;
	BOOL Result;
	LONG Result2;
	DWORD TempWidth;

	Result = EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &DisplayModeA); // get the current settings

	if (!Result)
	{
		printf("Getting the display settings failed: %lu (returned from GetLastError)!\n", GetLastError());
		return -1;
	}
	else
	{
		puts("Getting the display settings succeeded.");
	}

	if (DisplayModeA.dmFields | DM_DISPLAYORIENTATION)
	{
		if (DisplayModeA.dmDisplayOrientation == DMDO_DEFAULT) // depending on the orientation the appropriate new orientation will be set
		{
			DisplayModeA.dmDisplayOrientation = DMDO_90;
			puts("The display orientation is set to the default (DMDO_DEFAULT).");
			puts("It will now be changed to DMDO_90.");
		}
		else
		{
			DisplayModeA.dmDisplayOrientation = DMDO_DEFAULT;
			printf("The display orientation is set to something else: %lu (default is zero).\n", DisplayModeA.dmDisplayOrientation);
			puts("It will now be changed to DMDO_DEFAULT.");
		}

		TempWidth = DisplayModeA.dmPelsWidth;
		DisplayModeA.dmPelsWidth = DisplayModeA.dmPelsHeight;
		DisplayModeA.dmPelsHeight = TempWidth;

		DisplayModeA.dmFields = DM_PELSHEIGHT | DM_PELSWIDTH;

		Result2 = ChangeDisplaySettingsA(&DisplayModeA, 0);

		if (Result2 == DISP_CHANGE_SUCCESSFUL)
		{
			puts("New settings were successfully set.");
		}
		else
		{
			printf("Applying the new display settings failed: %li (returned from ChangeDisplaySettings)!\n", Result2);
			PutDispChangeError(Result2);
			return -2;
		}
	}
	else
	{
		puts("Display orientation field was not initialized!");
		return -3;
	}

	return 0;
}