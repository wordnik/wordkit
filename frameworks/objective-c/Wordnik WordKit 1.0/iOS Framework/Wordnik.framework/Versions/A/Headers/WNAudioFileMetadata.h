/*
 * Copyright Wordnik, Inc. 2010. All rights reserved.
 */

#import <Foundation/Foundation.h>

@interface WNAudioFileMetadata : NSObject {
@private
    /** metadata id. */
    NSInteger _fileId;
	
	/** creator of the audio file */
    NSString * _createdBy;
	
	/** time-expiring URL to get the file */
	NSString * _fileUrl;
	
	/** description of the metadata */
	NSString * _description;
}

+ (id) audioFileMetadataWithId: (NSInteger) fileId
					 createdBy:(NSString*)createdBy
					   fileUrl: (NSString*)fileUrl
				   description:(NSString*)description;

- (id) initWithId: (NSInteger)fileId
		createdBy:(NSString*)createdBy
		  fileUrl: (NSString*)fileUrl
	  description:(NSString*)description;

@property(nonatomic, readonly) NSInteger fileId;
@property(nonatomic, readonly) NSString* createdBy;
@property(nonatomic, readonly) NSString* fileUrl;
@property(nonatomic, readonly) NSString* description;

@end
