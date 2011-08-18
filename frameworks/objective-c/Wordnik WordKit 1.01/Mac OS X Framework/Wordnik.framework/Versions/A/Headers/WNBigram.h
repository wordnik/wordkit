/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>


@interface WNBigram : NSObject {
@private
    /** The first word string of this bigram. */
    NSString *_firstWordString;

    /** The second word string of this bigram. */
    NSString *_secondWordString;
    
    /** The mutual information score for this bigram. */
    double _mi;
    
    /** The weighted-log mutual information score for this bigram. */
    double _wlmi;
}

+ (id) bigramWithFirstWordString: (NSString *) firstWord
                secondWordString: (NSString *) secondWord
                              mi: (double) mutualInformationScore
                            wlmi: (double) weightLogMutualInformationScore;

- (id) initWithFirstWordString: (NSString *) firstWord 
              secondWordString: (NSString *) secondWord
                            mi: (double) mutualInformationScore
                          wlmi: (double) weightLogMutualInformationScore;


/** The first word string of this bigram. */
@property(nonatomic, readonly) NSString *firstWordString;

/** The second word string of this bigram. */
@property(nonatomic, readonly) NSString *secondWordString;

/** The mutual information score for this bigram. */
@property(nonatomic, readonly) double mi;

/** The weighted-log mutual information score for this bigram. */
@property(nonatomic, readonly) double wlmi;

@end
