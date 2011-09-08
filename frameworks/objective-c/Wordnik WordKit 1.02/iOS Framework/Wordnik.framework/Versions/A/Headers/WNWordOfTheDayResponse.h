/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

@interface WNWordOfTheDayResponse : NSObject {
@private
    /** The word string. */
    NSString *_word;
    
    /** The date the entry was published. */
    NSDate *_publishDate;

    /** An ordered array of definition strings, formatted for display. */
    NSArray *_definitions;

    /** An ordered array of usage examples, formatted for display. */
    NSArray *_usageExamples;

    /** An ordered array of notes, formatted for display. */
    NSArray *_notes;
}

+ (id) responseWithWord: (NSString *) word
			publishDate: (NSDate *) publishDate
			definitions: (NSArray *) definitions
		  usageExamples: (NSArray *) usageExamples
				  notes: (NSArray *) notes;

- (id) initWithWord: (NSString *) word
		publishDate: (NSDate *) publishDate
        definitions: (NSArray *) definitions
      usageExamples: (NSArray *) usageExamples
			  notes: (NSArray *) notes;

/** The word string. */
@property(nonatomic, readonly) NSString *word;

/** The date the entry was published. */
@property(nonatomic, readonly) NSDate *publishDate;

/** An ordered array of definition objects, formatted for display. */
@property(nonatomic, readonly) NSArray *definitions;

/** An ordered array of usage examples, formatted for display. */
@property(nonatomic, readonly) NSArray *usageExamples;

/** An ordered array of notes, formatted for display. */
@property(nonatomic, readonly) NSArray *notes;

@end
