/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <Wordnik/WNPartOfSpeech.h>
#import <Wordnik/WNDefinitionCitation.h>
#import <Wordnik/WNDefinitionLabel.h>
#import <Wordnik/WNDictionary.h>

@interface WNDefinition : NSObject {
@private
    /**
     * HeadWord. This is the word that should serve as the heading for this definition's
     * entry in the dictionary.
     */
    NSString *_headWord;

    /** The definition text. */
    NSString *_text;
    
    /** The optional extended definition text. If available, may be used in favor of the definition text
     * in contexts where a longer, expanded definition is suitable. */
    NSString *_extendedText;

    /** This definition's part of speech */
    WNPartOfSpeech *_partOfSpeech;
    
    /** The ordered array of citations for this definition, as an array of WNDefinitionCitation instances. */
    NSArray *_citations;

    /** The array of labels for this definition, as an array of WNDefinitionLabel instances. */
    NSArray *_labels;
	
	WNDictionary *_dictionary;
}

+ (id) definitionWithHeadWord: (NSString *) headWord 
						 text: (NSString *) text 
				 extendedText: (NSString *) extendedText
				 partOfSpeech: (WNPartOfSpeech *) partOfSpeech
					citations: (NSArray *) citations
					   labels: (NSArray *) labels
				   dictionary: (WNDictionary*)dictionary;

- (id) initWithHeadWord: (NSString *) headWord 
				   text: (NSString *) text 
		   extendedText: (NSString *) extendedText
		   partOfSpeech: (WNPartOfSpeech *) partOfSpeech
			  citations: (NSArray *) citations
				 labels: (NSArray *) labels
			 dictionary: (WNDictionary*)dictionary;


/**
 * Head word. This is the word that should serve as the heading for this definition's
 * entry in the dictionary.
 */
@property(nonatomic, readonly) NSString *headWord;

/** The definition text. */
@property(nonatomic, readonly) NSString *text;

/** The optional extended definition text. If not nil, this property may be used in favor of the definition text
 * in contexts where a longer, expanded definition is suitable. */
@property(nonatomic, readonly) NSString *extendedText;

/** This definition's part of speech */
@property(nonatomic, readonly) WNPartOfSpeech *partOfSpeech;

/** The ordered array of citations for this definition, as an array of WNDefinitionCitation instances. If no citations
 * are available, this array will be empty. */
@property(nonatomic, readonly) NSArray *citations;

/** The array of labels for this definition, as an array of WNDefinitionLabel instances. If no labels are available,
 * this array will be empty. */
@property(nonatomic, readonly) NSArray *labels;

/** The source dictionary for this definition.  If not definied, this will be nil */
@property(nonatomic, readonly) WNDictionary * dictionary;
@end
