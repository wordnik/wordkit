/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNSpellingSuggestion : NSObject <NSCopying> {
@private
    /** The suggested word. */
    NSString *_word;
}

+ (id) suggestionWithWord : (NSString *) word;
- (id) initWithWord : (NSString *) word;

/** A suggested alternative word. */
@property(nonatomic, readonly) NSString *word;

@end
