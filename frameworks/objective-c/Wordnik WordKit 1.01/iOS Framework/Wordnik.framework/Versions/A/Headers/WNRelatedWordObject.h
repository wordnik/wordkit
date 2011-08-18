/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import <Foundation/Foundation.h>
#import <Wordnik/WNRelatedWordType.h>

@interface WNRelatedWordObject : NSObject {
@private
    /** The word's string value. */
    NSString *_word;

    /** The word's relation type. */
    WNRelatedWordType *_relationType;
}

+ (id) relatedWordObjectWithWord: (NSString *) word relationType: (WNRelatedWordType *) relationType;
- (id) initWithWord: (NSString *) word relationType: (WNRelatedWordType *) relationType;

/** The word's string value. */
@property(nonatomic, readonly) NSString *word;

/** The word's relation to the original word. */
@property(nonatomic, readonly) WNRelatedWordType *relationType;

@end
