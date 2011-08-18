/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

#import <Wordnik/WNWordElementRequest.h>

@interface WNAudioFileMetadataRequest : NSObject <WNWordElementRequest> {
@private
	NSDateFormatter *_dateFormatter;
}

+ (id) request;
- (id) init;

@end
