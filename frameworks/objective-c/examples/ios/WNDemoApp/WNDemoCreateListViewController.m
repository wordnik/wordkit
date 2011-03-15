/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import "WNDemoCreateListViewController.h"
#import <Wordnik/WNAdditions.h>

/**
 * Implements a list creation UI;
 */
@implementation WNDemoCreateListViewController

/**
 * Initialize a new demo catalog view controller.
 */
- (id) initWithWordnikClient: (WNClient *) client {
    if ((self = [super initWithNibName: nil bundle: nil]) == nil)
        return nil;
    
    self.navigationItem.title = @"Create List";
    _client = [client retain];
    
    return self;
}

/**
 * @internal
 * Discard any references to retained subviews. This is called from both -dealloc and -viewDidUnload, and ensures
 * that references to subviews are not held after the primary view is discarded.
 */
- (void) discardSubviews {    
    WNNilRelease(_nameField);
    WNNilRelease(_descriptionField);
} 

- (void) dealloc {
    [self discardSubviews];    
    [_client release];
    
    [super dealloc];
}

// from UIViewController
- (void) viewDidLoad {
    [super viewDidLoad];    
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

- (void) reportError: (NSError *) error {
    UIAlertView *alert = [[[UIAlertView alloc] initWithTitle: @"Creation Failure" 
                                                     message: [error localizedFailureReason]
                                                    delegate: nil 
                                           cancelButtonTitle: @"OK" 
                                           otherButtonTitles: nil] autorelease];
    [alert show];
    return;
}

- (IBAction) didPressCreateButton: (id) sender {
    WNWordListCreateRequest *req = [WNWordListCreateRequest requestWithListName: _nameField.text
                                                                    description: _descriptionField.text
                                                                     accessType: WNWordListAccessTypePrivate];
    [_client createWordListWithRequest: req completionBlock: ^(WNWordListCreateResponse *response, NSError *error) {
        if (error != nil) {
            [self reportError: error];
            return;
        }
        
        UIAlertView *alert = [[[UIAlertView alloc] initWithTitle: @"List created" 
                                                         message: nil
                                                        delegate: nil 
                                               cancelButtonTitle: @"OK" 
                                               otherButtonTitles: nil] autorelease];
        [alert show];
    }];
}

@end
