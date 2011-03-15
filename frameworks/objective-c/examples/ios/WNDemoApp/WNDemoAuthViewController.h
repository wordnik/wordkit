/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>
#import <Wordnik/WNClient.h>

@interface WNDemoAuthViewController : UIViewController {
@private
    /** Authentication state label. */
    IBOutlet UILabel *_authState;

    /** Username text field. */
    IBOutlet UITextField *_usernameField;

    /** Password text field. */
    IBOutlet UITextField *_passwordField;

    /** Submit button. */
    IBOutlet UIButton *_submitButton;

    /** Wordnik client. */
    WNClient *_client;
}

- (id) initWithWordnikClient: (WNClient *) client;

- (IBAction) didPressLoginButton: (id) sender;

@end
