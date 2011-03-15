/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import "WNDemoAutocompleteViewController.h"
#import <Wordnik/WNAdditions.h>

/**
 * Implements an autocompletion demo UI.
 */
@implementation WNDemoAutocompleteViewController

/**
 * Initialize a new demo catalog view controller.
 */
- (id) initWithWordnikClient: (WNClient *) client {
    if ((self = [super initWithNibName: nil bundle: nil]) == nil)
        return nil;
    
    self.navigationItem.title = @"Word Suggest";

    _client = [client retain];
    [_client addObserver: self];
    
    return self;
}

/**
 * @internal
 * Discard any references to retained subviews. This is called from both -dealloc and -viewDidUnload, and ensures
 * that references to subviews are not held after the primary view is discarded.
 */
- (void) discardSubviews {
    _wordField.delegate = nil;

    WNNilRelease(_wordField);
    WNNilRelease(_resultTextView);
    WNNilRelease(_runningIndicator);
} 

- (void) dealloc {
    [self discardSubviews];

    [_requestTicket cancel];
    [_requestTicket release];

    [_client removeObserver: self];
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

// from WNClientObserver protocol
- (void) client: (WNClient *) client autocompleteWordRequestDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket {
    /* Drop saved reference to the request ticket */
    WNNilRelease(_requestTicket);
    
    /* Report error */
    UIAlertView *alert = [[[UIAlertView alloc] initWithTitle: @"Lookup Failure" 
                                                     message: [error localizedFailureReason]
                                                    delegate: nil 
                                           cancelButtonTitle: @"OK" 
                                           otherButtonTitles: nil] autorelease];
    [alert show];
}

// from WNClientObserver protocol
- (void) client: (WNClient *) client didReceiveAutocompleteWordResponse: (WNWordSearchResponse *) response requestTicket: (WNRequestTicket *) requestTicket {
    /* Verify that this corresponds to our request */
    if (![_requestTicket isEqual: requestTicket])
        return;

    /* Drop saved reference to the request ticket */
    WNNilRelease(_requestTicket);

    /* Display results */
    _resultTextView.text = [response.words componentsJoinedByString: @"\n"];
}


// from UITextFieldDelegate protocol
- (BOOL) textField: (UITextField *) textField shouldChangeCharactersInRange: (NSRange) range replacementString: (NSString *) string {
    /* Determine the new field value */
    NSString *fragment = [textField.text stringByReplacingCharactersInRange: range withString: string];

    /* Cancel any running request */
    [_requestTicket cancel];
    WNNilRelease(_requestTicket);

    /* If word was deleted, simply reset the current result text. */
    if ([fragment length] == 0) {
        _resultTextView.text = nil;
        return YES;
    }

    /* Submit an autocompletion request */
	WNWordSearchRequest * req = [WNWordSearchRequest requestWithWordFragment:fragment
																		skip:0 
																	   limit:10 
														 includePartOfSpeech:nil
														 excludePartOfSpeech:nil
															  minCorpusCount:0
															  maxCorpusCount:0
														  minDictionaryCount:1
														  maxDictionaryCount:0
																   minLength:0
																   maxLength:0
															 resultCollation:WNAutocompleteWordCollationFrequencyDescending];

    _requestTicket = [[_client autocompletedWordsWithRequest: req] retain];

    return YES;
}

@end
