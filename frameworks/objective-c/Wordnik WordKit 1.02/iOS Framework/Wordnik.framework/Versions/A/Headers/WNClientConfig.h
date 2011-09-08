/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNClientConfig : NSObject {
@private
    /** The base API URL. */
    NSURL *_URL;
    
    /** The base secure API URL. */
    NSURL *_secureURL;

    /** The API key to use for requests. */
    NSString *_apiKey;
}

+ (id) configWithAPIKey: (NSString *) apiKey;

- (id) initWithAPIKey: (NSString *) apiKey;
- (id) initWithURL: (NSURL *) apiURL secureURL: (NSURL *) secureURL apiKey: (NSString *) apiKey;

/** The base API URL. */
@property(nonatomic, readonly) NSURL *URL;

/** The base secure API URL. */
@property(nonatomic, readonly) NSURL *secureURL;

/** The API key used for requests. */
@property(nonatomic, readonly) NSString *apiKey;

@end
