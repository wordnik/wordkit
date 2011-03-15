//
//  WNDemoRandomWordsViewController.m
//  Wordnik
//
//  Created by Tony Tam on 2/26/11.
//  Copyright 2011 Wordnik. All rights reserved.
//

#import "WNDemoRandomWordsViewController.h"
#import <Wordnik/WNAdditions.h>

@interface WNDemoRandomWordsViewController () <UITableViewDelegate, UITableViewDataSource>
@end


@implementation WNDemoRandomWordsViewController

/**
 * Initialize a new demo catalog view controller.
 */
- (id) initWithWordnikClient: (WNClient *) client {
    if ((self = [super initWithNibName: nil bundle: nil]) == nil)
        return nil;
    
    self.navigationItem.title = @"Random Words";
    _client = [client retain];
    
    return self;
}

/**
 * @internal
 * Discard any references to retained subviews. This is called from both -dealloc and -viewDidUnload, and ensures
 * that references to subviews are not held after the primary view is discarded.
 */
- (void) discardSubviews {
    WNNilRelease(_tableView);
} 

- (void) dealloc {
    [self discardSubviews];    
    [_client release];
    [_randomWords release];
    
    [super dealloc];
}


// from UIViewController
- (void) viewDidAppear: (BOOL) animated {
    [super viewDidAppear: animated];
	WNRandomWordRequest *req = [WNRandomWordRequest requestWordsWithParameters:10 
														   includePartOfSpeech:nil
														   excludePartOfSpeech:nil
																minCorpusCount:0
																maxCorpusCount:0
															minDictionaryCount:0
															maxDictionaryCount:0
																	 minLength:0
																	 maxLength:0];
	
	[_client randomWordsWithParameters: req completionBlock: ^(NSArray *randomWords, NSError *error) {
        if (error != nil) {
            NSLog(@"Fetching word lists failed: %@", error);
            return;
        }
		
        [_randomWords release];
        _randomWords = [randomWords retain];
        
        [_tableView reloadData];
    }];
}

// from UIViewController
- (void) viewDidLoad {
    [super viewDidLoad];
	
    _tableView.dataSource = self;
    _tableView.delegate = self;
}

// from UIViewController
- (void) viewDidUnload {
    [super viewDidUnload];
    
    /* The primary view has been unloaded, so discard any subview references */
    [self discardSubviews];
}

// from UIViewController
- (BOOL) shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation) interfaceOrientation {
    return YES;
}

// from UITableViewDataSource
- (UITableViewCell *) tableView: (UITableView *) tableView cellForRowAtIndexPath: (NSIndexPath *) indexPath {
    NSString *identifier = @"ListCell";
    
    /* Dequeue (or create) a cell */
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: identifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle: UITableViewCellStyleDefault reuseIdentifier: identifier] autorelease];
    }
    
    /* Configure the cell */
    NSString *info = [_randomWords objectAtIndex: indexPath.row];
    cell.textLabel.text = info;
    
    return cell;
}

// from UITableViewDataSource
- (NSInteger) tableView: (UITableView *) tableView numberOfRowsInSection: (NSInteger) section {
    return [_randomWords count];
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}


@end
