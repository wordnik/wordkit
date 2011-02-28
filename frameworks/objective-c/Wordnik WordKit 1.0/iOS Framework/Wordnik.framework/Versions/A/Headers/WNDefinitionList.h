/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <Wordnik/WNDefinition.h>
#import <Wordnik/WNDictionary.h>

@interface WNDefinitionList : NSObject {
@private
    /** Source dictionary */
    WNDictionary *_dictionary;

    /** Ordered array of definitions. */
    NSArray *_definitions;
    
    /** Ordered array of unique head words. */
    NSArray *_headWords;

    /** Map of head word strings to definitions (String -> NSArray<WNDefinition>) */
    NSDictionary *_headWordMap;

    /** Map of parts of speech to definitions. (WNPartOfSpeech -> NSArray<WNDefinition>) */
    NSDictionary *_partsOfSpeechMap;

    /** Parts of speech that have available definitions. */
    NSArray *_partsOfSpeech;
}

+ (id) listWithSourceDictionary: (WNDictionary *) dictionary definitionArray: (NSArray *) definitions;
- (id) initWithSourceDictionary: (WNDictionary *) dictionary definitionArray: (NSArray *) definitions;

- (NSArray *) definitionsForPartOfSpeech: (WNPartOfSpeech *) partOfSpeech;
- (NSArray *) definitionsForHeadWord: (NSString *) headWord;
- (NSString *)componentsJoinedByString:(NSString *)separator;

/** The source dictionary. */
@property(nonatomic, readonly) WNDictionary *sourceDictionary;

/** Ordered array of definitions. */
@property(nonatomic, readonly) NSArray *definitions;

/** Ordered array of unique headwords contains in this list's definitions, as an array of NSString instances. */
@property(nonatomic, readonly) NSArray *headWords;

/** The parts of speech for which definitions are available. */
@property(nonatomic, readonly) NSArray *partsOfSpeech;

@end
