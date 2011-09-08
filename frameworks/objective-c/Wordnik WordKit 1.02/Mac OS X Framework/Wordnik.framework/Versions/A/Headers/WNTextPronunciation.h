/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNTextPronunciationType.h>

@interface WNTextPronunciation : NSObject {
@private
    /** The raw pronunciation string. */
    NSString *_pronunciationString;

    /** The pronunciation type. */
    WNTextPronunciationType *_type;
}

+ (id) pronunciationWithPronunciationString: (NSString *) pronunciationString type: (WNTextPronunciationType *) type;
- (id) initWithPronunciationString: (NSString *) pronunciationString type: (WNTextPronunciationType *) type;

/** The pronunciation's string value. */
@property(nonatomic, readonly) NSString *pronunciationString;

/** The pronunciation type. */
@property(nonatomic, readonly) WNTextPronunciationType *pronunciationType;

@end
