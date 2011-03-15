/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Wordnik/Wordnik.h>

#import "WNDemoAppDelegate.h"
#import "WNDemoCatalogViewController.h"

/* The API key to use for testing. */
#define API_KEY @"YOUR_API_KEY"

/**
 * Wordnik API Demo App
 */
@implementation WNDemoAppDelegate

// from UIApplicationDelegate protocol
- (void) applicationDidFinishLaunching: (UIApplication *) application {
    /* Set up our network client. */
    WNClientConfig *config = [WNClientConfig configWithAPIKey: API_KEY ];
    WNClient *client = [[[WNClient alloc] initWithClientConfig: config] autorelease];
    
    /* Fetch API usage information (for testing purposes). */
    [client requestAPIUsageStatusWithCompletionBlock: ^(WNClientAPIUsageStatus *status, NSError *error) {
        if (error != nil) {
            NSLog(@"Usage request failed: %@", error);
            return;
        }

        NSMutableString *output = [NSMutableString string];
        [output appendFormat: @"Expires at: %@\n", status.expirationDate];
        [output appendFormat: @"Reset at: %@\n", status.resetDate];
        [output appendFormat: @"Total calls permitted: %ld\n", (long) status.totalPermittedRequestCount];
        [output appendFormat: @"Total calls remaining: %ld\n", (long) status.remainingPermittedRequestCount];

        NSLog(@"API Usage:\n%@", output);
    }];

    /* Set up the root VC */
    WNDemoCatalogViewController *catalogVC = [[[WNDemoCatalogViewController alloc] initWithWordnikClient: client] autorelease];
    [_navController setViewControllers: [NSArray arrayWithObject: catalogVC] animated: NO];

    /* Display */
    [_window addSubview: _navController.view];    
    [_window makeKeyAndVisible];
}

- (void) dealloc {
    [_navController release];
    [_window release];
    
    [super dealloc];
}


@end
