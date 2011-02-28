/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNClientCredentials : NSObject {
@private
    /** Username. */
    NSString *_username;

    /** Password. */
    NSString *_password;
}

+ (id) credentialsWithUsername: (NSString *) username password: (NSString *) password;

- (id) initWithUsername: (NSString *) username password: (NSString *) password;

/** Wordnik username. */
@property(nonatomic, readonly) NSString *username;

/** Wordnik password. */
@property(nonatomic, readonly) NSString *password;

@end
