/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import <UIKit/UIKit.h>

#import <Wordnik/WNClient.h>

@interface WNDemoDeleteWordListViewController : UIViewController {
@private
    /** Table of available demo modules */
    IBOutlet UITableView *_tableView;
    
    /** Word list info. */
    NSArray *_wordListInfo;
    
    /** Wordnik client. */
    WNClient *_client;
}

- (id) initWithWordnikClient: (WNClient *) client;

@end
