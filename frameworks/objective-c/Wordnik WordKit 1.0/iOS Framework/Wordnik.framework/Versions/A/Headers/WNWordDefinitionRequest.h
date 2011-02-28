/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNConstants.h>
#import <Wordnik/WNDictionary.h>
#import <Wordnik/WNPartOfSpeech.h>

#import <Wordnik/WNWordElementRequest.h>

@interface WNWordDefinitionRequest : NSObject <WNWordElementRequest> {
@private    
    /** The source dictionary, or nil if all dictionaries should be consulted. */
    WNDictionary *_dictionary;

    /** The maximum number of definitions to return, or WNUnlimitedResultLength for no limit. */
    NSInteger _maxResultCount;

    /** The parts-of-speech to return definitions for, as a set of WNPartOfSpeech instances. If all parts of
     * speech should be permitted, this value will be nil. */
    NSSet *_partsOfSpeech;
}

+ (id) requestWithDictionary: (WNDictionary *) dictionary;
+ (id) requestWithDictionary: (WNDictionary *) dictionary maxResultCount: (NSInteger) maxResultCount;

+ (id) requestWithDictionary: (WNDictionary *) dictionary
               partsOfSpeech: (NSSet *) partsOfSpeech
              maxResultCount: (NSInteger) maxResultCount;

- (id) initWithDictionary: (WNDictionary *) dictionary 
            partsOfSpeech: (NSSet *) partsOfSpeech 
           maxResultCount: (NSInteger) maxResultCount;

@end
