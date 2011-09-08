/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNTextPronunciationType : NSObject {
@private
    /** Type name */
    NSString *_name;
}

+ (id) gcideDiacritical;
+ (id) arpabet;

+ (id) typeWithName: (NSString *) name;
- (id) initWithName: (NSString *) name;

/** Text pronunciation type name. */
@property(nonatomic, readonly) NSString *name;

@end
