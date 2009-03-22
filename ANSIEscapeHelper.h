//
//  ANSIEscapeHelper.h
//  AnsiColorsTest
//
//  Created by Ali Rantakari on 18.3.09.
//  Copyright 2009 Ali Rantakari. All rights reserved.
//

#import <Cocoa/Cocoa.h>


// the CSI (Control Sequence Initiator) -- i.e. "escape sequence prefix".
// (add your own CSI:Miami joke here)
#define kANSIEscapeCSI			@"\033["

// the end byte of an SGR (Select Graphic Rendition)
// ANSI Escape Sequence
#define kANSIEscapeSGREnd		@"m"



/*!
 @enum			sgrCode
 
 @abstract		SGR (Select Graphic Rendition) ANSI control codes.
 */
enum sgrCode
{
	SGRCodeNoneOrInvalid =		-1,
	
	SGRCodeAllReset =			0,
	
	SGRCodeIntensityBold =		1,
	SGRCodeIntensityFaint =		2,
	SGRCodeIntensityNormal =	22,
	
	SGRCodeItalicOn =			3,
	
	SGRCodeUnderlineSingle =	4,
	SGRCodeUnderlineDouble =	21,
	SGRCodeUnderlineNone =		24,
	
	SGRCodeFgBlack =		30,
	SGRCodeFgRed =			31,
	SGRCodeFgGreen =		32,
	SGRCodeFgYellow =		33,
	SGRCodeFgBlue =			34,
	SGRCodeFgMagenta =		35,
	SGRCodeFgCyan =			36,
	SGRCodeFgWhite =		37,
	SGRCodeFgReset =		39,
	
	SGRCodeBgBlack =		40,
	SGRCodeBgRed =			41,
	SGRCodeBgGreen =		42,
	SGRCodeBgYellow =		43,
	SGRCodeBgBlue =			44,
	SGRCodeBgMagenta =		45,
	SGRCodeBgCyan =			46,
	SGRCodeBgWhite =		47,
	SGRCodeBgReset =		49
};






/*!
 @class		ANSIEscapeHelper
 
 @abstract	Contains helper methods for dealing with strings
			that contain ANSI escape sequences for formatting (colors,
			underlining, bold etc.)
 */
@interface ANSIEscapeHelper : NSObject
{
	NSFont *font;
	NSMutableDictionary *ansiColors;
}

/*!
 @property		font
 
 @abstract		The font to use when creating string formatting attribute values.
 */
@property(retain) NSFont *font;

/*!
 @property		ansiColors
 
 @abstract		The colors to use for displaying ANSI colors.
 
 @discussion	Keys in this dictionary should be NSNumber objects containing SGR code
				values from the sgrCode enum. The corresponding values for these keys
				should be NSColor objects. If this property is nil or if it doesn't
				contain a key for a specific SGR code, the default color will be used
				instead.
 */
@property(retain) NSMutableDictionary *ansiColors;


/*!
 @method		attributedStringWithANSIEscapedString:
 
 @abstract		Returns an attributed string that corresponds both in contents
				and formatting to a given string that contains ANSI escape
				sequences.
 
 @param aString			A String containing ANSI escape sequences
 
 @result		An attributed string that mimics as closely as possible
				the formatting of the given attributed string.
 */
- (NSAttributedString*) attributedStringWithANSIEscapedString:(NSString*)aString;


/*!
 @method		ansiEscapedStringWithAttributedString:
 
 @abstract		Returns a string containing ANSI escape sequences that corresponds
				both in contents and formatting to a given attributed string.
 
 @param aAttributedString		An attributed string
 
 @result		A string that mimics as closely as possible
				the formatting of the given attributed string with
				ANSI escape sequences.
 */
- (NSString*) ansiEscapedStringWithAttributedString:(NSAttributedString*)aAttributedString;


/*!
 @method		escapeCodesForString:cleanString:
 
 @abstract		Returns an array of SGR codes and their locations from a
				string containing ANSI escape sequences as well as a "clean"
				version of the string (i.e. one without the ANSI escape
				sequences.)
 
 @param aString			A String containing ANSI escape sequences
 @param aCleanString	Upon return, contains a "clean" version of aString (i.e. aString
						without the ANSI escape sequences)
 
 @result		An array of NSDictionary objects, each of which has
				an NSNumber value for the key "code" (specifying an SGR code) and
				another NSNumber value for the key "location" (specifying the
				location of the code within aCleanString.)
 */
