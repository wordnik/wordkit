/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import <Foundation/Foundation.h>
#import <Wordnik/WNUsageFrequency.h>

@interface WNUsageFrequencyTimeline : NSObject {
@private
    /** Word frequency, ordered by year (oldest first) */
    NSArray *_wordFrequencies;

    /** Total word usage count for all years. */
    NSInteger _totalUsageCount;

    /** Usage count for unknown years. */
    NSInteger _unknownYearUsageCount;    
}

+ (id) frequencyTimelineWithWordFrequenciesFromArray: (NSArray *) wordFrequencies
                               unknownYearUsageCount: (NSInteger) unknownYearUsageCount;
- (id) initWithWordFrequenciesFromArray: (NSArray *) wordFrequencies
                  unknownYearUsageCount: (NSInteger) unknownYearUsageCount;

/** Word frequency, ordered by year (oldest first) */
@property(nonatomic, readonly) NSArray *wordFrequencies;

/** Total word usage count for all years, not including unknown years. */
@property(nonatomic, readonly) NSInteger totalUsageCount;

/** Usage count for unknown years. */
@property(nonatomic, readonly) NSInteger unknownYearUsageCount;

@end
