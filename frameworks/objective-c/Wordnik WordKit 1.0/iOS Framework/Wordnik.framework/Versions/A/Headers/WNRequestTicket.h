/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <Wordnik/WNConstants.h>

@interface WNRequestTicket : NSObject {
@private
#if WN_BLOCKS_AVAILABLE
    void (^_block)();
#else
    id _block;
#endif /* __BLOCKS__ */
}

+ (id) emptyTicket;

#if WN_BLOCKS_AVAILABLE
+ (id) ticketWithCancelBlock: (void (^)()) block;
- (id) initWithCancelBlock: (void (^)()) block;
#endif /* __BLOCKS__ */

- (void) cancel;

@end
