//
//  IFSheetController.m
//  IFSheetController
//
//  Created by Itai Ferber on 7/15/11.
//  Copyright 2011 Itai Ferber. All rights reserved.
//

#import "IFSheetController.h"

#ifdef IF_ERROR_REPORTING_LEVEL
#define IFLog(...) NSLog(__VA_ARGS__)
#else
#define IFLog(...)
#endif

@implementation IFSheetController

#pragma mark - Synthesis
@synthesize parentWindow = _parentWindow;
@synthesize sheet = _sheet;
@synthesize isOpen = _isOpen;

#pragma mark - Delegate Synthesis
- (void)setDelegate:(id)theDelegate {
#if __has_feature(objc_arc)
	_delegate = theDelegate;
#else
	[_delegateReference release];
	_delegateReference = [[MAZeroingWeakRef alloc] initWithTarget:theDelegate];
#endif
}

- (id)delegate {
#if __has_feature(objc_arc)
	return _delegate;
#else
	return [_delegateReference target];
#endif
}

#pragma mark - Sheet Methods
- (IBAction)openSheet:(id)sender {
	if (_isOpen) return;
	if (self.parentWindow && self.sheet) {
		[NSApp beginSheet:self.sheet modalForWindow:self.parentWindow modalDelegate:self didEndSelector:@selector(sheetDidEnd:returnCode:contextInfo:) contextInfo:NULL];
		_isOpen = YES;
	} else {
		IFLog(@"Could not open sheet! Either parent window (%@) or sheet (%@) is nil!", self.parentWindow, self.sheet);
	}
}

- (IBAction)openSheetAndMessageDelegate:(id)sender {
	if (_isOpen) return;
	if (self.parentWindow && self.sheet) {
#if __has_feature(objc_arc)
		id <IFSheetControllerDelegate> delegate = _delegate;
#else
		id <IFSheetControllerDelegate> delegate = [_delegateReference target];
#endif
		
		BOOL shouldOpen = YES;
		if (delegate && [delegate respondsToSelector:@selector(sheetControllerShouldOpenSheet:)]) {
			shouldOpen = [delegate sheetControllerShouldOpenSheet:self];
		}
		
		if (!shouldOpen) return;
		if (delegate && [delegate respondsToSelector:@selector(sheetControllerWillOpenSheet:)]) {
			[delegate sheetControllerWillOpenSheet:self];
		}
		
		[NSApp beginSheet:self.sheet modalForWindow:self.parentWindow modalDelegate:self didEndSelector:@selector(sheetDidEnd:returnCode:contextInfo:) contextInfo:NULL];
		_isOpen = YES;
		
		if (delegate && [delegate respondsToSelector:@selector(sheetControllerDidOpenSheet:)]) {
			[delegate sheetControllerDidOpenSheet:self];
		}
	} else {
		IFLog(@"Could not open sheet! Either parent window (%@) or sheet (%@) is nil!", self.parentWindow, self.sheet);
	}
}

- (IBAction)closeSheet:(id)sender {
	if (!_isOpen) return;
	if (self.parentWindow && self.sheet) {
		[NSApp endSheet:self.sheet];
		_isOpen = NO;	
	} else {
		IFLog(@"Could not close sheet! Either parent window (%@) or sheet (%@) is nil!", self.parentWindow, self.sheet);
	}
}

- (IBAction)closeSheetAndMessageDelegate:(id)sender {
	if (!_isOpen) return;
	if (self.parentWindow && self.sheet) {
#if __has_feature(objc_arc)
		id <IFSheetControllerDelegate> delegate = _delegate;
#else
		id <IFSheetControllerDelegate> delegate = [_delegateReference target];
#endif
		
		BOOL shouldClose = YES;
		if (delegate && [delegate respondsToSelector:@selector(sheetControllerShouldCloseSheet:)]) {
			shouldClose = [delegate sheetControllerShouldCloseSheet:self];
		}
		
		if (!shouldClose) return;
		if (delegate && [delegate respondsToSelector:@selector(sheetControllerWillCloseSheet:)]) {
			[delegate sheetControllerWillCloseSheet:self];
		}
		
		[NSApp endSheet:self.sheet];
		_isOpen = NO;
		
		if (delegate && [delegate respondsToSelector:@selector(sheetControllerDidCloseSheet:)]) {
			[delegate sheetControllerDidCloseSheet:self];
		}
	} else {
		IFLog(@"Could not close sheet! Either parent window (%@) or sheet (%@) is nil!", self.parentWindow, self.sheet);
	}
}

- (void)sheetDidEnd:(NSWindow *)theSheet returnCode:(NSInteger)theCode contextInfo:(void *)theInfo {
	[self.sheet orderOut:nil];
}

@end