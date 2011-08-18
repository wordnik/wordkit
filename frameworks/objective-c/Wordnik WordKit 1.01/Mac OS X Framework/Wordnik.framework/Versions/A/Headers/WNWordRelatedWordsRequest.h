/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNWordElementRequest.h>
#import <Wordnik/WNRelatedWordType.h>
#import <Wordnik/WNDictionary.h>
#import <Wordnik/WNConstants.h>

@interface WNWordRelatedWordsRequest : NSObject <WNWordElementRequest> {
@private
    /** Dictionary to use for query, or nil to use all available dictionaries. */
    WNDictionary *_dictionary;

    /** The parts-of-speech to return related words for, as a set of WNPartOfSpeech instances. If all parts of
     * speech should be permitted, this value will be nil. */
    NSSet *_partsOfSpeech;

    /** Requested word relation types, or nil to request all relation types. */
    NSSet *_relationTypes;
    
    /** The maximum number of related words to return, or WNUnlimitedResultLength for no limit. */
    NSInteger _maxResultCount;
}

+ (id) request;
+ (id) requestWithMaxResultCount: (NSInteger) maxResultCount;

+ (id) requestWithRelationTypes: (NSSet *) relationTypes;

+ (id) requestWithRelationTypes: (NSSet *) relationTypes
                 maxResultCount: (NSInteger) maxResultCount;

+ (id) requestWithRelationTypes: (NSSet *) relationTypes
                  partsOfSpeech: (NSSet *) partsOfSpeech
                     dictionary: (WNDictionary *) dictionary
                 maxResultCount: (NSInteger) maxResultCount;


- (id) init;

- (id) initWithRelationTypes: (NSSet *) relationTypes;
- (id) initWithRelationTypes: (NSSet *) relationTypes
              maxResultCount: (NSInteger) maxResultCount;

- (id) initWithRelationTypes: (NSSet *) relationTypes
               partsOfSpeech: (NSSet *) partsOfSpeech
                  dictionary: (WNDictionary *) dictionary
              maxResultCount: (NSInteger) maxResultCount;

@end
