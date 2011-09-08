/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import <Foundation/Foundation.h>


@interface WNRelatedWordType : NSObject <NSCopying> {
@private
    /** The canonical wordnik name for this relation type. */
    NSString *_name;
}

+ (id) synonym;
+ (id) antonym;
+ (id) form;
+ (id) hyponym;
+ (id) variant;
+ (id) verbStem;
+ (id) verbForm;
+ (id) crossReference;
+ (id) sameContext;

+ (id) relatedWordTypeWithName: (NSString *) name;
- (id) initWithTypeName: (NSString *) typeName;

/** Canonical Wordnik word relation type name. */
@property(nonatomic, readonly) NSString *name;

@end
