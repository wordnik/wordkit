/*
 * Copyright Wordnik, Inc. 2011. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Wordnik/WNWordDataSource.h>

@class WNCompositeWordDataSource;

@interface WNCompositeDataSourceListener : NSObject <WNWordDataSourceListener> {
@private
    /** The composite data source which created this listener */
    WNCompositeWordDataSource *_masterDataSource;
    
    /** The data sources for this request */
    NSArray   *_dataSources;
    
    /** The word string for this request */
    NSString *_wordString;
    
    /** The listener passed in on the main request */
    id <WNWordDataSourceListener> _listener;
    
    /** Current data source we are looking in */
    NSUInteger _currentIndex;
    
    /** Current cancel ticket */
    WNRequestTicket *_currentTicket;
    
    /** Last error sent from the data sources */
    NSError *_lastError;
}

- (id) initWithMasterSource: (WNCompositeWordDataSource *)masterDataSource dataSources: (NSArray *)dataSources wordString:(NSString *) wordString listener:(id <WNWordDataSourceListener>) listener;

- (void) start;

- (void) cancel;

@end