- (NSArray*) escapeCodesForString:(NSString*)aString cleanString:(NSString**)aCleanString;


/*!
 @method		ansiEscapedStringWithCodesAndLocations:cleanString:
 
 @abstract		Returns a string containing ANSI escape codes for formatting based
				on a string and an array of SGR codes and their locations within
				the given string.
 
 @param aCodesArray		An array of NSDictionary objects, each of which should have
						an NSNumber value for the key "code" (specifying an SGR
						code) and another NSNumber value for the key "location"
						(specifying the location of this SGR code in aCleanString.)
 @param aCleanString	The string to which to insert the ANSI escape codes
						described in aCodesArray.
 
 @result		A string containing ANSI escape codes.
 */
- (NSString*) ansiEscapedStringWithCodesAndLocations:(NSArray*)aCodesArray cleanString:(NSString*)aCleanString;


/*!
 @method		attributesForString:cleanString:
 
 @abstract		Convert ANSI escape sequences in a string to string formatting attributes.
 
 @discussion	Given a string with some ANSI escape sequences in it, this method returns
				attributes for formatting the specified string according to those ANSI
				escape sequences as well as a "clean" (i.e. free of the escape sequences)
				version of this string.
 
 @param aString			A String containing ANSI escape sequences
 @param aCleanString	Upon return, contains a "clean" version of aString (i.e. aString
						without the ANSI escape sequences)
 
 @result		An array containing NSDictionary objects, each of which has keys "range"
				(an NSValue containing an NSRange, specifying the range for the
				attribute within the "clean" version of aString), "attributeName" (an
				NSString) and "attributeValue" (an NSObject). You may use these as
				arguments for NSMutableAttributedString's methods for setting the
				visual formatting.
 */
- (NSArray*) attributesForString:(NSString*)aString cleanString:(NSString**)aCleanString;


/*!
 @method		sgrCode:endsFormattingIntroducedByCode:
 
 @abstract		Whether the occurrence of a given SGR code would end the formatting run
				introduced by another SGR code.
 
 @discussion	For example, SGRCodeFgReset, SGRCodeAllReset or any SGR code
				specifying a foreground color would end the formatting run
				introduced by a foreground color -specifying SGR code.
 
 @param endCode		The SGR code to test as a candidate for ending the formatting run
					introduced by startCode
 @param startCode	The SGR code that has introduced a formatting run
 
 @result		YES if the occurrence of endCode would end the formatting run
				introduced by startCode, NO otherwise.
 */
- (BOOL) sgrCode:(enum sgrCode)endCode endsFormattingIntroducedByCode:(enum sgrCode)startCode;


/*!
 @method		colorForSGRCode:
 
 @abstract		Returns the color to use for displaying a specific ANSI color.
 
 @discussion	This method first considers the values set in the ansiColors
				property and only then the standard basic colors (NSColor's
				redColor, blueColor etc.)
 
 @param code	An SGR code that specifies an ANSI color.
 
 @result		The color to use for displaying the ANSI color specified by code.
 */
- (NSColor*) colorForSGRCode:(enum sgrCode)code;


/*!
 @method		sgrCodeForColor:isForegroundColor:
 
 @abstract		Returns an SGR code that corresponds to a given color.
 
 @discussion	This method matches colors to their equivalent SGR codes
				by going through the colors specified in the ansiColors
				dictionary, and if ansiColors is null or if a match is
				not found there, by comparing the given color to the
				standard basic colors (NSColor's redColor, blueColor
				etc.) The comparison is done simply by checking for
				equality.
 
 @param aColor			The color to get a corresponding SGR code for
 @param aForeground		Whether you want a foreground or background color code
 
 @result		SGR code that corresponds with aColor.
 */
- (enum sgrCode) sgrCodeForColor:(NSColor*)aColor isForegroundColor:(BOOL)aForeground;

@end
