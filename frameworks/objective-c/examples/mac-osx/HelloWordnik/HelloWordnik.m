#import <Foundation/Foundation.h>
#import <Wordnik/Wordnik.h>

/** Replace with your API key here */
#define API_KEY @"YOUR_API_KEY"];

/**
 * Basic example to fetch definitions for a word
 */
int main (int argc, const char * argv[]) {
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	WNClientConfig *config = [WNClientConfig configWithAPIKey: API_KEY;
	WNClient *client = [WNClient clientWithConfig: config];

	//	Create definition request for 'Hello', using the American Heritage Dictionary.	
	NSArray *elements = [NSArray arrayWithObjects:
						 [WNWordDefinitionRequest requestWithDictionary: [WNDictionary ahdDictionary]],
						 nil];
							  
	//	Build a request
	WNWordRequest *req = [WNWordRequest requestWithWord: @"Hello"
								   requestCanonicalForm: YES
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
				NSLog(@"* %@\n",def.text);
			}
		}
		exit(0);
	}];
	
	[pool drain];
	[[NSRunLoop currentRunLoop] run];
    return 0;
}
