//
//  IFSheetControllerDelegate.h
//  IFSheetController
//
//  Created by Itai Ferber on 7/15/11.
//  Copyright 2011 Itai Ferber. All rights reserved.
//

#import <Foundation/Foundation.h>

@class IFSheetController;
@protocol IFSheetControllerDelegate <NSObject>
@optional
/*!
 Requests the delegate's permission for the given sheet controller to open its sheet.
 @param theController the sheet controller requesting permission
 @return whether the controller should open the sheet
 */
- (BOOL)sheetControllerShouldOpenSheet:(IFSheetController *)theController;

/*!
 Notifies the delegate that the given sheet controller will open its sheet.
 @param theController the sheet controller notifying the delegate
 */
- (void)sheetControllerWillOpenSheet:(IFSheetController *)theController;

/*!
 Notifies the delegate that the given sheet controller opened its sheet.
 @param theController the sheet controller notifying its delegate
 */
- (void)sheetControllerDidOpenSheet:(IFSheetController *)theController;

/*!
 Requests the delegate's permission for the given sheet controller to close its sheet.
 @param theController the sheet controller requesting permission
 @return whether the controller should close the sheet
 */
- (BOOL)sheetControllerShouldCloseSheet:(IFSheetController *)theController;

/*!
 Notifies the delegate that the given sheet controller will close its sheet.
 @param theController the sheet controller notifying its delegate
 */
- (void)sheetControllerWillCloseSheet:(IFSheetController *)theController;

/*!
 Notifies the delegate that the given sheet controller will close its sheet.
 @param theController the sheet controller notifying its delegate
 */
- (void)sheetControllerDidCloseSheet:(IFSheetController *)theController;

@end