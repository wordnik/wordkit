/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNUsageFrequency : NSObject {
@private
    /** The word usage count for this year. */
    NSInteger _usageCount;

    /** The year. */
    NSInteger _year;
}

+ (id) wordFrequencyWithYear: (NSInteger) year usageCount: (NSInteger) usageCount;
- (id) initWithYear: (NSInteger) year usageCount: (NSInteger) usageCount;

/** Word usage count for a given year. */
@property(nonatomic, readonly) NSInteger usageCount;

/** Year for this usage count. */
@property(nonatomic, readonly) NSInteger year;

@end
