/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNDictionary : NSObject <NSCopying> {
@private
    /** Canonical Wordnik dictionary name. */
    NSString *_name;

    /** Localized name. */
    NSString *_localizedName;
}

+ (WNDictionary *) ahdDictionary;
+ (WNDictionary *) centuryDictionary;
+ (WNDictionary *) wiktionaryDictionary;
+ (WNDictionary *) websterDictionary;
+ (WNDictionary *) wordnetDictionary;

+ (id) dictionaryWithName: (NSString *) dictionaryName;
- (id) initWithDictionaryName: (NSString *) dictionaryName;

/** Canonical Wordnik dictionary name. This is an internal, Wordnik-assigned name, and is not intended
 * to be presented to a user. */
@property(nonatomic, readonly) NSString *name;

/** The name of the dictionary, localized for the current locale. */
@property(nonatomic, readonly) NSString *localizedName;

@end
