/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>

@class WNDefinitionViewController;

/**
 * @ingroup classes_ios
 *
 * The WNDefinitionViewControllerDelegate protocol declares the interface that must be implemented by
 * WNDefinitionViewController delegates.
 */
@protocol WNDefinitionViewControllerDelegate <NSObject>
@optional

/**
 * Sent when the user requests that the definition view controller be dismissed.
 *
 * @param viewController The sending definition view controller.
 */
- (void) definitionViewControllerDidRequestClose: (WNDefinitionViewController *) viewController;

@end
