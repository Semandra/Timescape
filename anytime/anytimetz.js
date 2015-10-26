/*****************************************************************************
 *  FILE:  anytimetz.js - The Any+Time(TM) JavaScript Library
 *                        Basic Time Zone Support (source)
 *  VERSION: 4.1112
 *
 *  Copyright 2010 Andrew M. Andrews III (www.AMA3.com). Some Rights 
 *  Reserved. This work licensed under the Creative Commons Attribution-
 *  Noncommercial-Share Alike 3.0 Unported License except in jurisdicitons
 *  for which the license has been ported by Creative Commons International,
 *  where the work is licensed under the applicable ported license instead.
 *  For a copy of the unported license, visit
 *  http://creativecommons.org/licenses/by-nc-sa/3.0/
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300,
 *  San Francisco, California, 94105, USA.  For ported versions of the
 *  license, visit http://creativecommons.org/international/
 *
 *  Alternative licensing arrangements may be made by contacting the
 *  author at http://www.AMA3.com/contact/
 *
 *  This file adds basic labels for major time zones to the Any+Time(TM)
 *  JavaScript Library.  Time zone support is extremely complicated, and
 *  ECMA-262 (JavaScript) provides little support.  Developers are expected
 *  to tailor this file to meet their needs, mostly by removing lines that
 *  are not required by their users, and/or by removing either abbreviated
 *  (before double-dash) or long (after double-dash) names from the strings.
 *  
 *  Note that there is no automatic detection of daylight savings time
 *  (AKA summer time), due to lack of support in JavaScript and the 
 *  time-prohibitive complexity of attempting such support in code.
 *  If you want to take a stab at it, let me know; if you want to pay me
 *  large sums of money to add it, again, let me know. :-p
 *  
 *  This file should be included AFTER anytime.js (or anytimec.js) in any
 *  HTML page that requires it.
 *
 *  Any+Time is a trademark of Andrew M. Andrews III.
 ****************************************************************************/

//=============================================================================
//  AnyTime.utcLabel is an array of arrays, indexed by UTC offset IN MINUTES
//  (not hours-and-minutes).  This is used by AnyTime.Converter to display
//  time zone labels when the "%@" format specifier is used.  It is also used
//  by AnyTime.widget() to determine which time zone labels to offer as valid
//  choices when a user attempts to change the time zone.  NOTE: Positive
//  indicies are NOT signed.
//
//  Each sub-array contains a series of strings, each of which is a label
//  for a time-zone having the corresponding UTC offset.  The first string in
//  each sub-array is the default label for that UTC offset (the one used by
//  AnyTime.Converter.format() if utcFormatOffsetSubIndex is not specified and
//  setUtcFormatOffsetSubIndex() is not called.
//=============================================================================

AnyTime.utcLabel = [];
AnyTime.utcLabel[-720]=['UTC-12:00'];
AnyTime.utcLabel[-660]=['UTC-11:00'];
AnyTime.utcLabel[-600]=['UTC-10:00'];
AnyTime.utcLabel[-570]=['UTC-9:30'];
AnyTime.utcLabel[-540]=['UTC-9:00'];
AnyTime.utcLabel[-480]=['UTC-8:00'];
AnyTime.utcLabel[-420]=['UTC-7:00'];
AnyTime.utcLabel[-360]=['UTC-6:00'];
AnyTime.utcLabel[-300]=['UTC-5:00'];
AnyTime.utcLabel[-270]=['UTC-4:30'];
AnyTime.utcLabel[-240]=['UTC-4:00'];
AnyTime.utcLabel[-210]=['UTC-3:30'];
AnyTime.utcLabel[-180]=['UTC-3:00'];
AnyTime.utcLabel[-150]=['UTC-2:30'];
AnyTime.utcLabel[-120]=['UTC-2:00'];
AnyTime.utcLabel[-60]=['UTC-1:00'];
AnyTime.utcLabel[0]=['UTC'];
AnyTime.utcLabel[60]=['UTC+1:00'];
AnyTime.utcLabel[120]=['UTC+2:00'];
AnyTime.utcLabel[180]=['UTC+3:00'];
AnyTime.utcLabel[210]=['UTC+3:30'];
AnyTime.utcLabel[240]=['UTC+4:00'];
AnyTime.utcLabel[270]=['UTC+4:30'];
AnyTime.utcLabel[300]=['UTC+5:00'];
AnyTime.utcLabel[330]=['UTC+5:30'];
AnyTime.utcLabel[345]=['UTC+5:45'];
AnyTime.utcLabel[360]=['UTC+6:00'];
AnyTime.utcLabel[390]=['UTC+6:30'];
AnyTime.utcLabel[420]=['UTC+7:00'];
AnyTime.utcLabel[480]=['UTC+8:00'];
AnyTime.utcLabel[540]=['UTC+9:00'];
AnyTime.utcLabel[570]=['UTC+9:30'];
AnyTime.utcLabel[600]=['UTC+10:00'];
AnyTime.utcLabel[630]=['UTC+10:30'];
AnyTime.utcLabel[660]=['UTC+11:00'];
AnyTime.utcLabel[690]=['UTC+11:30'];
AnyTime.utcLabel[720]=['UTC+12:00'];
AnyTime.utcLabel[765]=['UTC+12:45'];
AnyTime.utcLabel[780]=['UTC+13:00'];
AnyTime.utcLabel[840]=['UTC+14:00'];

//
//END OF FILE
//