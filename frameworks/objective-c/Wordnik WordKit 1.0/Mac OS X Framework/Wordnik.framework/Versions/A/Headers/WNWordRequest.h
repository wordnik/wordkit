/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNWordElementRequest.h>
#import <Wordnik/WNWordDefinitionRequest.h>
#import <Wordnik/WNWordExampleRequest.h>
#import <Wordnik/WNWordRelatedWordsRequest.h>
#import <Wordnik/WNWordUsageFrequencyRequest.h>
#import <Wordnik/WNWordTextPronunciationRequest.h>
#import <Wordnik/WNAudioFileMetadataRequest.h>
#import <Wordnik/WNWordBigramRequest.h>

@interface WNWordRequest : NSObject {
@private
    /** The requested word. */
    NSString *_word;

    /** Indicates whether the canonical form of the word should be automatically selected. */
    BOOL _requestCanonicalForm;
    
    /** Indicates whether alternative spelling suggestions should be requested for this word. */
    BOOL _requestSpellingSuggestions;

    /** The word entry elements requests. */
    NSArray *_elementRequests;
}

+ (id) requestWithWord: (NSString *) word elementRequests: (NSArray *) elementRequests;

+ (id) requestWithWord: (NSString *) word
        requestCanonicalForm: (BOOL) requestCanonicalForm
  requestSpellingSuggestions: (BOOL) requestSpellingSuggestions
             elementRequests: (NSArray *) elementRequests;

- (id) initWithWord: (NSString *) word elementRequests: (NSArray *) elementRequests;

- (id)  initWithWord: (NSString *) word 
      requestCanonicalForm: (BOOL) requestCanonicalForm
requestSpellingSuggestions: (BOOL) requestSpellingSuggestions
           elementRequests: (NSArray *) elementRequests;

/** The requested word. */
@property(nonatomic, readonly) NSString *word;

/** Indicates whether spelling suggestions should be requested for this word. */
@property(nonatomic, readonly) BOOL requestSpellingSuggestions;

/** Indicates whether the canonical form of the word should be automatically selected; eg, a query for 'Zebra' would return 'zebra'. */
@property(nonatomic, readonly) BOOL requestCanonicalForm;

/** The set of word entry elements to be fetched, as an ordered array of WNWordElementRequest instances. */
@property(nonatomic, readonly) NSArray *elementRequests;

@end

#ifdef WORDNIK_PRIVATE
#import <Wordnik/WNWordRequestPrivate.h>
#endif