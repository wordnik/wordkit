/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import <UIKit/UIKit.h>

#import <Wordnik/WNClient.h>

@interface WNDemoModifyWordListViewController : UIViewController {
@private
    /** Table of words */
    IBOutlet UITableView *_tableView;
    
    /** Word entry field. */
    IBOutlet UITextField *_wordField;
    
    /** Word list identifier. */
    WNWordListIdentifier *_listIdentifier;

    /** Words in list. */
    NSArray *_wordStrings;
    
    /** Wordnik client. */
    WNClient *_client;
}

- (id) initWithWordnikClient: (WNClient *) client listIdentifier: (WNWordListIdentifier *) identifier;

- (IBAction) didPressDelete: (id) sender;
- (IBAction) didPressAdd: (id) sender;

@end
