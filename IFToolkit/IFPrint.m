//
//  IFPrint.m
//  IFToolkit
//
//  Created by Itai Ferber on 7/16/11.
//  Copyright 2011 Itai Ferber. All rights reserved.
//

/*
 Copyright (C) 2011 by Itai Ferber
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#import "IFPrint.h"

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