/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>
#import <Wordnik/WNClient.h>

@interface WNDemoWordInfoViewController : UIViewController {
    /** Word text field. */
    IBOutlet UITextField *_wordField;
    
    /** Lookup button. */
    IBOutlet UIButton *_lookupButton;
    
    /** Indicator shown while request is running. */
    IBOutlet UIActivityIndicatorView *_runningIndicator;
    
    /** The result text field */
    IBOutlet UITextView *_resultTextView;
    
    /** Wordnik client. */
    WNClient *_client;
}

- (id) initWithWordnikClient: (WNClient *) client;

- (IBAction) didPressLookupButton: (id) sender;

@end
