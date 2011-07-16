//
//  IFSheetController.h
//  IFSheetController
//
//  Created by Itai Ferber on 7/15/11.
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

#import <Foundation/Foundation.h>
#import "IFSheetControllerDelegate.h"

#if !__has_feature(objc_arc)
	#import "MAZeroingWeakRef.h"
#endif

/*!
 The IF_ERROR_REPORTING_LEVEL macro allows you to set the level at which IFSheetController will log any errors that it encounters. If the
 macro expands to 1 in the preprocessor, any errors encountered will be logged and IFSheet Controller will attempt to recover from them; if
 it expands to 0, it will silently recover from those errors.
 */
#ifndef IF_ERROR_REPORTING_LEVEL
#define IF_ERROR_REPORTING_LEVEL 1
#endif

/*!
 @class IFSheetController
 @abstract A sheet controller allowing for easy manipulation of sheet windows through Interface Builder.
 @discussion IFSheetController is a class that very easily allows you to set up and manipulate sheets without writing your own code. At the
 most basic level, all the sheet controller needs is a parent window and sheet window set in Interface Builder, and buttons executing the
 `openSheet...:` and `closeSheet...:` methods. If any customization is to be performed, a delegate implementing some of the methods found
 in the IFSheetControllerDelegate protocol is required.
 
 For its delegate when Automatic Reference Counting is not enabled, IFSheetController employs Michael Ash's MAZeroingWeakRef to avoid
 messaging a dangling pointer. The license for MAZeroingWeakRef is included below:
 */

/*! Copyright (c) 2010, Michael Ash
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 Neither the name of Michael Ash nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
@interface IFSheetController : NSObject {
	__strong NSWindow *_parentWindow;
	__strong NSWindow *_sheet;
	BOOL isOpen;
#if __has_feature(objc_arc)
	__weak id <IFSheetControllerDelegate> _delegate;
#else
	__strong MAZeroingWeakRef *_delegateReference;
#endif
}

@property (strong) IBOutlet NSWindow *parentWindow;
@property (strong) IBOutlet NSWindow *sheet;
@property (readonly) BOOL isOpen;
@property (weak) IBOutlet id <IFSheetControllerDelegate> delegate;

/*!
 Opens the assigned sheet without messaging the delegate. If either the parent window or sheet window are nil, this does nothing (unless
 IF_ERROR_REPORTING_LEVEL is set to 1, in which case it will log an error).
 @param sender the user interface control that sent the message
 */
- (IBAction)openSheet:(id)sender;

/*!
 Opens the assigned sheet, and if a delegate exists, messages the delegate for a response. The delegate will get the chance to deny opening
 the sheet, or taking further action before and after the sheet is opened. If either the parent window or sheet window are nil, this does 
 nothing (unless IF_ERROR_REPORTING_LEVEL is set to 1, in which case it will log an error).
 @param sender the user interface control that sent the message
 */
- (IBAction)openSheetAndMessageDelegate:(id)sender;

/*!
 Closes the assigned sheet without messaging the delegate. If either the parent window or sheet window are nil, this does nothing (unless
 IF_ERROR_REPORTING_LEVEL is set to 1, in which case it will log an error).
 @param sender the user interface control that sent the message
 */
- (IBAction)closeSheet:(id)sender;

/*!
 Closes the assigned sheet, and if a delegate exists, messages the delegate for a response. The delegate will get the chance to deny closing
 the sheet, or taking further action before and after the sheet is closed. If either the parent window or sheet window are nil, this does
 nothing (unless IF_ERROR_REPORTING_LEVEL is set to 1, in which case it will log an error).
 @param sender the user interface control that sent the message
 */
- (IBAction)closeSheetAndMessageDelegate:(id)sender;

@end