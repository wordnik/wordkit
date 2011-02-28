/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNClient.h>
#import <Wordnik/WNWordDataSource.h>

@interface WNWordNetworkDataSource : NSObject <WNWordDataSource> {
@private
    /** Backing network client. */
    WNClient *_client;
}

- (id) initWithWordnikClient: (WNClient *) client;

/** The Wordnik client used during initialization */
@property(readonly) WNClient *wordnikClient;

@end
