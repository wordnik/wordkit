/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import "WNDemoWordOfTheDayViewController.h"
#import <Wordnik/WNAdditions.h>

/**
 * A word of the day view controller.
 */
@implementation WNDemoWordOfTheDayViewController


/**
 * Initialize a new demo catalog view controller.
 */
- (id) initWithWordnikClient: (WNClient *) client {
    if ((self = [super initWithNibName: nil bundle: nil]) == nil)
        return nil;
    
    self.navigationItem.title = @"Word of the Day";
    
    _client = [client retain];
    
    return self;
}

/**
 * @internal
 * Discard any references to retained subviews. This is called from both -dealloc and -viewDidUnload, and ensures
 * that references to subviews are not held after the primary view is discarded.
 */
- (void) discardSubviews {    
    WNNilRelease(_resultTextView);
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

- (void) viewDidAppear: (BOOL) animated {
    [_client requestWordOfTheDayWithCompletionBlock: ^(WNWordOfTheDayResponse *response, NSError *error) {
        if (error != nil) {
            _resultTextView.text = [NSString stringWithFormat: @"An error occured: %@", error];
            return;
        }

        NSMutableString *text = [NSMutableString string];

        [text appendFormat: @"Word: %@\n", response.word];
        
        if ([response.definitions count] > 0) {
            [text appendString: @"\n\n• Definitions: \n"];

			for(WNDefinition * def in response.definitions){
				[text appendFormat: @"%@%@", def.text, @"\n"];
			}
        }

        if ([response.usageExamples count] > 0) {
            [text appendString: @"\n\n• Examples: \n"];

			for(WNExample * def in response.usageExamples){
				[text appendFormat: @"%@%@", def.text, @"\n"];
			}
        }

        if ([response.notes count] > 0) {
            [text appendString: @"\n\n• Notes: \n"];
            [text appendString: [response.notes componentsJoinedByString: @"\n"]];
        }
        
        _resultTextView.text = text;
    }];
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

@end
