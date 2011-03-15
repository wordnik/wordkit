/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import "WNDemoModifyWordListViewController.h"
#import <Wordnik/WNAdditions.h>

@interface WNDemoModifyWordListViewController () <UITableViewDelegate, UITableViewDataSource>
@end

/**
 * Displays the user's word lists.
 */
@implementation WNDemoModifyWordListViewController

/**
 * Initialize a new demo catalog view controller.
 */
- (id) initWithWordnikClient: (WNClient *) client listIdentifier: (WNWordListIdentifier *) identifier {
    if ((self = [super initWithNibName: nil bundle: nil]) == nil)
        return nil;
    
    self.navigationItem.title = @"Wordnik Lists";
    _client = [client retain];
    _listIdentifier = [identifier retain];
    
    return self;
}

/**
 * @internal
 * Discard any references to retained subviews. This is called from both -dealloc and -viewDidUnload, and ensures
 * that references to subviews are not held after the primary view is discarded.
 */
- (void) discardSubviews {
    WNNilRelease(_tableView);
    WNNilRelease(_wordField);
} 

- (void) dealloc {
    [self discardSubviews];    
    [_client release];
    [_listIdentifier release];
    [_wordStrings release];
    
    [super dealloc];
}

- (void) reloadData {
    [_client wordsFromListWithIdentifier: _listIdentifier completionBlock: ^(NSArray *wordStrings, NSError *error) {
        if (error != nil) {
            NSLog(@"Failed to fetch word strings: %@", error);
            return;
        }

        [_wordStrings release];
        _wordStrings = [wordStrings retain];

        [_tableView reloadData];
    }];
}

// from UIViewController
- (void) viewDidAppear: (BOOL) animated {
    [super viewDidAppear: animated];
    [self reloadData];
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
- (void) didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}


// from UIViewController
- (BOOL) shouldAutorotateToInterfaceOrientation: (UIInterfaceOrientation) interfaceOrientation {
    return YES;
}

// from UITableViewDelegate
- (void) tableView: (UITableView *) tableView didSelectRowAtIndexPath: (NSIndexPath *) indexPath {
    [tableView deselectRowAtIndexPath: indexPath animated: YES];

    _wordField.text = [_wordStrings objectAtIndex: indexPath.row];
}

- (IBAction) didPressDelete: (id) sender {
    [_wordField resignFirstResponder];
    [_client removeWord: _wordField.text fromListWithIdentifier: _listIdentifier completionBlock: ^(NSError *error) {
        if (error != nil) {
            NSLog(@"Failed to remove word string: %@", error);
            return;
        }

        [self reloadData];
    }];
}

- (IBAction) didPressAdd: (id) sender {
    [_wordField resignFirstResponder];
    [_client addWord: _wordField.text toListWithIdentifier: _listIdentifier completionBlock: ^(NSError *error) {
        if (error != nil) {
            NSLog(@"Failed to add word string: %@", error);
            return;
        }
        
        [self reloadData];
    }];
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
    cell.textLabel.text = [_wordStrings objectAtIndex: indexPath.row];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return cell;
}

// from UITableViewDataSource
- (NSInteger) tableView: (UITableView *) tableView numberOfRowsInSection: (NSInteger) section {
    return [_wordStrings count];
}

@end
