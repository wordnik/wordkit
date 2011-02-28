/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

@interface WNClientAPIUsageStatus : NSObject {
@private
    /** Total number of permitted requests within this reset period. */
    NSInteger _totalPermittedRequestCount;

    /** Remaining number of requests within this reset period. */
    NSInteger _remainingPermittedRequestCount;

    /** Date after which this reset period will expire. */
    NSDate *_expirationDate;

    /** Date after which this reset period will be reset. */
    NSDate *_resetDate;
}

+ (id) usageStatusWithTotalPermittedRequestCount: (NSInteger) totalPermittedRequestCount
                  remainingPermittedRequestCount: (NSInteger) remainingPermittedRequestCount
                                  expirationDate: (NSDate *) expirationDate
                                       resetDate: (NSDate *) resetDate;

- (id) initWithTotalPermittedRequestCount: (NSInteger) totalPermittedRequestCount
           remainingPermittedRequestCount: (NSInteger) remainingPermittedRequestCount
                           expirationDate: (NSDate *) expirationDate
                                resetDate: (NSDate *) resetDate;

/** Total number of permitted requests within this reset period. */
@property(nonatomic, readonly) NSInteger totalPermittedRequestCount;

/** Remaining number of requests within this reset period. */
@property(nonatomic, readonly) NSInteger remainingPermittedRequestCount;

/** Date after which this reset period will expire, or nil for no expiration. */
@property(nonatomic, readonly) NSDate *expirationDate;

/** Date after which this reset period will be reset, or nil if no reset will occur. */
@property(nonatomic, readonly) NSDate *resetDate;

@end
