/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNDefinitionCitation : NSObject {
@private
    /** The citation source name. */
    NSString *_sourceName;

    /** The citation text. */
    NSString *_text;
}

+ (id) citationWithSourceName: (NSString *) sourceName text: (NSString *) text;
- (id) initWithSourceName: (NSString *) sourceName text: (NSString *) text;

/** The citation source's name. */
@property(nonatomic, readonly) NSString *sourceName;

/** The citation text. */
@property(nonatomic, readonly) NSString *text;

@end
