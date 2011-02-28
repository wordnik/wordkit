/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNRequestTicket.h>
#import <Wordnik/WNWordResponse.h>

#import <Wordnik/WNWordSearchResponse.h>
#import <Wordnik/WNWordOfTheDayResponse.h>

#import <Wordnik/WNWordListCreateResponse.h>

#import <Wordnik/WNClientAPIUsageStatus.h>

@class WNClient;

/**
 * @ingroup classes_client
 *
 * The WNClientObserver protocol declares the interface that WNClient observers must implement.
 */
@protocol WNClientObserver
@optional

#pragma mark API Usage Status

/**
 * Sent when an API usage status request succeeds.
 *
 * @param client The sending client.
 * @param status The API usage status as reported by the server.
 * @param requestTicket The request ticket corresponding to the successful status request.
 */
- (void) client: (WNClient *) client didReceiveAPIUsageStatus: (WNClientAPIUsageStatus *) status requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when an API usage status request fails.
 *
 * @param client The sending client.
 * @param error An error in the WNErrorDomain describing the request failure.
 * @param requestTicket The request ticket corresponding to the status request.
 */
- (void) client: (WNClient *) client apiUsageStatusRequestDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket;

#pragma mark Authentication

/**
 * Sent when client authentication succeeds.
 *
 * @param client The sending client.
 * @param requestTicket The request ticket corresponding to the successful login request.
 */
- (void) client: (WNClient *) client didLoginWithRequestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when the client logs out.
 *
 * @param client The sending client.
 */
- (void) clientDidLogout: (WNClient *) client;

/**
 * Sent when client authentication has failed.
 *
 * @param client The sending client.
 * @param error An error in the WNErrorDomain describing the authentication failure.
 * @param requestTicket The request ticket corresponding to the failed login request.
 */
- (void) client: (WNClient *) client loginDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket;


#pragma mark Word Lookup

/**
 * Sent when a single word request has succeeded.
 *
 * @param client The sending client.
 * @param response The word response.
 * @param requestTicket The request ticket corresponding to the word request.
 */
- (void) client: (WNClient *) client didReceiveWordResponse: (WNWordResponse *) response requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when a multi-word request has succeeded.
 *
 * @param client The sending client.
 * @param responses The word responses.
 * @param requestTicket The request ticket corresponding to the word request.
 */
- (void) client: (WNClient *) client didReceiveWordResponses: (NSArray *) responses requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when a single or mult-word request has failed.
 *
 * @param client The sending client.
 * @param error An error in the WNErrorDomain describing the request failure.
 * @param requestTicket The request ticket corresponding to the word request.
 */
- (void) client: (WNClient *) client wordRequestDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket;


#pragma mark Random Words

/**
 * Sent when a random word request has succeeded.
 *
 * @param client The sending client.
 * @param words Array of random words.
 * @param requestTicket The request ticket corresponding to the word request.
 */
- (void) client: (WNClient *) client didReceiveRandomWords: (NSArray *) words requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when a random word request has failed.
 *
 * @param client The sending client.
 * @param error An error in the WNErrorDomain describing the request failure.
 * @param requestTicket The request ticket corresponding to the random word request.
 */
- (void) client: (WNClient *) client randomWordRequestDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket;


#pragma mark Autocomplete

/**
 * Sent when an autocomplete request has succeeded.
 *
 * @param client The sending client.
 * @param response The autocomplete response.
 * @param requestTicket The request ticket corresponding to the autocomplete word request.
 */
- (void) client: (WNClient *) client didReceiveAutocompleteWordResponse: (WNWordSearchResponse *) response requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when an autocomplete request has failed.
 *
 * @param client The sending client.
 * @param error An error in the WNErrorDomain describing the request failure.
 * @param requestTicket The request ticket corresponding to the autocomplete word request.
 */
- (void) client: (WNClient *) client autocompleteWordRequestDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket;


#pragma mark Word of The Day

/**
 * Sent when a word of the day request has succeeded.
 *
 * @param client The sending client.
 * @param response The word-of-the-day response.
 * @param requestTicket The request ticket corresponding to the autocomplete word request.
 */
- (void) client: (WNClient *) client didReceiveWordOfTheDayResponse: (WNWordOfTheDayResponse *) response requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when a word of the day request has failed.
 *
 * @param client The sending client.
 * @param error An error in the WNErrorDomain describing the request failure.
 * @param requestTicket The request ticket corresponding to the word of the day request.
 */
- (void) client: (WNClient *) client wordOfTheDayRequestDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket;


#pragma mark Word List

/**
 * Sent when a word list creation request has succeeded.
 *
 * @param client The sending client.
 * @param response The list creation response response.
 * @param requestTicket The request ticket corresponding to the list creation request.
 */
