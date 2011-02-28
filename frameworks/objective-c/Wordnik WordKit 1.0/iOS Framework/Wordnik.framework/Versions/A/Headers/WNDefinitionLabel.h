/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

@interface WNDefinitionLabel : NSObject {
@private
    /** Label type. */
    NSString *_type;

    /** Label text. */
    NSString *_text;
}

+ (id) labelWithType: (NSString *) type text: (NSString *) string;
- (id) initWithLabelType: (NSString *) type text: (NSString *) string;

/** Label type. */
@property(nonatomic, readonly) NSString * type;

/** Label text. */
@property(nonatomic, readonly) NSString *text;

@end
