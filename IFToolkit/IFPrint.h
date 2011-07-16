//
//  IFPrint.h
//  IFToolkit
//
//  Created by Itai Ferber on 7/16/11.
//  Copyright 2011 Itai Ferber. All rights reserved.
//

#ifndef IFToolkit_IFPrint_h
#define IFToolkit_IFPrint_h

#import <Foundation/Foundation.h>

/*!
 @function IFPrint
 @abstract NSLog-like printing without the extra crud.
 @discussion IFPrint allows you to print information to stdout without going through the hoops that NSLog does. You get the formatting
 niceties of NSLog, without logging information to the system, and printing an extra timestamp.
 @param format the format to print, followed by the arguments
 */
void IFPrint (NSString *format, ...) NS_FORMAT_FUNCTION(1, 2);
void IFPrint (NSString *format, ...) {
	if (!format) return;
	va_list arguments;
	va_start(arguments, format);
	
	NSString *output = [[NSString alloc] initWithFormat:format arguments:arguments];
	va_end(arguments);
	
	fputs([output UTF8String], stdout);
#if !__has_feature(objc_arc)
	[output release];
#endif
}

/*!
 @function IFFPrint
 @abstract NSLog-like printing without the extra crud.
 @discussion IFFPrint allows you to print information to a given file handle without going through the hoops that NSLog does. You get the 
 formatting  niceties of NSLog, without logging information to the system, and printing an extra timestamp. You even get more customization
 by providing your own file handle to print to.
 @param file the file handle to print to
 @param format the format to print, followed by the arguments
 */
void IFFPrint (FILE *file, NSString *format, ...) NS_FORMAT_FUNCTION(2, 3);
void IFFPrint (FILE *file, NSString *format, ...) {
	if (!format) return;
	va_list arguments;
	va_start(arguments, format);
	
	NSString *output = [[NSString alloc] initWithFormat:format arguments:arguments];
	va_end(arguments);
	
	fputs([output UTF8String], file == NULL ? stdout : file);
#if !__has_feature(objc_arc)
	[output release];
#endif
}

#endif
