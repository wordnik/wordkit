/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

extern NSString *WNErrorServerMessageKey;
extern NSString *WNErrorDomain;

/**
 * Unlimited result length.
 *
 * @ingroup constants
 */
#define WNUnlimitedResultLength ((NSInteger)-1)

/**
 * NSError codes in the WNErrorDomain.
 * @ingroup enums
 */
typedef enum {
    /** An unknown error occured. Any use of this error code should be considered a bug. */
    WNErrorCodeUnknown = 0,

    /** The request failed due to a network, server, or other communications error. */
    WNErrorCodeConnectionFailed = 1,
    
    /** The request failed due to an invalid response received from the server. */
    WNErrorCodeInvalidResponse = 2,

    /** The request failed due to a conflict with an existing request. */
    WNErrorCodeRequestConflict = 3,
    
    /** Authentication to the remote server or resource failed. */
    WNErrorCodeAuthenticatedFailed = 4,

    /**
     * The server returned an error result for the request, but a more specific error code is unavailable. Additional
     * information may be available via the WNErrorServerMessageKey.
     *
     * @todo Should the server always provide more specific error codes so that we can provide less general request
     * errors?
     */
    WNErrorCodeRequestGeneralError = 5,
    
    /** The request failed due to a database query failure. */
    WNErrorCodeDatabaseQueryFailed = 6,
    
    /** The request failed due to no available data sources. */
    WNErrorCodeNoDataSourcesAvailable = 7,
    
} WNErrorCode;

/*
 * Provide a WN_BLOCKS_AVAILABLE flag, which will be enabled if the compiler itself supports blocks. Unlike Apple's
 * NS_BLOCKS_AVAILABLE, this allows the use of PLBlocks while avoiding parse errors on earlier non-block-enabled
 * compilers.
 */
#ifdef __BLOCKS__
    #define WN_BLOCKS_AVAILABLE 1
#else
    #define WN_BLOCKS_AVAILABLE 0
#endif


#ifdef WORDNIK_PRIVATE
NSError *WNServerErrorWithCode (WNErrorCode code, NSString *failureReason, NSString *serverMessage, NSError *cause);
NSError *WNErrorWithCode (WNErrorCode code, NSString *failureReason, NSError *cause);
#endif
