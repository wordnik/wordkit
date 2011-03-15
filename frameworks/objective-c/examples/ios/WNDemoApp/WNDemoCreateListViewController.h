/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>
#import <Wordnik/Wordnik.h>

@interface WNDemoCreateListViewController : UIViewController <UITextFieldDelegate, WNClientObserver> {
@private
    /** List name field */
    IBOutlet UITextField *_nameField;

    /** List description field. */
    IBOutlet UITextField *_descriptionField;
    
    /** Wordnik client. */
    WNClient *_client;
}

- (id) initWithWordnikClient: (WNClient *) client;

- (IBAction) didPressCreateButton: (id) sender;

@end
