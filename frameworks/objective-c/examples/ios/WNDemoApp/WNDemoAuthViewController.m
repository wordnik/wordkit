/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import "WNDemoAuthViewController.h"
#import <Wordnik/WNAdditions.h>

@interface WNDemoAuthViewController () <WNClientObserver>
- (void) configureViewForAuthState;
@end


/**
 * Implements a basic authentication UI.
 */
@implementation WNDemoAuthViewController

/**
 * Initialize a new demo catalog view controller.
 */
- (id) initWithWordnikClient: (WNClient *) client {
    if ((self = [super initWithNibName: nil bundle: nil]) == nil)
        return nil;
    
    self.navigationItem.title = @"Authentication";
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
    [_client removeObserver: self];

    WNNilRelease(_usernameField);
    WNNilRelease(_passwordField);
    WNNilRelease(_submitButton);
} 

- (void) dealloc {
    [self discardSubviews];    
    [_client release];
    
    [super dealloc];
}

// from UIViewController
- (void) viewDidLoad {
    [super viewDidLoad];
    
    [self configureViewForAuthState];
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

// Reconfigure the view for the current authentication state.
- (void) configureViewForAuthState {

    /* Configure the UI */
    WNClientAuthState state = _client.authenticationState;
    void (^Config)(NSString *, NSString *) = ^(NSString *authLabel, NSString *buttonLabel) {
        if (state != WNClientAuthStateLoggedOut) {
            _usernameField.enabled = NO;
            _passwordField.enabled = NO;
        }

        [_submitButton setTitle: buttonLabel forState: UIControlStateNormal];
        _authState.text = authLabel;
    };

    switch (state) {
        case WNClientAuthStateLoggedOut:
            Config(@"Logged out", @"Log in");
            break;

        case WNClientAuthStateLoggingIn:
            Config(@"Logging in", @"Cancel");
            break;

        case WNClientAuthStateLoggedIn:
            Config(@"Logged In", @"Log out");
            break;
    }
}

- (IBAction) didPressLoginButton: (id) sender {
    /* If logged in, log out */
    if (_client.authenticationState == WNClientAuthStateLoggedIn) {
        [_client logout];
        return;
    }

    /* Otherwise, log in */
    WNClientCredentials *creds = [WNClientCredentials credentialsWithUsername: _usernameField.text password: _passwordField.text];
    [_client loginWithCredentials: creds];
}

// from WNClientObserver protocol
- (void) client: (WNClient *) client didLoginWithRequestTicket: (WNRequestTicket *) requestTicket {
    [self configureViewForAuthState];
}

// from WNClientObserver protocol
- (void) clientDidLogout: (WNClient *) client {
    [self configureViewForAuthState];
}

// from WNClientObserver protocol
- (void) client: (WNClient *) client loginDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket {
    UIAlertView *alert = [[[UIAlertView alloc] initWithTitle: @"Login Failure" 
                                                     message: [error localizedFailureReason]
                                                    delegate: nil 
                                           cancelButtonTitle: @"OK" 
                                           otherButtonTitles: nil] autorelease];
    [alert show];

    [self configureViewForAuthState];
}

@end
