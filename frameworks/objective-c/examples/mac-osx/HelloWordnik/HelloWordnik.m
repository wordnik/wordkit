#import <Foundation/Foundation.h>
#import <Wordnik/Wordnik.h>

/** Replace with your API key here */
#define API_KEY @"fe77d2c34a350d601e00e071b730220efe321328c2df0a430"];

/**
 * Basic example to fetch definitions for a word
 */
int main (int argc, const char * argv[]) {
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	WNClientConfig *config = [WNClientConfig configWithAPIKey: API_KEY;
	WNClient *client = [WNClient clientWithConfig: config];
							  
	/* Fetch API usage information (for testing purposes). */
	[client requestAPIUsageStatusWithCompletionBlock: ^(WNClientAPIUsageStatus *status, NSError *error) {
        if (error != nil) {
            NSLog(@"Usage request failed: %@", error);
            return;
        }
		
        NSMutableString *output = [NSMutableString string];
        [output appendFormat: @"Expires at: %@\n", status.expirationDate];
        [output appendFormat: @"Reset at: %@\n", status.resetDate];
        [output appendFormat: @"Total calls permitted: %ld\n", (long) status.totalPermittedRequestCount];
        [output appendFormat: @"Total calls remaining: %ld\n", (long) status.remainingPermittedRequestCount];
		
        NSLog(@"API Usage:\n%@", output);
    }];

	//	Create definition request for 'Hello', using the American Heritage Dictionary.	
	NSArray *elements = [NSArray arrayWithObjects:
						 [WNWordDefinitionRequest requestWithDictionary: nil],
						 nil];
							  
	//	Build a request
	WNWordRequest *req = [WNWordRequest requestWithWord: @"hi"
								   requestCanonicalForm: NO
							 requestSpellingSuggestions: YES
										elementRequests: elements];

	//	Issue the request with completion block
	[client wordWithRequest: req completionBlock: ^(WNWordResponse * resp, NSError *error) {
		if (error != nil) {
			NSLog(@"Word lookup failed failed: %@", error);
			exit(0);
		}
		NSLog(@"%@", resp.wordObject.word);

		for(WNDefinitionList * defs in resp.wordObject.definitions){
			NSLog(@"Definitions from the %@ dictionary",defs.sourceDictionary.name);
			for(WNDefinition * def in defs.definitions){
				NSLog(@"* %@, %@\n",def.text, def.dictionary);
			}
		}
		exit(0);
	}];
	
	[pool drain];
	[[NSRunLoop currentRunLoop] run];
    return 0;
}
