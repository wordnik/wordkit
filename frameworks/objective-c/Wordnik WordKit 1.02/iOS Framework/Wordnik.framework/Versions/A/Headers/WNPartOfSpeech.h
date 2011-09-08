/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNPartOfSpeech : NSObject {
@private
    /** The canonical wordnik name for this part of speech. */
    NSString *_name;
    
    /** A human readable name for this part of speech. */
    NSString *_localizedName;
}

+ (id) notSpecified; // no part of speech specified

+ (id) noun;
+ (id) verb;
+ (id) adjective;
+ (id) adverb;
+ (id) idiom;
+ (id) article;
+ (id) abbreviation;
+ (id) preposition;
+ (id) prefix;
+ (id) interjection;
+ (id) suffix;
+ (id) conjunction;
+ (id) adjectiveAndAdverb;
+ (id) nounAndAdjective;
+ (id) nounAndVerbTransitive;
+ (id) nounAndVerb;
+ (id) pastParticiple;
+ (id) imperative;
+ (id) nounPlural;
+ (id) properNounPlural;
+ (id) verbIntransitive;
+ (id) properNoun;
+ (id) adjectiveAndNoun;
+ (id) imperativeAndPastParticiple;
+ (id) pronoun;
+ (id) verbTransitive;
+ (id) nounAndVerbIntransitive;
+ (id) adverbAndPreposition;
+ (id) properNounPosessive;
+ (id) nounPosessive;

+ (id) partOfSpeechWithName: (NSString *) name;
- (id) initWithPartOfSpeechName: (NSString *) name;

/** Canonical Wordnik part-of-speech name. */
@property(nonatomic, readonly) NSString *name;

/** A human readable name for this part of speech. */
@property(nonatomic, readonly) NSString *localizedName;

@end
