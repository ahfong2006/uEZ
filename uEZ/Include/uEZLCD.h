/**
 *	@file 	uEZLCD.h
 *  @brief 	uEZ LCD Interface
 *
 *	The uEZ interface which maps to low level LCD drivers.
 */
#ifndef _UEZ_LCD_H_
#define _UEZ_LCD_H_

/*--------------------------------------------------------------------------
 * uEZ(R) - Copyright (C) 2007-2011 Future Designs, Inc.
 *--------------------------------------------------------------------------
 * This file is part of the uEZ(R) distribution.  See the included
 * uEZLicense.txt or visit http://www.teamfdi.com/uez for details.
 *
 *    *===============================================================*
 *    |  Future Designs, Inc. can port uEZ(tm) to your own hardware!  |
 *    |             We can get you up and running fast!               |
 *    |      See http://www.teamfdi.com/uez for more details.         |
 *    *===============================================================*
 *
 *-------------------------------------------------------------------------*/

#include "uEZTypes.h"
#include "uEZErrors.h"
#include <Types/LCD.h>

/**
 *	@struct T_uezLCDConfiguration
 */
typedef struct {
    TUInt32 iXResolution;
    TUInt32 iYResolution;
    T_uezLCDColorDepth iColorDepth;
    T_uezLCDPixelOrder iPixelOrder;
    TUInt32 iCurrentFrame;
    TUInt32 iNumTotalFrames;
    TUInt32 iBytesPerVisibleRaster;
    TUInt32 iBytesPerWholeRaster;
    TUInt32 iNumBacklightLevels;
} T_uezLCDConfiguration;

/**
 *	@struct T_uezLCDScreensaverInfo
 */
typedef struct {
    TUInt32 iMSAnimationRefresh;
    TUInt32 iMSTillDim;
    TUInt32 iMSTillAnimation;
    TUInt32 iMSTillSleep;
    TUInt32 iAnimationBacklightLevel;
    TUInt32 iDimBacklightLevel;
    void (*iCallback_AnimationStart)();
    void (*iCallback_AnimationUpdate)();
    void (*iCallback_AnimationSleep)();
    void (*iCallback_AnimationEnd)();
} T_uezLCDScreenSaverInfo;

/**
 *	Open up access to the LCD bank.
 *
 *	@param [in] 	*aName		ointer to name of LCD display (usually "LCD")
 *	@param [out]	*aLCDDevice	Pointer to LCD device handle to be returned
 *
 *	@return		T_uezError
 */
T_uezError UEZLCDOpen(
            const char * const aName, 
            T_uezDevice *aLCDDevice);
			
/**
 *	End access to the LCD bank.
 *
 *	@param [in]	aLCDDevice		LCD Device handle to close
 *
 *	@return		T_uezError
 */						
T_uezError UEZLCDClose(T_uezDevice aLCDDevice);

/**
 *	Get information about the LCD device.
 *
 *	@param [in]		aLCDDevice				LCD Device handle
 *	@param [out]	*aConfiguration		Pointer to a Structure for returned data
 *
 *	@return		T_uezError
 */		
T_uezError UEZLCDGetInfo(
            T_uezDevice aLCDDevice,
            T_uezLCDConfiguration *aConfiguration);
						
/**
 *	Returns a pointer to the frame memory in the LCD display.
 *
 *	@param [in]		aLCDDevice				LCD Device handle
 *	@param [in]		aFrame						Index to frame (0 based)
 *	@param [out]	**aFrameBuffer		Pointer to base address
 *
 *	@return		T_uezError
 */
T_uezError UEZLCDGetFrame(
            T_uezDevice aLCDDevice, 
            TUInt32 aFrame, 
            void **aFrameBuffer);
						
/**
 *	Makes the passed frame the actively viewed frame on the LCD 
 *  (if not already).
 *
 *	@param [in]		aLCDDevice				LCD Device handle
 *	@param [in]		aFrame						Index to frame (0 based)
 *
 *	@return		T_uezError
 */
