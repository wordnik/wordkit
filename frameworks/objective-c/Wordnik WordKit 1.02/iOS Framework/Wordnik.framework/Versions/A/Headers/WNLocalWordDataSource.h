/*
 * Copyright Wordnik, Inc. 2011. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNWordDataSource.h>

@class WNOfflineDatabase;

@interface WNLocalWordDataSource : NSObject <WNWordDataSource> {   
@private
    /** Underlying database for local word data source */
    WNOfflineDatabase *_database;
}

-initWithPath:(NSString *)path;

@end
