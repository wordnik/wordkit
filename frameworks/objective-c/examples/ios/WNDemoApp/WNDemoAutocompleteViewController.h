/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>
#import <Wordnik/Wordnik.h>

@interface WNDemoAutocompleteViewController : UIViewController <UITextFieldDelegate, WNClientObserver> {
@private
    /** Word text field. */
    IBOutlet UITextField *_wordField;

    /** Indicator shown while request is running. */
    IBOutlet UIActivityIndicatorView *_runningIndicator;
    
    /** The result text field */
    IBOutlet UITextView *_resultTextView;

    /** The current autocomplete request */
    WNRequestTicket *_requestTicket;
    
    /** Wordnik client. */
    WNClient *_client;
}

- (id) initWithWordnikClient: (WNClient *) client;

@end
