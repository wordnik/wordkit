/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNWordResponse.h>
#import <Wordnik/WNRequestTicket.h>

@protocol WNWordDataSource;

/**
 * @defgroup classes_datasource Data Source
 * @ingroup classes
 *
 * Provides a generic API for asynchronous loading of word data from arbitrary sources.
 */

/**
 * @ingroup classes_datasource
 *
 * Implement the WNWordDataSourceListener protocol to receive asynchronous results from WNWordDataSource.
 */
@protocol WNWordDataSourceListener <NSObject>

/**
 * Called when a successful word response has been received.
 *
 * @param dataSource The sending data source.
 * @param response The word response.
 */
- (void) dataSource: (id<WNWordDataSource>) dataSource didReceiveWordResponse: (WNWordResponse *) response;

/**
 * Called when word lookup fails.
 *
 * @param dataSource The sending data source.
 * @param error An error in the WNErrorDomain that describes the failure.
 */
- (void) dataSource: (id<WNWordDataSource>) dataSource didFailWithError: (NSError *) error;

@end


/**
 * A generic asynchronous data source for performing wordnik lookups.
 *
 * @note Implementing this API requires a block-compatible compiler, available in iOS 4.0 or later.
 */
@protocol WNWordDataSource <NSObject>

/**
 * Perform an asynchronous lookup of the provided word, providing the WNWordResult to the given
 * WNWordDataSourceListener.
 */
- (WNRequestTicket *) wordResponseWithWord: (NSString *) word listener: (id<WNWordDataSourceListener>) listener;

@end
