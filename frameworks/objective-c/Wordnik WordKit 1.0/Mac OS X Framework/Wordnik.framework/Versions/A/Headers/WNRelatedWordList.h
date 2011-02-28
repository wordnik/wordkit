/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNRelatedWordObject.h>

@interface WNRelatedWordList : NSObject {
@private
    /** Ordered array of related words. */
    NSArray *_relatedWords;

    /** Map of relation types to ordered array of related words (WNRelatedWordType -> NSArray<WNRelatedWordType>) */
    NSDictionary *_relationTypeMap;
}

+ (id) listWithRelatedWordArray: (NSArray *) relatedWords;
- (id) initWithRelatedWordArray: (NSArray *) relatedWords;

- (NSArray *) wordsForRelationType: (WNRelatedWordType *) relationType;

- (WNRelatedWordList *) listByAppendingWordsFromList: (WNRelatedWordList *) list;

/** Ordered array of related words. */
@property(nonatomic, readonly) NSArray *relatedWords;

/** Relation types for which related words are available. */
@property(nonatomic, readonly) NSArray *relationTypes;

@end
