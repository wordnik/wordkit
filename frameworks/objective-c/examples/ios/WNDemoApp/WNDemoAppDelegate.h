/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <UIKit/UIKit.h>

@interface WNDemoAppDelegate : NSObject <UIApplicationDelegate> {
@private
    /** Main window. */
    IBOutlet UIWindow *_window;
    
    /** Navigation controller */
    IBOutlet UINavigationController *_navController;
}

@end
