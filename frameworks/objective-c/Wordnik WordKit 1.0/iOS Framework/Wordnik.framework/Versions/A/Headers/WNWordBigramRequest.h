/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNConstants.h>
#import <Wordnik/WNBigram.h>

#import <Wordnik/WNWordElementRequest.h>

@interface WNWordBigramRequest : NSObject <WNWordElementRequest> {
@private    
    /** The maximum number of bigrams to return, or WNUnlimitedResultLength for no limit. */
    NSInteger _maxResultCount;
}

+ (id) request;
+ (id) requestWithMaxResultCount: (NSInteger) maxResultCount;

- (id) init;
- (id) initWithMaxResultCount: (NSInteger) maxResultCount;

/** The maximum number of bigrams to return, or WNUnlimitedResultLength for no limit. */
@property(nonatomic, readonly) NSInteger maxResultCount;

@end
