/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>
#import <Wordnik/Wordnik.h>

@interface WNDemoWordOfTheDayViewController : UIViewController {
@private    
    /** The result text field */
    IBOutlet UITextView *_resultTextView;
    
    /** Wordnik client. */
    WNClient *_client;
}

- (id) initWithWordnikClient: (WNClient *) client;

@end
