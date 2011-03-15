/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import <UIKit/UIKit.h>

#import <Wordnik/WNClient.h>
#import <Wordnik/WNCompositeWordDataSource.h>

@interface WNDemoCatalogViewController : UIViewController {
@private
    /** Table of available demo modules */
    IBOutlet UITableView *_tableView;
    
    /** Maps section index to section title. */
    NSMutableArray *_sectionTitles;

    /** Array of arrays. Maps section index to an array of cell titles. */
    NSMutableArray *_titles;

    /** Array of arrays. Maps section index to ActionBlock instances. */
    NSMutableArray *_actions;
    
    /** Wordnik client. */
    WNClient *_client;
    
    /** Network data source (wraps the client) */
    WNCompositeWordDataSource *_dataSource;

}

- (id) initWithWordnikClient: (WNClient *) client;

@end
