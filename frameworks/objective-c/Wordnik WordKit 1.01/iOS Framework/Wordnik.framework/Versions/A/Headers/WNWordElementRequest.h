/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNWordObject.h>

#ifdef WORDNIK_PRIVATE
#import <Wordnik/WNRestResource.h>
#import <Wordnik/WNRestResponse.h>
#endif

/**
 * A WNWordElementRequest specifies a specific word element to be fetched from a server
 * or other data source.
 *
 * Such elements include definitions, example phrases, and pronounciation information.
 *
 * @see WNWordDefinitionRequest
 * @see WNWordBigramRequest
 * @see WNWordExampleRequest
 * @see WNWordRelatedWordsRequest
 * @see WNWordUsageFrequencyRequest
 * @see WNWordPunctuationFactorRequest
 * @see WNWordTextPronunciationRequest
 */
@protocol WNWordElementRequest <NSObject>

#ifdef WORDNIK_PRIVATE

/**
 * @internal
 * @{
 */


/**
 * Return a new WNWordObject instance formed by parsing and applying the contents of @a response to the existing
 * @a word value. The provided response <em>MUST NOT</em> be an error response.
 *
 * If an error occurs parsing the response, nil should be returned, and an error in the WNErrorDomain 
 * must be provided if @a outError is non-NULL.
 *
 * @param response A REST response corresponding to this element's returned restResource.
 * @param word An immutable word object; the union of this word with the data included in @a response should
 * be returned.
 * @param outError If an error occurs parsing the JSON object, upon return contains
 * an error in the WNErrorDomain that describes the problem. Pass NULL if you do not want error information.
 */
- (WNWordObject *) wordByApplyingRestResponse: (WNRestResponse *) response 
                                 toWord: (WNWordObject *) word 
                                  error: (NSError **) outError;

/**
 * Return the REST resource representation for this request.
 */
- (WNRestResource *) restResource;

/**
 * @}
 */

#endif

@end
