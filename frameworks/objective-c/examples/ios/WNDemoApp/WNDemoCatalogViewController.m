/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import "WNDemoCatalogViewController.h"

#import "WNDemoAuthViewController.h"
#import "WNDemoWordInfoViewController.h"
#import "WNDemoAutocompleteViewController.h"
#import "WNDemoWordOfTheDayViewController.h"
#import "WNDemoRandomWordsViewController.h"
#import "WNDemoCreateListViewController.h"
#import "WNDemoAllWordListsViewController.h"
#import "WNDemoDeleteWordListViewController.h"

#import <WordnikUI/WNDefinitionViewController.h>
#import "WNAdditions.h"

typedef UIViewController *(^ActionBlock)();

@interface WNDemoCatalogViewController () <UITableViewDelegate, UITableViewDataSource, WNClientObserver>
@end

/**
 * Displays a list-based catalog of available demo modules.
 */
@implementation WNDemoCatalogViewController

/**
 * Initialize a new demo catalog view controller.
 */
- (id) initWithWordnikClient: (WNClient *) client {
    if ((self = [super initWithNibName: nil bundle: nil]) == nil)
        return nil;
    
    self.navigationItem.title = @"Wordnik";
    _client = [client retain];
    [_client addObserver: self];
    
    _dataSource = [[WNCompositeWordDataSource alloc] init];
    
    WNWordNetworkDataSource *networkDataSource = [[[WNWordNetworkDataSource alloc] initWithWordnikClient: _client] autorelease];

    [_dataSource addNetworkDataSource: networkDataSource];
    
    NSString *path=[[NSBundle mainBundle] pathForResource:@"OfflineDatabase" ofType: @"wordnik"];
    
    WNLocalWordDataSource *localDataSource=[[[WNLocalWordDataSource alloc] initWithPath:path] autorelease];
    
    if(localDataSource!=nil)
        [_dataSource addLocalDataSource: localDataSource];
    
    return self;
}

/**
 * @internal
 * Discard any references to retained subviews. This is called from both -dealloc and -viewDidUnload, and ensures
 * that references to subviews are not held after the primary view is discarded.
 */
- (void) discardSubviews {
    WNNilRelease(_tableView);
    WNNilRelease(_titles);
    WNNilRelease(_actions);
    WNNilRelease(_sectionTitles);
} 

- (void) dealloc {
    [self discardSubviews];    
    [_client release];
    [_client removeObserver: self];

    [_dataSource release];

    [super dealloc];
}

- (void) reloadCatalog {
    /* Reset current values */
    [_sectionTitles release];
    [_actions release];
    [_titles release];

    _sectionTitles = [NSMutableArray new];
    _actions = [NSMutableArray new];
    _titles = [NSMutableArray new];

    /* A little DSL for defining the table view's contents */
    typedef void (^ModuleDef)(NSString *, BOOL, ActionBlock);
    ModuleDef Module = nil;
    ModuleDef (^Section)(NSString *) = ^ModuleDef (NSString *title) {
        NSMutableArray *titles = [NSMutableArray array];
        NSMutableArray *actions = [NSMutableArray array];

        [_sectionTitles addObject: title];
        [_titles addObject: titles];
        [_actions addObject: actions];

        return [[^(NSString *title, BOOL authRequired, ActionBlock block) {
            [titles addObject: title];
            
            if (authRequired && _client.authenticationState != WNClientAuthStateLoggedIn) {
                [actions addObject: [NSNull null]];
            } else {
                [actions addObject: [[block copy] autorelease]];
            }
        } copy] autorelease];
    };

    /* UI SDK */
    Module = Section(@"UI SDK");
    Module(@"Definition View", NO, ^UIViewController *{
        return [[[WNDefinitionViewController alloc] initWithWord: @"jangle" dataSource: _dataSource] autorelease];
    });    

    /* Data SDK */
    Module = Section(@"Data SDK");
    Module(@"Authentication", NO, ^UIViewController *{
        return [[[WNDemoAuthViewController alloc] initWithWordnikClient: _client] autorelease];
    });
    
    Module(@"Word Lookup", NO, ^UIViewController *{
        return [[[WNDemoWordInfoViewController alloc] initWithWordnikClient: _client] autorelease];
    });
    
    Module(@"Word Search", NO, ^UIViewController *{
        return [[[WNDemoAutocompleteViewController alloc] initWithWordnikClient: _client] autorelease];
    });
    
    Module(@"Word of the Day", NO, ^UIViewController *{
        return [[[WNDemoWordOfTheDayViewController alloc] initWithWordnikClient: _client] autorelease];
    });
	
    Module(@"Random Words", NO, ^UIViewController *{
        return [[[WNDemoRandomWordsViewController alloc] initWithWordnikClient: _client] autorelease];
    });

    /* Data SDK - List Management */
    Module = Section(@"Data SDK (Lists)");
    Module(@"Create Word List", YES, ^UIViewController *{
        return [[[WNDemoCreateListViewController alloc] initWithWordnikClient: _client] autorelease];
    });
    
    Module(@"All Word Lists", YES, ^UIViewController *{
        return [[[WNDemoAllWordListsViewController alloc] initWithWordnikClient: _client] autorelease];
    });
    
    Module(@"Delete Word List", YES, ^UIViewController *{
        return [[[WNDemoDeleteWordListViewController alloc] initWithWordnikClient: _client] autorelease];
    });

    [_tableView reloadData];
}

