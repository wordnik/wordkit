/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */


#import <Foundation/Foundation.h>


@interface WNExample : NSObject {
@private
    /** The example text. */
    NSString *_text;

    /** The example's title. */
    NSString *_title;

    /** The example's publish date date. */
    NSDateComponents *_pubDateComponents;

    /** The example's source URL, or nil if no URL is available. */
    NSURL *_sourceURL;
}

+ (id) exampleSentenceWithTitle: (NSString *) title 
                           text: (NSString *) text 
      publicationDateComponents: (NSDateComponents *) publicationDateComponents 
                      sourceURL: (NSURL *) sourceURL;

- (id)       initWithTitle: (NSString *) title 
                      text: (NSString *) text 
 publicationDateComponents: (NSDateComponents *) publicationDateComponents 
                 sourceURL: (NSURL *) sourceURL;

/** The example text. */
@property(nonatomic, readonly) NSString *text;

/** The example's title. */
@property(nonatomic, readonly) NSString *title;

/** The example's publication date, or nil if unknown. */
@property(nonatomic, readonly) NSDateComponents *publicationDateComponents;

/** The example's source URL, or nil if no URL is available. */
@property(nonatomic, readonly) NSURL *sourceURL;

@end
