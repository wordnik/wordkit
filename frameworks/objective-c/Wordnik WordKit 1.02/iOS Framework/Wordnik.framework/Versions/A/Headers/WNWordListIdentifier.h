/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNWordListIdentifier : NSObject {
@private
    /** The wordlist identifier's string value. */
    NSString *_stringValue;
}

+ (id) identifierWithString: (NSString *) identifierString;
- (id) initWithString: (NSString *) identifierString;

/** The identifier's string value. */
@property(nonatomic, readonly) NSString *stringValue;

@end