T_uezError UEZLCDShowFrame(
            T_uezDevice aLCDDevice, 
            TUInt32 aFrame);

/**
 *	Turns ON the LCD display.
 *
 *	@param [in]		aLCDDevice				LCD Device handle
 *
 *	@return		T_uezError
 */						
T_uezError UEZLCDOn(T_uezDevice aLCDDevice);

/**
 *	Turns OFF the LCD display.
 *
 *	@param [in]		aLCDDevice				LCD Device handle
 *
 *	@return		T_uezError
 */		
T_uezError UEZLCDOff(T_uezDevice aLCDDevice);

/**
 *	Turns on or off the backlight.  A value of 0 is off and values of 1 
 *  or higher is higher levels of brightness (dependent on the LCD 
 *  display).  If a display is on/off only, this value will be 1 or 0 
 *  respectively.
 *
 *	@param [in]		aLCDDevice	LCD Device handle
 *	@param [in]		aLevel    	Level of backlight
 *
 *	@return		T_uezError
 */	
T_uezError UEZLCDBacklight(
            T_uezDevice aLCDDevice, 
            TUInt32 aLevel);
						
/**
 *	Change the color of a palette entry given the red, green, blue
 *  component of a particular color index.  The color components are
 *  expressed in full 16-bit values at a higher resolution than
 *  the hardware can usually perform.  The color is down shifted to what
 *  the hardware can handle.
 *
 *	@param [in] aLCDDevice				Handle to opened LCD device.
 * 	@param [in] aColorIndex		Index to palette entry
 *  @param [in] aRed					Red value
 *  @param [in] aGreen				Green value
 *  @param [in] aBlue					Blue value
 *
 *	@return		T_uezError
 */	
T_uezError UEZLCDSetPaletteColor(
            T_uezDevice aLCDDevice,
            TUInt32 aColorIndex, 
            TUInt16 aRed, 
            TUInt16 aGreen, 
            TUInt16 aBlue);
						
/**
 *	Returns the current backlight level from the LCD and optionally
 *  returns the maximum number of levels.
 *
 *	@param [in] 	aLCDDevice				Handle to opened LCD device.
 * 	@param [out] 	*aLevel					Level of backlight
 *  @param [out] 	*aNumLevels				Total number of levels
 *
 *	@return		T_uezError
 */	
T_uezError UEZLCDGetBacklightLevel(
            T_uezDevice aLCDDevice, 
            TUInt32 *aLevel,
            TUInt32 *aNumLevels);
						
#define UEZLCDSetBacklightLevel(lcd, level)     UEZLCDBacklight(lcd, level)


T_uezError UEZLCDWaitForVerticalSync(T_uezDevice aLCDDevice, TUInt32 aTimeout);

/**
 *	Starts the Screensaver Task
 *
 *	@param [in] 	aLCDDevice				Handle to opened LCD device.
 * 	@param [out] 	*aLCDScreenSaverInfo	Screen saver info structure
 *
 *	@return		T_uezError
 */	
T_uezError UEZLCDScreensaverStart(
    T_uezDevice aLCDDevice,
    const T_uezLCDScreenSaverInfo *aLCDScreenSaverInfo);

/**
 *	Starts the Screensaver Task
 *
 *	@return		T_uezError
 */	
T_uezError UEZLCDScreensaverStop();

/**
 *	Wakes the screen saver. This can be called periodically to prevent
 *  the screen saver from appearing.
 *
 *	@return		T_uezError
 */	
void UEZLCDScreensaverWake();

/**
 *	How to deturmine if the screen saver is active
 *
 *	@return		TBool
 */	
TBool UEZLCDScreensaverIsActive();

#endif // _UEZ_LCD_H_

/*-------------------------------------------------------------------------*
 * End of File:  uEZLCD.h
 *-------------------------------------------------------------------------*/
