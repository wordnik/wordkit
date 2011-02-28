/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import "WNWordListInfo.h"

@interface WNWordListCreateRequest : NSObject {
@private
    /** Word list name. */
    NSString *_name;

    /** Word list description. */
    NSString *_description;

    /** Word list access type. */
    WNWordListAccessType _accessType;
}


+ (id) requestWithListName: (NSString *) name 
               description: (NSString *) description 
                accessType: (WNWordListAccessType) accessType;

- (id) initWithListName: (NSString *) name 
            description: (NSString *) description 
             accessType: (WNWordListAccessType) accessType;

/** Word list name. */
@property(nonatomic, readonly) NSString *name;

/** Word list description. */
@property(nonatomic, readonly) NSString *description;

/** Word list access type. */
@property(nonatomic, readonly) WNWordListAccessType accessType;

@end
