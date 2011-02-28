/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>

@class WNDefinitionView;

/**
 * @ingroup classes_ios
 *
 * The WNDefinitionViewDelegate protocol declares the interface that must be implemented by
 * WNDefinitionView delegates.
 */
@protocol WNDefinitionViewDelegate <NSObject>
@optional

/**
 * Sent when the user navigates to an internet-based URL. The delegate may choose to open the MobileSafari
 * application, or alternatively, display the web page directly in the application's UI.
 *
 * @param definitionView The sending definition view.
 * @param URL The URL to which the user has attempted to navigate.
 */
- (void) definitionView: (WNDefinitionView *) definitionView didNavigateToURL: (NSURL *) URL;

/**
 * Sent when the user selects a new word for additional detail.
 *
 * @param definitionView The sending definition view.
 * @param word The word string selected by the user.
 */
- (void) definitionView: (WNDefinitionView *) definitionView didSelectWordString: (NSString *) word;

@end
