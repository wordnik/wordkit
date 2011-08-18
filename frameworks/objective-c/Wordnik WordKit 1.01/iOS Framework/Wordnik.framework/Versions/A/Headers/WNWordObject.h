/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNDefinitionList.h>
#import <Wordnik/WNExample.h>
#import <Wordnik/WNRelatedWordList.h>
#import <Wordnik/WNUsageFrequencyTimeline.h>
#import <Wordnik/WNAudioFileMetadata.h>
#import <Wordnik/WNBigram.h>

@interface WNWordObject : NSObject {
@private
    /** The word's string value. */
    NSString *_word;

    /** The word's definition list. */
    NSArray *_definitions;

    /** Ordered array of bigram phrases. */
    NSArray *_bigrams;
    
    /** Related word list. */
    WNRelatedWordList *_relatedWords;

    /** Ordered array of example sentences. */
    NSArray *_examples;

    /** Word usage frequency timeline. */
    WNUsageFrequencyTimeline *_frequencyTimeline;
    
    /** Text pronunciations. */
    NSArray *_pronunciations;

    /** Audio file metadata factor. */
    NSArray *_audioFileMetadata;
}

+ (id) wordObjectWithWord: (NSString *) word;
+ (id) wordObjectWithWord: (NSString *) word 
			  definitions: (NSArray *) definitions
				 examples: (NSArray *) examples
			 relatedWords: (WNRelatedWordList *) relatedWords
   usageFrequencyTimeline: (WNUsageFrequencyTimeline *) frequencyTimeline
	   textPronunciations: (NSArray *) textPronunciations
				  bigrams: (NSArray *) bigrams
		audioFileMetadata:(NSArray*)audioFileMetadata;

- (id) initWithWord: (NSString *) word;
- (id) initWithWord: (NSString *) word 
		definitions: (NSArray *) definitions
		   examples: (NSArray *) examples
	   relatedWords: (WNRelatedWordList *) relatedWords
usageFrequencyTimeline: (WNUsageFrequencyTimeline *) frequencyTimeline
 textPronunciations: (NSArray *) textPronunciations
			bigrams: (NSArray *) bigrams
  audioFileMetadata:(NSArray*)audioFileMetadata;

- (WNWordObject *) wordObjectByAppendingElementsFromWord: (WNWordObject *) otherWord;

/** The word's string value. */
@property(nonatomic, readonly) NSString *word;

/** The word's definition lists, if available. If not available, this property will be nil. */
@property(nonatomic, readonly) NSArray *definitions;

/** The word's associated bigram phrases as an ordered array of WNBigram instances, if available. If not available, this
 * property will be nil. */
@property(nonatomic, readonly) NSArray *bigrams;

/** Example sentences as an ordered array of WNExample instances, if available. If not available, this property
 * will be nil. */
@property(nonatomic, readonly) NSArray *examples;

/** Related word list, if available. If not available, this property will be nil. */
@property(nonatomic, readonly) WNRelatedWordList *relatedWords;

/** Word usage frequency timeline, if available. If not available, this property will be nil. */
@property(nonatomic, readonly) WNUsageFrequencyTimeline *usageFrequencyTimeline;

/** Text pronunciations as an array of WNTextPronunciation instances, if available. If not available, this property will be nil. */
@property(nonatomic, readonly) NSArray *textPronunciations;

/** Audio file metadata as an array of WNAudioFileMetadata objects.  If not available, this property will be nil */
@property(nonatomic, readonly) NSArray *audioFileMetadata;

@end
