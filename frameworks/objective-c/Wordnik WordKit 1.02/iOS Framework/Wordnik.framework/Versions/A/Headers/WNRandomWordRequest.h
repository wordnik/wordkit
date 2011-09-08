/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <Wordnik/WNConstants.h>

@interface WNRandomWordRequest : NSObject {
@private
	NSInteger _count;
	NSString* _includePartOfSpeech;
	NSString* _excludePartOfSpeech;
	NSInteger _minCorpusCount;
	NSInteger _maxCorpusCount;
	NSInteger _minDictionaryCount;
	NSInteger _maxDictionaryCount;
	NSInteger _minLength;
	NSInteger _maxLength;
}

+ (id) request;
+ (id) requestWordsWithParameters:(NSInteger)count
			  includePartOfSpeech:(NSString*)includePartOfSpeech
			  excludePartOfSpeech:(NSString*)excludePartOfSpeech
				   minCorpusCount:(NSInteger)minCorpusCount
				   maxCorpusCount:(NSInteger)maxCorpusCount
			   minDictionaryCount:(NSInteger)minDictionaryCount
			   maxDictionaryCount:(NSInteger)maxDictionaryCount
						minLength:(NSInteger)minLength
						maxLength:(NSInteger)maxLength;

- (id) init;
- (id) initWordsWithParameters:(NSInteger)count
		   includePartOfSpeech:(NSString*)includePartOfSpeech
		   excludePartOfSpeech:(NSString*)excludePartOfSpeech
				minCorpusCount:(NSInteger)minCorpusCount
				maxCorpusCount:(NSInteger)maxCorpusCount
			minDictionaryCount:(NSInteger)minDictionaryCount
			maxDictionaryCount:(NSInteger)maxDictionaryCount
					 minLength:(NSInteger)minLength
					 maxLength:(NSInteger)maxLength;

/** The maximum number of results to return, or WNUnlimitedResultLength to return the maximum number permitted by the server. */
@property(nonatomic, readonly) NSInteger count;
@property(nonatomic, readonly) NSString* includePartOfSpeech;
@property(nonatomic, readonly) NSString* excludePartOfSpeech;
@property(nonatomic, readonly) NSInteger minCorpusCount;
@property(nonatomic, readonly) NSInteger maxCorpusCount;
@property(nonatomic, readonly) NSInteger minDictionaryCount;
@property(nonatomic, readonly) NSInteger maxDictionaryCount;
@property(nonatomic, readonly) NSInteger minLength;
@property(nonatomic, readonly) NSInteger maxLength;

@end
