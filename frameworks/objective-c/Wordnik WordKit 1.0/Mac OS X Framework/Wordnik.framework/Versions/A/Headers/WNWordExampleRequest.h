/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNConstants.h>
#import <Wordnik/WNExample.h>

#import <Wordnik/WNWordElementRequest.h>

@interface WNWordExampleRequest : NSObject <WNWordElementRequest> {
@private    
}

+ (id) request;
- (id) init;

@end
