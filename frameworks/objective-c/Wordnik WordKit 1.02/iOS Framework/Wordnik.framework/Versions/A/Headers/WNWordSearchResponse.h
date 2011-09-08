/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

@interface WNWordSearchResponse : NSObject {
@private
    /** The total result count. */
    NSInteger _totalResults;

    /** The returned word strings. */
    NSArray *_words;
}

+ (id) responseWithWords: (NSArray *) words 
			totalResults: (NSInteger) totalResults;

- (id) initWithWords: (NSArray *) words
		totalResults: (NSInteger) totalResults;

/** Matching word strings. */
@property(nonatomic, readonly) NSArray *words;

/**
 * The total number of autocomplete matches. Fewer matches may be available in this response.
 */
@property(nonatomic, readonly) NSInteger totalResults;

@end

