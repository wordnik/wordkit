//
//  WNDemoRandomWordsViewController.h
//  Wordnik
//
//  Created by Tony Tam on 2/26/11.
//  Copyright 2011 Wordnik. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Wordnik/WNClient.h>


@interface WNDemoRandomWordsViewController : UIViewController {
    /** Table of available word lists */
    IBOutlet UITableView *_tableView;
    
    /** Random Words info. */
    NSArray *_randomWords;
    
    /** Wordnik client. */
    WNClient *_client;
	
}

@end
