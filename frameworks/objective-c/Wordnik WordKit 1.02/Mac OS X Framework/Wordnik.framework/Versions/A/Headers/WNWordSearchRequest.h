/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

/**
 * @ingroup globals
 *
 * Supported collations for WNWordSearchRequest.
 */
typedef enum {
    /** Order the results alphabetically. */
    WNAutocompleteWordCollationAlphabetical = 0,

    /** Order the results by frequency descending -- that is, highest frequency results will be listed
     * first */
    WNAutocompleteWordCollationFrequencyDescending = 1
} WNAutocompleteWordCollation;


@interface WNWordSearchRequest : NSObject {
@private
    NSString *_wordFragment;
	NSInteger _skip;
	NSInteger _limit;
	NSString* _includePartOfSpeech;
	NSString* _excludePartOfSpeech;
	NSInteger _minCorpusCount;
	NSInteger _maxCorpusCount;
	NSInteger _minDictionaryCount;
	NSInteger _maxDictionaryCount;
	NSInteger _minLength;
	NSInteger _maxLength;
    WNAutocompleteWordCollation _resultCollation;
}

+ (id) requestWithWordFragment: (NSString *)wordFragment
						  skip: (NSInteger)skip
						 limit: (NSInteger)limit
		   includePartOfSpeech: (NSString*)includePartOfSpeech
		   excludePartOfSpeech: (NSString*)excludePartOfSpeech
				minCorpusCount: (NSInteger)minCorpusCount
				maxCorpusCount: (NSInteger)maxCorpusCount
			minDictionaryCount: (NSInteger)minDictionaryCount
			maxDictionaryCount: (NSInteger)maxDictionaryCount
					 minLength: (NSInteger)minLength
					 maxLength: (NSInteger)maxLength
			   resultCollation: (WNAutocompleteWordCollation) resultCollation;

- (id)  initWithWordFragment: (NSString *)wordFragment
						skip: (NSInteger)skip
					   limit: (NSInteger)limit
		 includePartOfSpeech: (NSString*)includePartOfSpeech
		 excludePartOfSpeech: (NSString*)excludePartOfSpeech
			  minCorpusCount: (NSInteger)minCorpusCount
			  maxCorpusCount: (NSInteger)maxCorpusCount
		  minDictionaryCount: (NSInteger)minDictionaryCount
		  maxDictionaryCount: (NSInteger)maxDictionaryCount
				   minLength: (NSInteger)minLength
				   maxLength: (NSInteger)maxLength
			 resultCollation: (WNAutocompleteWordCollation) resultCollation;

/** The word fragment to be autocompleted. A single-character '*' wild-card may be included; 't*e' would match 'the'. */
@property(nonatomic, readonly) NSString *wordFragment;

/** The offset of the results to be returned. Can be used to paginate autocomplete suggestions. */
@property(nonatomic, readonly) NSInteger skip;
@property(nonatomic, readonly) NSInteger limit;
@property(nonatomic, readonly) NSString* includePartOfSpeech;
@property(nonatomic, readonly) NSString* excludePartOfSpeech;
@property(nonatomic, readonly) NSInteger minCorpusCount;
@property(nonatomic, readonly) NSInteger maxCorpusCount;
@property(nonatomic, readonly) NSInteger minDictionaryCount;
@property(nonatomic, readonly) NSInteger maxDictionaryCount;
@property(nonatomic, readonly) NSInteger minLength;
@property(nonatomic, readonly) NSInteger maxLength;

/** The collation to use for the returned results. */
@property(nonatomic, readonly) WNAutocompleteWordCollation resultCollation;


@end
