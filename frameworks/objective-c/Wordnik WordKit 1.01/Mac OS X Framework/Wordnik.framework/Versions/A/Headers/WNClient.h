/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNConstants.h>
#import <Wordnik/WNRequestTicket.h>

#import <Wordnik/WNWordObject.h>

#import <Wordnik/WNClientObserver.h>
#import <Wordnik/WNClientConfig.h>
#import <Wordnik/WNClientCredentials.h>

#import <Wordnik/WNWordRequest.h>
#import <Wordnik/WNWordResponse.h>

#import <Wordnik/WNRandomWordRequest.h>

#import <Wordnik/WNWordSearchRequest.h>
#import <Wordnik/WNWordSearchResponse.h>

#import <Wordnik/WNWordOfTheDayResponse.h>

#import <Wordnik/WNWordListCreateRequest.h>
#import <Wordnik/WNWordListCreateResponse.h>

#import <Wordnik/WNClientAPIUsageStatus.h>

#ifdef WORDNIK_PRIVATE
#import <Wordnik/WNObserverProxy.h>
#import <Wordnik/WNRestClient.h>
#else
@class WNObserverProxy;
@class WNRestClient;
#endif

/**
 * @ingroup enums
 *
 * WNClient authentication state.
 */
typedef enum {
    /** The client is not logged in. */
    WNClientAuthStateLoggedOut = 0,

    /** The client is in the process of logging in. */
    WNClientAuthStateLoggingIn = 1,

    /** The client has successfully logged in. */
    WNClientAuthStateLoggedIn = 2
} WNClientAuthState;


@interface WNClient : NSObject {
@private
    /** The REST API client. */
    WNRestClient *_rest;

    /** The authentication token, or nil if the client has not authenticated */
    NSString *_authToken;
    
    /** The current client authentication state. */
    WNClientAuthState _authState;

    /** A cancel ticket that may be used to pre-empt a pending authentication request. If nil,
     * no authentication request is pending */
    WNRequestTicket *_authPreemptTicket;

    /** Registered observers */
    WNObserverProxy<WNClientObserver> *_observers;

    /** Date formatter used for parsing JSON dates. */
    NSDateFormatter *_dateFormatter;
}

+ (id) clientWithConfig: (WNClientConfig *) config;
- (id) initWithClientConfig: (WNClientConfig *) config;

/** The client config used during initialization */
@property(readonly) WNClientConfig *clientConfig;

#pragma mark API Usage

- (WNRequestTicket *) requestAPIUsageStatus;
- (WNRequestTicket *) requestAPIUsageStatusWithCompletionBlock: (void (^)(WNClientAPIUsageStatus *status, NSError *error)) completionBlock;

#pragma mark Authentication

- (WNRequestTicket *) loginWithCredentials: (WNClientCredentials *) credentials;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) loginWithCredentials: (WNClientCredentials *) credentials completionBlock: (void (^)(NSError *error)) completionBlock;
#endif

- (void) logout;

#pragma mark Word API

- (WNRequestTicket *) wordWithRequest: (WNWordRequest *) request;
- (WNRequestTicket *) wordsWithRequests: (NSArray *) wordRequests;

#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) wordWithRequest: (WNWordRequest *) request 
					  completionBlock: (void (^)(WNWordResponse *response, NSError *error)) completionBlock;
- (WNRequestTicket *) wordsWithRequests: (NSArray *) wordRequests 
						completionBlock: (void (^)(NSArray *responses, NSError *error)) completionBlock;
#endif


#pragma mark Random Words
- (WNRequestTicket *) randomWordsWithParameters:(WNRandomWordRequest *)request;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) randomWordsWithParameters: (WNRandomWordRequest *) request
								completionBlock: (void (^)(NSArray *words, NSError *error)) completionBlock;
#endif

#pragma mark Autocomplete

- (WNRequestTicket *) autocompletedWordsWithRequest: (WNWordSearchRequest *) request;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) autocompletedWordsWithRequest: (WNWordSearchRequest *) request
                                    completionBlock: (void (^)(WNWordSearchResponse *response, NSError *error)) completionBlock;
#endif


#pragma mark Word Of the Day

- (WNRequestTicket *) requestWordOfTheDay;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) requestWordOfTheDayWithCompletionBlock: (void (^)(WNWordOfTheDayResponse *response, NSError *error)) completionBlock;
#endif


#pragma mark Word Lists

- (WNRequestTicket *) createWordListWithRequest: (WNWordListCreateRequest *) request;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) createWordListWithRequest: (WNWordListCreateRequest *) request
                                completionBlock: (void (^)(WNWordListCreateResponse *response, NSError *error)) completionBlock;
#endif

- (WNRequestTicket *) deleteWordListWithIdentifier: (WNWordListIdentifier *) identifier;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) deleteWordListWithIdentifier: (WNWordListIdentifier *) identifier
                                   completionBlock: (void (^)(NSError *error)) completionBlock;
#endif

- (WNRequestTicket *) requestAllWordListInfo;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) requestAllWordListInfoWithCompletionBlock: (void (^)(NSArray *wordListsInfo, NSError *error)) completionBlock;
#endif

- (WNRequestTicket *) wordsFromListWithIdentifier: (WNWordListIdentifier *) identifier;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) wordsFromListWithIdentifier: (WNWordListIdentifier *) identifier
                                        completionBlock: (void (^)(NSArray *words, NSError *error)) completionBlock;
#endif

- (WNRequestTicket *) addWord: (NSString *) word toListWithIdentifier: (WNWordListIdentifier *) identifier;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) addWord: (NSString *) word
               toListWithIdentifier: (WNWordListIdentifier *) identifier
                    completionBlock: (void (^)(NSError *error)) completionBlock;
#endif

- (WNRequestTicket *) removeWord: (NSString *) word fromListWithIdentifier: (WNWordListIdentifier *) identifier;
#if WN_BLOCKS_AVAILABLE
- (WNRequestTicket *) removeWord: (NSString *) word
                fromListWithIdentifier: (WNWordListIdentifier *) identifier
                       completionBlock: (void (^)(NSError *error)) completionBlock;
#endif

#pragma mark Observers

- (void) addObserver: (id<WNClientObserver>) observer;
- (void) removeObserver: (id<WNClientObserver>) observer;

#pragma mark Properties

/** The current client authentication state. */
@property(nonatomic, readonly) WNClientAuthState authenticationState;

@end
