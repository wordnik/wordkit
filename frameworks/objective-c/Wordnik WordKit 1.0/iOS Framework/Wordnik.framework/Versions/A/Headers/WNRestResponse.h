/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import <Foundation/Foundation.h>


@interface WNRestResponse : NSObject {
@private
    /** The untyped JSON object response */
    id _jsonObject;
    
    /** If YES, the response is an API error. */
    BOOL _isError;
    
    /** The server-provided error message associated with this response, or nil if the response is not an error. */
    NSString *_errorMessage;

    /** If YES, the response corresponds to a batch request. */
    BOOL _batched;

    /** Subresponses, if any. Will not be nil, but may be empty. */
    NSArray *_subresponses;
}

+ (id) responseWithJSONObject: (id) jsonObject isBatched: (BOOL) isBatched error: (NSError **) outError;
- (id) initWithJSONObject: (id) jsonObject isBatched: (BOOL) isBatched error: (NSError **) outError;

/** The untyped JSON object returned from the server. */
@property(nonatomic, readonly) id jsonObject;

/** A boolean value indicating whether this is a server error response. */
@property(nonatomic, readonly, getter=isError) BOOL error;

/** The server-provided error message associated with this response, or nil if the response is not an error. */
@property(nonatomic, readonly) NSString *errorMessage;

/** A boolean value indicating whether this is a batched response. */
@property(nonatomic, readonly, getter=isBatched) BOOL batched;

/** An ordered array of batched subresponses. If this is not a batched response, the array will be empty. */
@property(nonatomic, readonly) NSArray *subresponses;

@end