// from UIViewController
- (void) viewDidLoad {
    [super viewDidLoad];

    _tableView.dataSource = self;
    _tableView.delegate = self;
    [self reloadCatalog];
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

    ActionBlock block = [[_actions objectAtIndex: indexPath.section] objectAtIndex: indexPath.row];
    if ([block isEqual: [NSNull null]]) {
        UIAlertView *alert = [[[UIAlertView alloc] initWithTitle: @"Authentication Required"
                                                         message: @"You must log in before using this method"
                                                        delegate: nil
                                               cancelButtonTitle: @"OK"
                                               otherButtonTitles: nil] autorelease];
        [alert show];
        return;
    }

    [self.navigationController pushViewController: block() animated: YES];
}

// from UITableViewDataSource
- (NSString *) tableView: (UITableView *) tableView titleForHeaderInSection: (NSInteger) section {
    return [_sectionTitles objectAtIndex: section];
}

// from UITableViewDataSource
- (UITableViewCell *) tableView: (UITableView *) tableView cellForRowAtIndexPath: (NSIndexPath *) indexPath {
    NSString *identifier = @"DemoModuleCell";

    /* Dequeue (or create) a cell */
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: identifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle: UITableViewCellStyleDefault reuseIdentifier: identifier] autorelease];
    }

    /* Configure the cell */
    cell.textLabel.text = [[_titles objectAtIndex: indexPath.section] objectAtIndex: indexPath.row];

    /* Check if the cell should be disabled */
    id action = [[_actions objectAtIndex: indexPath.section] objectAtIndex: indexPath.row];
    if ([action isEqual: [NSNull null]]) {
        cell.accessoryType = UITableViewCellAccessoryNone;
        cell.textLabel.textColor = [UIColor grayColor];
    } else {
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.textLabel.textColor = [UIColor blackColor];
    }

    return cell;
}

// from UITableViewDataSource
- (NSInteger) numberOfSectionsInTableView: (UITableView *) tableView {
    return [_sectionTitles count];
}

// from UITableViewDataSource
- (NSInteger) tableView: (UITableView *) tableView numberOfRowsInSection: (NSInteger) section {
    return [[_titles objectAtIndex: section] count];
}


// from WNClientObserver protocol
- (void) client: (WNClient *) client didLoginWithRequestTicket: (WNRequestTicket *) requestTicket {
    /* Reload the table so that auth-required items will be visible */
    if ([self isViewLoaded])
        [self reloadCatalog];
}

// from WNClientObserver protocol
- (void) clientDidLogout: (WNClient *) client {
    /* Reload the table so that auth-required items will be hidden */
    if ([self isViewLoaded])
        [self reloadCatalog];
}

@end