- (void) client: (WNClient *) client didReceiveWordListCreateResponse: (WNWordListCreateResponse *) response requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when a word list creation request has failed.
 *
 * @param client The sending client.
 * @param error An error in the WNErrorDomain describing the request failure.
 * @param requestTicket The request ticket corresponding to the list creation request.
 */
- (void) client: (WNClient *) client wordListCreationDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket;



/**
 * Sent when a word list deletion request has failed.
 *
 * @param client The sending client.
 * @param identifier The word list's unique identifier.
 * @param error An error in the WNErrorDomain describing the failure.
 * @param requestTicket The request ticket corresponding to the failed deletion request.
 */
- (void) client: (WNClient *) client wordListDeletionDidFailWithError: (NSError *) error identifier: (WNWordListIdentifier *) identifier requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when a word list deletion request has succeeded.
 *
 * @param client The sending client.
 * @param identifier The word list's unique identifier.
 * @param requestTicket The request ticket corresponding to the failed deletion request.
 */
- (void) client: (WNClient *) client didDeleteWordListWithIdentifier: (WNWordListIdentifier *) identifier requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when an all word list info request has succeeded.
 *
 * @param client The sending client.
 * @param wordListInfo An array of WNWordListInfo instances.
 * @param requestTicket The request ticket corresponding to the list creation request.
 */
- (void) client: (WNClient *) client didReceiveAllWordListInfo: (NSArray *) wordListInfo requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when an all word list info request has failed.
 *
 * @param client The sending client.
 * @param error An error in the WNErrorDomain describing the request failure.
 * @param requestTicket The request ticket corresponding to the list info request.
 */
- (void) client: (WNClient *) client allWordListInfoRequestDidFailWithError: (NSError *) error requestTicket: (WNRequestTicket *) requestTicket;


/**
 * Sent when the full list of word strings for a given list has been received.
 *
 * @param client The sending client.
 * @param words The received word strings.
 * @param identifier The list identifier.
 * @param requestTicket The request ticket corresponding to the word string request.
 */
- (void) client: (WNClient *) client
    didReceiveWords: (NSArray *) words 
    forListWithIdentifier: (WNWordListIdentifier *) identifier
            requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when a word list word string request has failed.
 *
 * @param client The sending client.
 * @param error An error in the WNErrorDomain describing the failure.
 * @param identifier The list identifier.
 * @param requestTicket The request ticket corresponding to the word string request.
 */
- (void) client: (WNClient *) client
    wordRequestDidFailWithError: (NSError *) error 
                 forListWithIdentifier: (WNWordListIdentifier *) identifier
                         requestTicket: (WNRequestTicket *) requestTicket;


/**
 * Sent when a word string has successfully been added to a word list.
 *
 * @param client The sending client.
 * @param word The added word string
 * @param identifier The list identifier.
 * @param requestTicket The request ticket corresponding to the word string request.
 */
- (void) client: (WNClient *) client
    didAddWord: (NSString *) word
toListWithIdentifier: (WNWordListIdentifier *) identifier
       requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when a failure occurs adding a word string to a word list.
 *
 * @param client The sending client.
 * @param word The word string the client attempted to add.
 * @param error An error in the WNErrorDomain describing the failure.
 * @param identifier The list identifier.
 * @param requestTicket The request ticket corresponding to the word string request.
 */
- (void) client: (WNClient *) client
    didFailToAddWord: (NSString *) word
                 withError: (NSError *) error
      toListWithIdentifier: (WNWordListIdentifier *) identifier
             requestTicket: (WNRequestTicket *) requestTicket;



/**
 * Sent when a word string has successfully been removed from a word list.
 *
 * @param client The sending client.
 * @param word The added word string
 * @param identifier The list identifier.
 * @param requestTicket The request ticket corresponding to the word string request.
 */
- (void) client: (WNClient *) client
    didRemoveWord: (NSString *) word
 fromListWithIdentifier: (WNWordListIdentifier *) identifier
          requestTicket: (WNRequestTicket *) requestTicket;

/**
 * Sent when a failure occurs removing a word string from a word list.
 *
 * @param client The sending client.
 * @param word The word string the client attempted to remove.
 * @param error An error in the WNErrorDomain describing the failure.
 * @param identifier The list identifier.
 * @param requestTicket The request ticket corresponding to the word string request.
 */
- (void) client: (WNClient *) client
    didFailToRemoveWord: (NSString *) word
                    withError: (NSError *) error
       fromListWithIdentifier: (WNWordListIdentifier *) identifier
                requestTicket: (WNRequestTicket *) requestTicket;


@end
