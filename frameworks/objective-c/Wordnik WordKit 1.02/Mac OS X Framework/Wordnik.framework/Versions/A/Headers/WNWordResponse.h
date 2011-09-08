/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import <Foundation/Foundation.h>

#import <Wordnik/WNWordObject.h>
#import <Wordnik/WNSpellingSuggestion.h>

@interface WNWordResponse : NSObject {
@private
    /** The returned word record. */
    WNWordObject *_wordObject;
    
    /** Alternative spelling suggestions as an ordered array of WNSpellingSuggestion instances. Will be empty
     * if alternative spelling suggestions were not either not requested or not available. */
    NSArray *_spellingSuggestions;
}

+ (id) responseWithWord: (WNWordObject *) word spellingSuggestions: (NSArray *) spellingSuggestions;
- (id) initWithWord: (WNWordObject *) word spellingSuggestions: (NSArray *) spellingSuggestions;

/** The returned word record. */
@property(nonatomic, readonly) WNWordObject *wordObject;

/** Alternative spelling suggestions as an ordered array of WNSpellingSuggestion instances. Will be empty
 * if alternative spelling suggestions were not requested. */
@property(nonatomic, readonly) NSArray *spellingSuggestions;

@end
