/*
 * Copyright Wordnik, Inc. 2011. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNWordDataSource.h>
#import <Wordnik/WNLocalWordDataSource.h>
#import <Wordnik/WNWordNetworkDataSource.h>

/**
 * WNCompositeWordDataSource codes for the active policy in data source selection.
 * @ingroup enums
 */
typedef enum {
    /** Use the online data sources if they are reachable */
    WNUseOnlineWhenReachablePolicy,
    
    /** Use the online data sources only, do not use offline data source */
    WNUseOnlineOnlyPolicy,
    
    /** Use the offline data sources first, if the word is not present, then go online if reachable */
    WNUseOfflinePreferredPolicy,
    
    /** Default policy is WNUseOnlineWhenReachablePolicy */
    WNUseDefaultPolicy = WNUseOnlineWhenReachablePolicy,
} WNDataSourceSelectionPolicy;

@interface WNCompositeWordDataSource : NSObject <WNWordDataSource> {  
@private
    /** Current data source selection policy */
    WNDataSourceSelectionPolicy _policy;
        
    /** Local data sources, an array of WNLocalWordDatSource instances */
    NSMutableArray *_localDataSources;
    
    /** Reachability per network data source */
    NSMutableArray *_reachabilities;
    
    /** Network data sources */
    NSMutableArray *_networkDataSources;
    
    NSTimer *_timer;
}

- (id) init;

/** The technique used to get the results */
@property(assign) WNDataSourceSelectionPolicy policy;

- (void) addLocalDataSource: (WNLocalWordDataSource *) dataSource;
- (void) removeLocalDataSource: (WNLocalWordDataSource *) dataSource;

- (void) addNetworkDataSource: (WNWordNetworkDataSource *) dataSource;
- (void) removeNetworkDataSource: (WNWordNetworkDataSource *) dataSource;

@end
