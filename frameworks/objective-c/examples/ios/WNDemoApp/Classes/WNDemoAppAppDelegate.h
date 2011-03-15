//
//  WNDemoAppAppDelegate.h
//  WNDemoApp
//
//  Created by Tony Tam on 3/15/11.
//  Copyright 2011 wordnik. All rights reserved.
//

#import <UIKit/UIKit.h>

@class WNDemoAppViewController;

@interface WNDemoAppAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    WNDemoAppViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet WNDemoAppViewController *viewController;

@end

