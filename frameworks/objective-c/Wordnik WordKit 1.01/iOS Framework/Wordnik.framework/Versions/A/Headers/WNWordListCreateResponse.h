/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <Wordnik/WNWordListInfo.h>

@interface WNWordListCreateResponse : NSObject {
@private
    /** The server-supplied list information. */
    WNWordListInfo *_listInfo;
}

+ (id) responseWithListInfo: (WNWordListInfo *) listInfo;
- (id) initWithListInfo: (WNWordListInfo *) listInfo;

/** The server-supplied list information. */
@property(nonatomic, readonly) WNWordListInfo *listInfo;

@end
