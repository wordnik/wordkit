#import <Foundation/Foundation.h>
#import <Wordnik/Wordnik.h>
#import <AppKit/NSSound.h>

/** Replace with your API key here */
#define API_KEY @"YOUR_API_KEY"];

/**
 * Simple example to fetch an audio file metadata and play it back
 * using the AppKit framework
 */

int main (int argc, const char * argv[]) {
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	WNClientConfig *config = [WNClientConfig configWithAPIKey: API_KEY;
	WNClient *client = [WNClient clientWithConfig: config];

	//	include audio in the elements to retrieve
	NSArray *elements = [NSArray arrayWithObjects:
					   [WNAudioFileMetadataRequest request],
					   nil];

	//	Build a request
	WNWordRequest *req = [WNWordRequest requestWithWord: @"gorilla"
								   requestCanonicalForm: YES
							 requestSpellingSuggestions: YES
										elementRequests: elements];

	//	Issue the request with completion block
	[client wordWithRequest: req completionBlock: ^(WNWordResponse * resp, NSError *error) {
		if (error != nil) {
			NSLog(@"Word lookup failed failed: %@", error);
			exit(0);
		}
		for(WNAudioFileMetadata *audio in resp.wordObject.audioFileMetadata){
			NSURL * url = [NSURL URLWithString:audio.fileUrl ];
			NSLog(@"playing url: %@",url);

			NSSound *sound = [[NSSound alloc] initWithContentsOfURL:url byReference:NO];
			[sound play];
			while([sound isPlaying]){
				sleep(1);
			}
			[sound release];
		}
		exit(0);
	}];
							  
	[pool drain];
	[[NSRunLoop currentRunLoop] run];
	return 0;
}
