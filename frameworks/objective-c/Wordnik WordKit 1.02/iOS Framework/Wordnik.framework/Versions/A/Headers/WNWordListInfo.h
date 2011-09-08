/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNWordListIdentifier.h>

/**
 * @ingroup enums
 *
 * Word list access types.
 */
typedef enum {
    /** A public word list. */
    WNWordListAccessTypePublic = 0,

    /** A private word list. */
    WNWordListAccessTypePrivate = 1
} WNWordListAccessType;


@interface WNWordListInfo : NSObject {
@private
    /** The list's unique identifier. */
    WNWordListIdentifier *_identifier;

    /** The list's name. */
    NSString *_name;
    
    /** The list's description. */
    NSString *_description;

    /** The list's creation date. */
    NSDate *_creationDate;
    
    /** The list's last modification date. */
    NSDate *_modificationDate;

    /** The number of words in the list. */
    NSInteger _wordCount;
}

+ (id) infoWithIdentifier: (WNWordListIdentifier *) identifier
                     name: (NSString *) name
              description: (NSString *) description
             creationDate: (NSDate *) creationDate
         modificationDate: (NSDate *) modificationDate
                wordCount: (NSInteger) wordCount;

- (id) initWithIdentifier: (WNWordListIdentifier *) identifier
                     name: (NSString *) name
              description: (NSString *) description
             creationDate: (NSDate *) creationDate
         modificationDate: (NSDate *) modificationDate
                wordCount: (NSInteger) wordCount;

/** The list's unique identifier. */
@property(nonatomic, readonly) WNWordListIdentifier *identifier;

/** The list's name. */
@property(nonatomic, readonly) NSString *name;

/** The list's description. */
@property(nonatomic, readonly) NSString *description;

/** The list's creation date. */
@property(nonatomic, readonly) NSDate *creationDate;

/** The list's last modification date. */
@property(nonatomic, readonly) NSDate *modificationDate;

/** The number of words in the list. */
@property(nonatomic, readonly) NSInteger wordCount;

@end
